//! Used to store and compute the telemetry available on a stock Ms. Baker

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
