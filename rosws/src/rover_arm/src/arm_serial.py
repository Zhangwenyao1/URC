from Queue import Queue
import actionlib
import threading
import control_msgs.msg
import trajectory_msgs.msg
import rospy
import time
import struct
import serial

JOINT_ORDERINGS = {
    4: [
        "shoulder",
        "elbow",
        "lower_elbow",
        "hip"
    ],
    2: [
        "grip_twist",
        "grip"
    ]
}


class SerialCommunicator(threading.Thread):
    def __init__(self, prt, new_waypoint_cb,):
        """

        :type prt: serial.Serial
        """
        super(SerialCommunicator, self).__init__()
        self.is_aborting = False
        self.serial_p = prt
        self.done_waypoint_cb = new_waypoint_cb
        self.waypoint_queue = Queue()

    def _send_waypoint_message(self, waypoint, joint_names):
        # type: (trajectory_msgs.msg.JointTrajectory) -> None
        n_joints = len(joint_names)
        joint_positions = []
        for pub_joint in JOINT_ORDERINGS[n_joints]:
            ind = joint_names.index(pub_joint)
            joint_positions.append(waypoint.positions[ind])
        fmtstr = "<bxx" + "fx" * n_joints
        packed = struct.pack(fmtstr, 1 if n_joints == 4 else 3, *joint_positions)
        self.serial_p.write(packed)

    def abort(self):
        self.is_aborting = True

    def _read_status(self):
        n_joints = len(JOINT_ORDERINGS)
        fmtstr = "<bxx"
        typ = self.serial_p.read(struct.calcsize(fmtstr))
        if typ == 2:
            self.abort()
            return
        else:
            fmtstr = "<" + "fx" * (4 if typ == 1 else 2)
        data = struct.unpack(fmtstr, data)
        self.done_waypoint_cb(False, data)

    def run(self):
        while True:
            next_waypoint = self.waypoint_queue.get()
            self._send_waypoint_message(next_waypoint[1], next_waypoint[0])
            got_response = False
            l = next_waypoint[0]
            while not got_response:
                if self.serial_p.in_waiting > 0:  
                    time.sleep(0.5)
                    self._read_status()
                    got_response = True
                if self.is_aborting:
                    self.waypoint_queue = Queue()
                    self._send_abort()
                    got_response = True
                    self.is_aborting = False

    def _send_abort(self):
        self.serial_p.write('\x02\x00\x00')


class ArmActionServer:
    def __init__(self, serial_):
        self.as_arm = actionlib.SimpleActionServer("arm_controller/follow_joint_trajectory",
                                                   control_msgs.msg.FollowJointTrajectoryAction,
                                                   auto_start=False)
        self._feedback_message = control_msgs.msg.FollowJointTrajectoryActionFeedback()
        self._result_message = control_msgs.msg.FollowJointTrajectoryActionResult()
        self.serial_thread = SerialCommunicator(serial_, self._next_waypoint)

        self.as_arm.register_goal_callback(lambda: self.goal_callback())
        self.as_arm.register_preempt_callback(lambda: self.preempt_callback())

    def _next_waypoint(self, stopped, joints):
        pass

    def goal_callback(self):
        pass

    def preempt_callback(self):
        self.serial_thread.abort()



