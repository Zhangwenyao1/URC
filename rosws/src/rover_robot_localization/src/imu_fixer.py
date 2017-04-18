#!/usr/bin/python
import sensor_msgs.msg, sensor_msgs
import rospy

def imu_fixer(data):
    """
    :type data: sensor_msgs.msg.Imu
    """

    # Convert linear acceleration units from magnitude of G's to m/s squared
    data.linear_acceleration.x = data.linear_acceleration.x * 9.8
    data.linear_acceleration.y = data.linear_acceleration.y * 9.8
    data.linear_acceleration.z = data.linear_acceleration.z * 9.8

    ## SET COVARIANCES
    # Convert tuples to mutable arrays
    linear_acceleration_covariance = list(data.linear_acceleration_covariance)
    angular_velocity_covariance = list(data.angular_velocity_covariance)
    orientation_covariance = list(data.orientation_covariance)
    # Set covariances to what was found in the gazebo simulation of the Clearpath Jackal IMU
    linear_acceleration_covariance[0] = 0.000025
    linear_acceleration_covariance[4] = 0.000025
    linear_acceleration_covariance[8] = 0.000025
    angular_velocity_covariance[0] = 0.000025
    angular_velocity_covariance[4] = 0.000025
    angular_velocity_covariance[8] = 0.000025
    orientation_covariance[0] = 0.00000026
    orientation_covariance[4] = 0.00000026
    data.linear_acceleration_covariance = linear_acceleration_covariance
    data.angular_velocity_covariance = angular_velocity_covariance
    data.orientation_covariance = orientation_covariance

    imu_fixed_publisher.publish(data)

if __name__ == "__main__":
    rospy.init_node("imu_fixer")

    imu_fixed_publisher = rospy.Publisher('/imu/data_fixed', sensor_msgs.msg.Imu, queue_size=1)
    bad_pointcloud = rospy.Subscriber('/imu/data', sensor_msgs.msg.Imu, callback=imu_fixer, queue_size=1)
    rospy.spin()