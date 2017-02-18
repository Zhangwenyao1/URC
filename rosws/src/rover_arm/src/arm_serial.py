from Queue import Queue
import actionlib
import threading
import control_msgs.msg
import trajectory_msgs.msg
import rospy
import time
import struct
import serial

JOINT_ORDERINGS = [
    "elbow_lower",
    "elbow_middle",
    "elbow_upper",
    "base_twist",
    "grip",
    "grip_twist"
]


class SerialCommunicator(threading.Thread):
    def __init__(self, prt, new_waypoint_cb, joint_names):
        """

        :type prt: serial.Serial
        """
        super(SerialCommunicator, self).__init__()
        self.is_aborting = False
        self.serial_p = prt
        self.done_waypoint_cb = new_waypoint_cb
        self.waypoint_queue = Queue()
        self.joint_names = joint_names

    def _send_waypoint_message(self, waypoint, joint_names):
        # type: (trajectory_msgs.msg.JointTrajectory) -> None
        n_joints = len(JOINT_ORDERINGS)
        joint_positions = []
        for pub_joint in JOINT_ORDERINGS:
            ind = joint_names.index(pub_joint)
            joint_positions.append(waypoint.positions[ind])
        fmtstr = "<bxx" + "fx" * n_joints
        packed = struct.pack(fmtstr, 1, *joint_positions)
        self.serial_p.write(packed)

    def abort(self):
        self.is_aborting = True

    def _read_status(self):
        n_joints = len(JOINT_ORDERINGS)
        fmtstr = "<" + "fx" * n_joints
        data = self.serial_p.read(struct.calcsize(fmtstr))
        data = struct.unpack(fmtstr, data)
        self.done_waypoint_cb(False, data)

    def run(self):
        while True:
            next_waypoint = self.waypoint_queue.get()
            self._send_waypoint_message(next_waypoint, self.joint_names)
            got_response = False
            while not got_response:
                if self.serial_p.in_waiting > 0:
                    time.sleep(0.5)
                    self._read_status()
                    got_response = True
                if self.is_aborting:
                    self.waypoint_queue = Queue()
                    self._send_abort()
                    got_response = True
                    self.is_aborting = True
                    self.done_waypoint_cb(True, [])

    def _send_abort(self):
        self.serial_p.write('\x02\x00\x00')


class ArmActionServer:
    def __init__(self, serial_):
        self.as_ = actionlib.SimpleActionServer("arm/follow_joint_trajectory",
                                                control_msgs.msg.FollowJointTrajectoryAction,
                                                auto_start=False)
        self._feedback_message = control_msgs.msg.FollowJointTrajectoryActionFeedback()
        self._result_message = control_msgs.msg.FollowJointTrajectoryActionResult()
        self.serial_thread = SerialCommunicator(serial_, self.next_waypoint, JOINT_ORDERINGS)

    def next_waypoint(self):
        pass

    def goal_callback(self):
        pass

    def preempt_callback(self):
        pass

