//! Used to store and compute the telemetry available on a stock Ms. Baker

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

#![no_std]

pub struct RawTelemetry {
    /// Time since telemetry collection started(T0), in microseconds
    /// 
    /// !NOTE! this caps the collection time at about 1.19 hours, so
    /// if for some reason you wish to read for longer than that change this
    /// to a u64.
    us_time: u32,
    /// x acceleration in mm/s^2
    mms2_x: i32,
    /// y acceleration in mm/s^2
    mms2_y: i32,
    /// z acceleration in mm/s^2
    mms2_z: i32,
    /// x angular velocity in microradians/s
    urads_x: i32,
    /// y angular velocity in microradians/s
    urads_y: i32,
    /// z angular velocity in microradians/s
    urads_z: i32,
    /// IMU temperature in millicelcius
    mc_imu: i32,
}
