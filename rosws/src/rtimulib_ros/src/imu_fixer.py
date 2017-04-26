#!/usr/bin/python
import rospy
import tf_conversions

from geometry_msgs.msg import Vector3
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32


def imu_fixer(data):
    """
    :type data: sensor_msgs.msg.Imu
    """

    # Convert linear acceleration units from magnitude of G's to m/s squared
    #data.linear_acceleration.x = data.linear_acceleration.x * 10 # doesn't seem like this is needed
    #data.linear_acceleration.y = data.linear_acceleration.y * 10
    data.linear_acceleration.z = data.linear_acceleration.z * 10 # 10 seems to get an end result closer to 9.8m/s

    ## SET COVARIANCES
    # Convert tuples to mutable arrays
    linear_acceleration_covariance = list(data.linear_acceleration_covariance)
    angular_velocity_covariance = list(data.angular_velocity_covariance)
    orientation_covariance = list(data.orientation_covariance)
    # Set covariances to what was found in the gazebo simulation of the Clearpath Jackal IMU
    linear_acceleration_covariance[0] = 0.0025
    linear_acceleration_covariance[4] = 0.0025
    linear_acceleration_covariance[8] = 0.0025
    angular_velocity_covariance[0] = 0.0025
    angular_velocity_covariance[4] = 0.0025
    angular_velocity_covariance[8] = 0.0025
    orientation_covariance[0] = 0.000026
    orientation_covariance[4] = 0.0026
    orientation_covariance[8] = 0.0026
    data.linear_acceleration_covariance = linear_acceleration_covariance
    data.angular_velocity_covariance = angular_velocity_covariance
    data.orientation_covariance = orientation_covariance

    imu_fixed_publisher.publish(data)

    # Publish roll pitch yaw
    quaternion = [data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w]
    euler_tuple = tf_conversions.transformations.euler_from_quaternion(quaternion)
    euler_vector = Vector3(euler_tuple[0], euler_tuple[1], euler_tuple[2])
    roll_pitch_yaw_publisher.publish(euler_vector)


if __name__ == "__main__":
    rospy.init_node("imu_fixer")

    imu_fixed_publisher = rospy.Publisher('/imu/data_fixed', Imu, queue_size=1)
    roll_pitch_yaw_publisher = rospy.Publisher('/imu/roll_pitch_yaw', Vector3, queue_size=1)

    imu_subscriber = rospy.Subscriber('/imu/data_raw', Imu, callback=imu_fixer, queue_size=1)

    rospy.spin()
