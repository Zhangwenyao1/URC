#!/usr/bin/env python

#Basic imports
# from ctypes import *
import sys
import math
import rospy

from sensor_msgs.msg import Imu, MagneticField

class Compass():
    def __init__(self):
        self.last_angles = [0,0,0]              # The last set of bearing angles
        self.compass_bearing_filter = []        # bearing store for filtering
        self.bearing_filter_size = 10           # Max size of bearing store
        self.compass_bearing = 0                # Init bearing value
        self.linear_acceleration = (0,0,0)      # Latest measurement (x, y, z)
        self.mag_field = (0,0,0)                # Latest measurement (x, y, z)

    def CalculateBearing(self):
        """
        Calculates a bearing value using the accelerometer and magnetometer
        """
        angles = []
        gravity = self.linear_acceleration
        mag_field = self.mag_field
        
        # Roll angle about axis 0
        # tan(roll angle) = gy/gz
        # Atan2 gives us output as (-180 - 180) deg
        roll_angle = math.atan2(gravity[1], gravity[2])
        
        # Pitch Angle - about axis 1
        # tan(pitch angle) = -gx / ((gy * sin(roll angle)) + (gz * cos(roll angle)))
        # Pitch angle range is (-90 - 90) degrees
        pitch_angle = math.atan( -gravity[0] / (gravity[1] * math.sin(roll_angle) + gravity[2] * math.cos(roll_angle)))
        
        # Yaw Angle - about axis 2
        # tan(yaw angle) = (mz * sin(roll) \96 my * cos(roll)) / 
        #                   (mx * cos(pitch) + my * sin(pitch) * sin(roll) + mz * sin(pitch) * cos(roll))
        #      Use Atan2 to get our range in (-180 - 180)
           
        #  Yaw angle == 0 degrees when axis 0 is pointing at magnetic north
        yaw_angle = math.atan2( mag_field[2] * math.sin(roll_angle) - mag_field[1] * math.cos(roll_angle),
                mag_field[0] * math.cos(pitch_angle) + mag_field[1] * math.sin(pitch_angle) * math.sin(roll_angle) + mag_field[2] * math.sin(pitch_angle) * math.cos(roll_angle))                                         
        
        # Add angles to our list
        angles.append(roll_angle)
        angles.append(pitch_angle)
        angles.append(yaw_angle)
        
        # This is our low pass filter to make the values look nicer on screen
        # Make sure the filter bugger doesn't have values passing the -180<->180 mark
        # This only applies to the Roll and Yaw - Pitch will never have a sudden switch like that
        for i in xrange(0,3,2):
            
            if( math.fabs( angles[i] - self.last_angles[i] > 3 )):
                
                for stuff in self.compass_bearing_filter:
                    
                    if(angles[i] > self.last_angles[i]):
                        stuff[i] += 360 * math.pi / 180.0
                    else:
                        stuff[i] -= 360 * math.pi / 180.0
                        
        self.last_angles = angles
        
        self.compass_bearing_filter.append(angles)
        
        if(len(self.compass_bearing_filter) > self.bearing_filter_size):
            self.compass_bearing_filter.pop(0)
            
        yaw_angle = pitch_angle = roll_angle = 0
        
        for stuff in self.compass_bearing_filter:
            roll_angle += stuff[0]
            pitch_angle += stuff[1]
            yaw_angle += stuff[2]
            
        yaw_angle = yaw_angle / len(self.compass_bearing_filter)
        pitch_angle = pitch_angle / len(self.compass_bearing_filter)
        roll_angle = roll_angle / len(self.compass_bearing_filter)
        
        # Convert radians to degrees for display
        self.compass_bearing = yaw_angle * (180.0 / math.pi)
        
        # Set a directional string (one of 8 compass directions
        # based on the angle i.e. North, North-East, South-West etc.
        # Split by checking main 4 compass point angles +/- 22.5 deg
        
        string_bearing = None
        if(self.compass_bearing >=0 and self.compass_bearing < 22.5 ):
            string_bearing = "North: "
        elif(self.compass_bearing >=22.5 and self.compass_bearing < 67.5 ):
            string_bearing = "North East: "
        elif(self.compass_bearing >=67.5 and self.compass_bearing < 112.5 ):
            string_bearing = "East: "
        elif(self.compass_bearing >=112.5 and self.compass_bearing < 157.5 ):
            string_bearing = "South East: "
        elif(self.compass_bearing >=157.5 and self.compass_bearing <= 180 ):
            string_bearing = "South: "
        elif(self.compass_bearing <= -157.5 and self.compass_bearing > -180 ):
            string_bearing = "South: "
        elif(self.compass_bearing <= -112.5 and self.compass_bearing > -157.5 ):
            string_bearing = "South West: "
        elif(self.compass_bearing <= -67.5 and self.compass_bearing > -112.5 ):
            string_bearing = "West: "
        elif(self.compass_bearing <= -22.5 and self.compass_bearing > -67.5 ):
            string_bearing = "North West: "
        elif(self.compass_bearing <= 0.0 and self.compass_bearing > -22.5 ):
            string_bearing = "North: "
        else:
            return
        
        # Add the actual bearing value to the string then print
        string_bearing = string_bearing + " %.1f" % self.compass_bearing
        print string_bearing

compass = Compass()

def imu_callback(data, compass):
    compass.linear_acceleration = (data.linear_acceleration.x,
                                   data.linear_acceleration.y,
                                   data.linear_acceleration.z)
    compass.CalculateBearing()

def mag_callback(data, compass):
    compass.mag_field = (data.magnetic_field.x,
                         data.magnetic_field.y,
                         data.magnetic_field.z)
    compass.CalculateBearing()


if __name__ == "__main__":
    compass = Compass()

    rospy.init_node("compass")

    imu_subscriber = rospy.Subscriber('/imu/mag', MagneticField, mag_callback, compass, queue_size=1)
    imu_subscriber = rospy.Subscriber('/imu/data_raw', Imu, imu_callback, compass, queue_size=1)

    rospy.spin()
