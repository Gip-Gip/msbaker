//! Code used to interface with SD cards using SDIO

// Copyright (c) 2023 Charles M. Thompson
//
// This file is part of Ms. Baker's firmware.
//
// Ms. Baker's firmware is free software: you can redistribute it and/or modify it under
// the terms only of version 3 of the GNU General Public License as published
// by the Free Software Foundation
//
// Ms. Baker's firmware is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// Ms. Baker's firmware(in a file named LEGAL-SOFTWARE).
// If not, see <https://www.gnu.org/licenses/>.

use hal::pio::{MovStatusConfig, PinDir, ShiftDirection, PIOExt, PIO, PIOBuilder, SM0, SM1, StateMachine, UninitStateMachine, Running, Rx, Tx};
use pio_proc::pio_file;
use cortex_m::delay::Delay;
use rp2040_hal as hal;

/// CRC7 Table used for calculating all 7-bit sd-card crcs
pub static CRC7_TABLE: [u8; 256] = [
    0x00, 0x12, 0x24, 0x36, 0x48, 0x5a, 0x6c, 0x7e, 0x90, 0x82, 0xb4, 0xa6, 0xd8, 0xca, 0xfc, 0xee,
    0x32, 0x20, 0x16, 0x04, 0x7a, 0x68, 0x5e, 0x4c, 0xa2, 0xb0, 0x86, 0x94, 0xea, 0xf8, 0xce, 0xdc,
    0x64, 0x76, 0x40, 0x52, 0x2c, 0x3e, 0x08, 0x1a, 0xf4, 0xe6, 0xd0, 0xc2, 0xbc, 0xae, 0x98, 0x8a,
    0x56, 0x44, 0x72, 0x60, 0x1e, 0x0c, 0x3a, 0x28, 0xc6, 0xd4, 0xe2, 0xf0, 0x8e, 0x9c, 0xaa, 0xb8,
    0xc8, 0xda, 0xec, 0xfe, 0x80, 0x92, 0xa4, 0xb6, 0x58, 0x4a, 0x7c, 0x6e, 0x10, 0x02, 0x34, 0x26,
    0xfa, 0xe8, 0xde, 0xcc, 0xb2, 0xa0, 0x96, 0x84, 0x6a, 0x78, 0x4e, 0x5c, 0x22, 0x30, 0x06, 0x14,
    0xac, 0xbe, 0x88, 0x9a, 0xe4, 0xf6, 0xc0, 0xd2, 0x3c, 0x2e, 0x18, 0x0a, 0x74, 0x66, 0x50, 0x42,
    0x9e, 0x8c, 0xba, 0xa8, 0xd6, 0xc4, 0xf2, 0xe0, 0x0e, 0x1c, 0x2a, 0x38, 0x46, 0x54, 0x62, 0x70,
    0x82, 0x90, 0xa6, 0xb4, 0xca, 0xd8, 0xee, 0xfc, 0x12, 0x00, 0x36, 0x24, 0x5a, 0x48, 0x7e, 0x6c,
    0xb0, 0xa2, 0x94, 0x86, 0xf8, 0xea, 0xdc, 0xce, 0x20, 0x32, 0x04, 0x16, 0x68, 0x7a, 0x4c, 0x5e,
    0xe6, 0xf4, 0xc2, 0xd0, 0xae, 0xbc, 0x8a, 0x98, 0x76, 0x64, 0x52, 0x40, 0x3e, 0x2c, 0x1a, 0x08,
    0xd4, 0xc6, 0xf0, 0xe2, 0x9c, 0x8e, 0xb8, 0xaa, 0x44, 0x56, 0x60, 0x72, 0x0c, 0x1e, 0x28, 0x3a,
    0x4a, 0x58, 0x6e, 0x7c, 0x02, 0x10, 0x26, 0x34, 0xda, 0xc8, 0xfe, 0xec, 0x92, 0x80, 0xb6, 0xa4,
    0x78, 0x6a, 0x5c, 0x4e, 0x30, 0x22, 0x14, 0x06, 0xe8, 0xfa, 0xcc, 0xde, 0xa0, 0xb2, 0x84, 0x96,
    0x2e, 0x3c, 0x0a, 0x18, 0x66, 0x74, 0x42, 0x50, 0xbe, 0xac, 0x9a, 0x88, 0xf6, 0xe4, 0xd2, 0xc0,
    0x1c, 0x0e, 0x38, 0x2a, 0x54, 0x46, 0x70, 0x62, 0x8c, 0x9e, 0xa8, 0xba, 0xc4, 0xd6, 0xe0, 0xf2,
];

/// Simple function that calculates a crc7 from a slice of data
pub fn calculate_crc7(data: &[u8]) -> u8 {
    let mut crc: u8 = 0;

    for byte in data {
        // Get the index of the next crc
        let index = byte ^ crc;

        crc = CRC7_TABLE[index as usize];
    }

    crc >> 1 // The least significant bit is not used, get rid of it
}

/// Possible commands to give to the SD card
#[derive(PartialEq)]
pub enum SdCmd {
    /// CMD0: GO_IDLE_STATE, R0
    GoIdleState,
    /// CMD2: ALL_SEND_CID, R2.
    /// CMD3: SEND_RELATIVE_ADDR, R6.
    /// CMD6: SWITCH_FUNC, R1
    /// CMD7: SELECT_DESELECT_CARD, R1b.
    /// CMD8: SEND_IF_COND, R7.
    /// CMD9: SEND_CSD, R1.
    /// CMD10: SEND_CID, R1.
    /// CMD12: STOP_TRANSMISSION, R1b.
    /// CMD13: SEND_STATUS, R2.
    /// CMD16: SET_BLOCKLEN, R1.
    /// CMD17: READ_SINGLE_BLOCK, R1.
    /// CMD18: READ_MULTIPLE_BLOCK, R1.
    /// CMD24: WRITE_BLOCK, R1.
    /// CMD25: WRITE_MULTIPLE_BLOCK, R1.
    /// CMD27: PROGRAM_CSD, R1.
    /// CMD32: ERASE_WR_BLK_START, R1.
    /// CMD33: ERASE_WR_BLK_END, R1.
    /// CMD38: ERASE, R1b.
    /// CMD55: APP_CMD, R1. **DO NOT USE.** APP_CMD is automatically sent before any ACMD.
    /// Supply the RCA with this command
    AppCmd(u16),
    /// CMD56: GEN_CMD
    /// ACMD6: SET_BUS_WIDTH
    /// ACMD13: SD_STATUS
    /// ACMD22: SEND_NUM_WR_BLOCKS
    /// ACMD23: SET_WR_BLK_ERASE_COUNT
    /// ACMD41: SD_APP_OP_COND
    /// ACMD42: SET_CLR_CARD_DETECT
    /// ACMD51: SEND_SCR
    SendScr,
}

impl SdCmd {
    /// Get the index of a command
    pub fn get_cmd_index(&self) -> u8 {
        match self {
            SdCmd::GoIdleState => 0,
            SdCmd::SendScr => 51,
            SdCmd::AppCmd(_) => 55,
        }
    }

    /// Get the response type of a command
    pub fn get_cmd_response(&self) -> SdCmdResponse {
        match self {
            SdCmd::GoIdleState => SdCmdResponse::R0,
            SdCmd::SendScr |
                SdCmd::AppCmd(_) => SdCmdResponse::R1,
        }
    }

    /// Returns true if a command is an app command
    pub fn is_acmd(&self) -> bool {
        match self {
            SdCmd::GoIdleState |
                SdCmd::AppCmd(_) => false,
            SdCmd::SendScr => true,
        }
    }

    /// Format command as 8 bytes. For use with send_command
    pub fn format(&self) -> [u32; 2] {
        let mut data: [u8; 8] = [0; 8];

        // The SDIO PIO we're using requires the length of the command to be
        // specified in bits. This will be the first byte.
        // !TODO! since there are no commands to my knowledge that are *not*
        // 48 bits, find some way to remove this
        data[0] = 48 - 1;

        // Next 6 bytes are the command
        // The second byte is the command index or'd with bit 7 set
        data[1] = self.get_cmd_index() | 0b0100_0000;

        // The next 4 bytes include the argument
        let argument: [u8; 4] = match self {
            // RCA the first 2 bytes,
            Self::AppCmd(rca) => {
                let rca_bytes = rca.to_be_bytes();
                [rca_bytes[0], rca_bytes[1], 0, 0]
            }
            // No argument
            Self::GoIdleState|
               Self::SendScr => [0; 4],
        };

        data[2..6].clone_from_slice(&argument);

        // The next byte is a crc7 of all the command bytes excluding the crc
        let crc = calculate_crc7(&data[1..6]);

        // Also add the end bit(always 1)
        data[6] = (crc << 1) | 0b0000_0001;

        // Lastly, specify the length of the response
        data[7] = self.get_cmd_response().get_response_len();

        // Convert the data array into a le u32
        let word_0: u32 = 0x2f_40_00_00;
        let word_1: u32 = 0x00_CD_00_00;

        [word_0, word_1]
    }
}

/// Possible response types for SD commands
#[derive(PartialEq)]
pub enum SdCmdResponse {
    /// R0, no response
    R0,
    /// R1, normal response
    R1,
    /// R1b, normal response with busy
    R1b,
    /// R2, CID/CSD register
    R2,
    /// R3, OCR register
    R3,
    /// R6, Published RCA response
    R6,
    /// R7, Card interface condition
    R7,
}

impl SdCmdResponse {
    /// Get the length of the response in bits
    pub fn get_response_len(&self) -> u8 {
        match self {
            SdCmdResponse::R0 => 0,
            SdCmdResponse::R1
            | SdCmdResponse::R1b
            | SdCmdResponse::R3
            | SdCmdResponse::R6
            | SdCmdResponse::R7 => 48,
            SdCmdResponse::R2 => 136,
        }
    }
}

/// SDIO 4bit interface struct
pub struct Sdio4bit<P: PIOExt> {
    /// PIO struct, can be PIO0 or PIO1. programs are installed to this.
    pio: PIO<P>,
    /// Reference to the processor's delay struct, used for timing purposes
    delay: Delay,
    /// The command state machine, controls SD_CLK and SD_CMD
    sm_cmd: StateMachine<(P, SM0), Running>,
    sm_cmd_rx: Rx<(P, SM0)>,
    sm_cmd_tx: Tx<(P, SM0)>,
    // The data state machine, controls SD_DAT0-SD_DAT3
    // sm_dat: StateMachine<(P, SM1), Running>,
    // sm_dat_rx: Rx<(P, SM1)>,
    // sm_dat_tx: Tx<(P, SM1)>,
}

impl<P: PIOExt> Sdio4bit<P> {
    pub fn new(
            mut pio: PIO<P>,
            mut delay: Delay,
            sm0: UninitStateMachine<(P, SM0)>,
            sm1: UninitStateMachine<(P, SM1)>,
            sd_clk_id: u8,
            sd_cmd_id: u8,
            sd_dat0_id: u8,
            sd_dat1_id: u8,
            sd_dat2_id: u8,
            sd_dat3_id: u8) -> Self {
        // Initialilze the raw program variables from the rp2040_sdio.pio file
        let program_sdio_cmd_clk =
            pio_file!("src/rp2040_sdio.pio", select_program("sdio_cmd_clk")).program;
        // let program_sdio_data_rx =
        //     pio_file!("src/rp2040_sdio.pio", select_program("sdio_data_rx")).program;
        // let program_sdio_data_tx =
        //     pio_file!("src/rp2040_sdio.pio", select_program("sdio_data_tx")).program;

        // Install them to the pio
        let program_sdio_cmd_clk = pio.install(&program_sdio_cmd_clk).unwrap();
        // let program_sdio_data_rx = pio.install(&program_sdio_data_rx).unwrap();
        // let program_sdio_data_tx = pio.install(&program_sdio_data_tx).unwrap();

        let (mut sm_cmd, sm_cmd_rx, sm_cmd_tx) = PIOBuilder::from_program(program_sdio_cmd_clk)
            .set_mov_status_config(MovStatusConfig::Tx(2))
            .set_pins(sd_cmd_id, 1)
            .out_pins(sd_cmd_id, 1)
            .in_pin_base(sd_cmd_id)
            .jmp_pin(sd_cmd_id)
            .side_set_pin_base(sd_clk_id)
            .out_shift_direction(ShiftDirection::Left)
            .in_shift_direction(ShiftDirection::Left)
            .clock_divisor_fixed_point(25, 0)
            .autopush(true)
            .autopull(true)
            .build(sm0);

        sm_cmd.set_pindirs([(sd_clk_id, PinDir::Output), (sd_cmd_id, PinDir::Output)]);
        // Start the state machine
        let sm_cmd = sm_cmd.start();

        Self {
            pio,
            delay,
            sm_cmd,
            sm_cmd_rx,
            sm_cmd_tx,
        }
    }

    /// Initialize the SD card
    pub fn init(&mut self) {
        // Wait 1ms to ensure that the card is properly initialized
        self.delay.delay_ms(1);

        // Send CMD0
        loop {
            self.send_command(SdCmd::GoIdleState);
            self.delay.delay_us(50);
        }
    }

    pub fn send_command(&mut self, command: SdCmd) {
        // If the command is an app command, first send the AppCmd command
        if command.is_acmd() {
            self.send_command(SdCmd::AppCmd(0x0000));
        }

        // Get the data for the command
        let command_data = command.format();

        // Push both words into tx
        self.sm_cmd.drain_tx_fifo();
        self.sm_cmd_tx.write(0x2f_40_00_00); // CMD0 in int
        self.sm_cmd_tx.write(0x00_CD_00_00);

        // If there is no response, return
        if command.get_cmd_response() == SdCmdResponse::R0 {
            return;
        }
    }
}
