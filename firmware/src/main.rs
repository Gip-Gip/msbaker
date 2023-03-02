//! Main functions and other top-level code needed to operate

#![no_std]
#![no_main]

use rp2040_hal as hal;

use core::panic::PanicInfo;
use hal::pac;

use embedded_hal::blocking::i2c::WriteRead;
use fugit::RateExtU32;

use embedded_hal::digital::v2::OutputPin;
use rp2040_hal::clocks::Clock;

#[link_section = ".boot2"]
#[used]
pub static BOOT2: [u8; 256] = rp2040_boot2::BOOT_LOADER_GENERIC_03H;

const XTAL_FREQ_HZ: u32 = 12_000_000u32;
const IMU_ADDR: u8 = 0b1101010;
const IMU_CHECK_REG: u8 = 0x0F;
const IMU_CHECK_VAL: u8 = 0b01101100;

/// Core 0 main function, the entrypoint for our code
/// Everything starts here!
#[rp2040_hal::entry]
fn main_0() -> ! {
    // ===================================================================== //
    // STEP 1, INITIALIZATION!                                               //
    // ===================================================================== //
    let mut pac = pac::Peripherals::take().unwrap();
    let core = pac::CorePeripherals::take().unwrap();

    let mut watchdog = hal::Watchdog::new(pac.WATCHDOG);

    let clocks = hal::clocks::init_clocks_and_plls(
        XTAL_FREQ_HZ,
        pac.XOSC,
        pac.CLOCKS,
        pac.PLL_SYS,
        pac.PLL_USB,
        &mut pac.RESETS,
        &mut watchdog,
    )
    .ok()
    .unwrap();

    let sio = hal::Sio::new(pac.SIO);

    let pins = hal::gpio::Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    // Initialize GPIO
    let mut pin_led = pins.gpio25.into_push_pull_output();
    // Initialize the I2C1 line
    // !TODO! says it's I2C0 on the schematic, figure out why
    let pin_i2c1_sda = pins.gpio6.into_mode::<hal::gpio::FunctionI2C>();
    let pin_i2c1_scl = pins.gpio7.into_mode::<hal::gpio::FunctionI2C>();
    let mut i2c1 = hal::I2C::i2c1(
        pac.I2C1,
        pin_i2c1_sda,
        pin_i2c1_scl,
        400.kHz(),
        &mut pac.RESETS,
        &clocks.system_clock,
    );

    // ===================================================================== //
    // STEP 1.1, SELF CHECKS!                                                //
    // ===================================================================== //

    // Check the IMU
    let mut response: [u8; 1] = [0; 1];
    // Remember you have to write to i2c to read from i2c...
    i2c1.write_read(IMU_ADDR, &[IMU_CHECK_REG], &mut response)
        .unwrap();

    if response[0] != IMU_CHECK_VAL {
        panic!("IMU NOT OK!");
    }

    // !TODO! Self check for sd card

    // !TODO! Initialize core 1

    // ===================================================================== //
    // STEP 2, WAIT!                                                         //
    // ===================================================================== //

    // Turn the LED solid to signify all is good!
    pin_led.set_high().unwrap();

    loop {
        cortex_m::asm::wfi();
    }
}

/// Core 1 main function, called by core 0
fn main_1() {
    todo!()
}

#[panic_handler]
fn panic(_: &PanicInfo) -> ! {
    loop {}
}
