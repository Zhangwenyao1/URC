#!/usr/bin/env python
import serial
import struct
import rospy
import time
import std_msgs.msg
import std_srvs.srv
import rover_science.srv

s = serial.Serial(port="/dev/ttyACM0", baudrate=38400)

# >>>>>>> 1a396af84aee11c31531639724103fc760b585a8 lazy
rospy.init_node("science_serial")
sensor_names = ("ph", "temp", "humid")
pub = {n: rospy.Publisher("/science/" + name, std_msgs.msg.Float32, queue_size=10) for n, name in zip((0, 1, 2), sensor_names)}


# CAROUSEL CONTROL
def move_to_funnel(request):
    data = struct.pack("<BB", 0x00, request.index)
    s.write(data)
    rospy.loginfo('Move %s to funnel' % request.index)
#<<<<<<< HEAD
#    timeout = time.time() + 16   # 10 seconds from now
#    while True:
#        if s.in_waiting > 0:
#            data = s.read(1)
#            rospy.loginfo('Response from arduino %s!' % data)
#            return rover_science.srv.CarouselResponse(success=True)
#        if time.time() > timeout:
#            rospy.logerr('Timeout exceeded!')
# 
#           return rover_science.srv.CarouselResponse(success=False)
#        ti
#=======
    # timeout = time.time() + 10   # 10 seconds from now
    # while True:
    #     if s.in_waiting:
    #         data = s.read(1)
    #         rospy.loginfo('Response from arduino %s!' % data)
    #         return rover_science.srv.CarouselResponse(success=True)
    #     if time.time() > timeout:
    #         rospy.logerr('Timeout exceeded!')
    #         return rover_science.srv.CarouselResponse(success=False)
    #     time.sleep(1)
    return rover_science.srv.CarouselResponse(success=True)
#>>>>>>> 1a396af84aee11c31531639724103fc760b585a8

def move_to_ph(request):
    data = struct.pack("<BB", 0x01, request.index)
    s.write(data)
    rospy.loginfo('Move %s to ph' % request.index)
    # timeout = time.time() + 10   # 10 seconds from now
    # while True:
    #     if s.in_waiting:
    #         data = s.read(1)
    #         rospy.loginfo('Response from arduino %s!' % data)
    #         return rover_science.srv.CarouselResponse(success=True)
    #     if time.time() > timeout:
    #         rospy.logerr('Timeout exceeded!')
    #         return rover_science.srv.CarouselResponse(success=False)
    #     time.sleep(1)
    return rover_science.srv.CarouselResponse(success=True)

to_funnel_service = rospy.Service("/science/carousel/funnel", rover_science.srv.Carousel, move_to_funnel)
rospy.loginfo('Initialized service /science/carousel/funnel')
to_ph_service = rospy.Service("/science/carousel/ph", rover_science.srv.Carousel, move_to_ph)
rospy.loginfo('Initialized service /science/carousel/ph')

# ETHANOL probe CONTROL (Open/Close)
def open_tube(request):
    data = struct.pack("<B", 0x02)
    s.write(data)
    rospy.loginfo('Open tube')
    return std_srvs.srv.EmptyResponse()

open_tube_service = rospy.Service("/science/tube/open", std_srvs.srv.Empty, open_tube)
rospy.loginfo('Initialized service /science/tube/open')

def close_tube(request):
    data = struct.pack("<B", 0x03)
    s.write(data)
    rospy.loginfo('Close tube')
    return std_srvs.srv.EmptyResponse()

close_tube_service = rospy.Service("/science/tube/close", std_srvs.srv.Empty, close_tube)
rospy.loginfo('Initialized service /science/tube/close')

# PROBE CONTROL (Up/Down)
def probe_up(request):
    data = struct.pack("<B", 0x04)
    s.write(data)
    rospy.loginfo('Probe up')
    return std_srvs.srv.EmptyResponse()

probe_up_service = rospy.Service("/science/probe/up", std_srvs.srv.Empty, probe_up)
rospy.loginfo('Initialized service /science/probe/up')

def probe_down(request):
    data = struct.pack("<B", 0x05)
    s.write(data)
    rospy.loginfo('Probe down')
    return std_srvs.srv.EmptyResponse()

probe_down_service = rospy.Service("/science/probe/down", std_srvs.srv.Empty, probe_down)
rospy.loginfo('Initialized service /science/probe/down')

# PUMP CONTROL (On/Off)
def pump_on(request):
    data = struct.pack("<B", 0x06)
    s.write(data)
    rospy.loginfo('Pump on')
    return std_srvs.srv.EmptyResponse()

pump_on_service = rospy.Service("/science/pump/on", std_srvs.srv.Empty, pump_on)
rospy.loginfo('Initialized service /science/pump/on')

def pump_off(request):
    data = struct.pack("<B", 0x07)
    s.write(data)
    rospy.loginfo('Pump off')
    return std_srvs.srv.EmptyResponse()

pump_off_service = rospy.Service("/science/pump/off", std_srvs.srv.Empty, pump_off)
rospy.loginfo('Initialized service /science/pump/off')

while not rospy.is_shutdown():
    if s.in_waiting < 1:
        time.sleep(0.33)
    else:
        t = s.read(1)
        if ord(t) in (0, 1, 2):
            v = struct.unpack("<f", s.read(4))[0]
            rospy.loginfo("Data {} Value {}".format(sensor_names[ord(t)], v))
            pub[ord(t)].publish(v)
        else:
            rospy.logerr("Bad data! %s " % t)

