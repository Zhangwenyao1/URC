import struct

import serial
import time

enable_streamer = "!Sg3C51\r\n"
serial_device = serial.Serial(raw_input("[*] Feed me serial: "), baudrate=115200)
time.sleep(0.6)
serial_device.write(enable_streamer)
time.sleep(0.5)
serial_device.write(enable_streamer)
time.sleep(0.4)
haystack = serial_device.read(serial_device.in_waiting)


def find_needle(haystack):
    for line in haystack.split("\r\n"):
        if line.startswith("!sg"):
            return line
    return None


def read_formatted_uint(dat):
    time.sleep(0.005)

    return int(dat, base=16)


needle = find_needle(haystack)
gyro_dsr = accel_dsr = yaw_offset = 0
if needle:
    print "[*] Got stream response: {}".format(needle)
    gyro_dsr = float(read_formatted_uint(needle[3:8]))
    accel_dsr = float(read_formatted_uint(needle[8:13]))
    yaw_offset = float(needle[15:23])
    print "[*] Extracted: gyro{} accel{} yawoffset{}".format(gyro_dsr, accel_dsr, yaw_offset)
else:
    print "[!] Didn't get stream response! FATAL"
    print haystack
    raise


while True:
    while serial_device.in_waiting > 0:
        cbeg = serial_device.read(1)
        if cbeg != "!":
            continue
        pound = serial_device.read(1)  # #
        if pound != "g":
            continue
        time.sleep(0.05)
        data_buffer = bytes(serial_device.read(51))
        try:
            dataz = []
            for i in range(0, 34, 4):
                dataz.append(struct.unpack("<H", data_buffer[i:i+2])[0])
            print "[*] Got data packet: {}".format(dataz)
            print dataz[0] / (32768.0 / gyro_dsr)
            serial_device.read(4)  # Read csum and rn
            time.sleep(0.1)
        except struct.error:
            print "[!] Malformed packet!"
    else:
        time.sleep(0.05)
