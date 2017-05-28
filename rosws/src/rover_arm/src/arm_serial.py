#!/usr/bin/env python
import actionlib
import control_msgs.msg
import trajectory_msgs.msg
import std_msgs.msg
import rospy
import struct
import serial
import time

JOINT_ORDERINGS = {
    4: [
        "shoulder",
        "elbow",
        "lower_elbow",
        "hip"
    ],
}


MOTION_TIMELIMIT = 0.7


class ArmActionServer:
    def __init__(self, serial_):
        serial_ = serial_ # type: serial.Serial
        self.as_arm = actionlib.SimpleActionServer("/arm_controller/follow_joint_trajectory",
                                                   control_msgs.msg.FollowJointTrajectoryAction,
                                                   auto_start=False)
        self._feedback_message = control_msgs.msg.FollowJointTrajectoryFeedback()
        self._result_message = control_msgs.msg.FollowJointTrajectoryResult()
        self._goal = control_msgs.msg.FollowJointTrajectoryGoal()

        self.as_arm.register_goal_callback(lambda: self.goal_callback())
        self.as_arm.register_preempt_callback(lambda: self.preempt_callback())
        self.serial = serial_
        self.is_preempt = False
        self.ltime = time.time()

        self.as_arm.start()

    def goal_callback(self):
        self._goal = self.as_arm.accept_new_goal()  # type: control_msgs.msg.FollowJointTrajectoryGoal
        rospy.loginfo("GOT NEW GOAL!!!!")
        if len(self._goal.trajectory.joint_names) != 4:
            self.as_arm.set_aborted(None, "Bad joints")
            return
        indicies = [self._goal.trajectory.joint_names.index(x) for x in JOINT_ORDERINGS[4]]
        for setpoint in self._goal.trajectory.points:
            pts = setpoint.positions
            self.ltime = time.time()
            rospy.loginfo("Sending setpoint: " + str(pts))
            if self.is_preempt:
                self.as_arm.set_preempted(None, "Preempt")
                self.is_preempt = False
                self._send_abort()
                return
            a, b, c, d = pts[indicies[0]], pts[indicies[1]], pts[indicies[2]], pts[indicies[3]]
            self.serial.write("\x01" + struct.pack("<ffff", a, b, c, d))
            rospy.loginfo("Sent command")
            if self._wait_response():
                if self.is_preempt:
                    self.as_arm.set_preempted(None, "Preempt")
                    self.is_preempt = False
                    self._send_abort()
                    return
                rospy.loginfo("Got feedback! Next setpoint")
                self._feedback_message.joint_names = self._goal.trajectory.joint_names
                self._feedback_message.desired = setpoint
                self._feedback_message.actual = setpoint
                self._feedback_message.error = trajectory_msgs.msg.JointTrajectoryPoint(positions=[0,0,0,0],velocities=[0,0,0,0],accelerations=[0,0,0,0],effort=[0,0,0,0],time_from_start=setpoint.time_from_start)
                self.as_arm.publish_feedback(self._feedback_message)
                continue
            else:
                if self.is_preempt:
                    self.as_arm.set_preempted(None, "Preempt")
                    self.is_preempt = False
                    self._send_abort()
                    return
                self.as_arm.set_aborted(None, "Aborted")
                rospy.logerr("Failed!")
                return
        rospy.loginfo("Done!")
        self._send_finish()
        self._result_message.error_code = self._result_message.SUCCESSFUL
        self.as_arm.set_succeeded(self._result_message, "Done!")
        return

    def preempt_callback(self):
        self.is_preempt = True

    def _wait_response(self):
        while True:
            if self.is_preempt:
                return False
            elif time.time() - self.ltime > MOTION_TIMELIMIT:
                return False
            elif self.serial.in_waiting < 1:
                continue
            else:
                d = self.serial.read(1)
                if d[0] == 0x01:
                    return True
                else:
                    return False

    def _send_abort(self):
        self.serial.write('\x02')

    def _send_finish(self):
        self.serial.write('\x04')


def new_data(msg):
    direction = msg.data
    d = 0
    if abs(direction) <= 0.2:
        pass
    elif direction > 0:
        d = 1
    else:
        d = -1
    m = "\x05" + struct.pack("<b", d)
    serial_dev.write(m)

rospy.init_node("serial_arm_node")
serial_port = rospy.get_param("~dev","/dev/ttyUSB0")
serial_dev = serial.Serial(port=serial_port, baudrate=9600)
p = rospy.Subscriber("/arm_controller/winch", std_msgs.msg.Float32, callback=new_data, queue_size=10)
as_arm_ = ArmActionServer(serial_dev)
rospy.spin()
