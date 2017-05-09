#!/usr/bin/env python
import rospy
import filesend.msg
import binascii
import pylzma
import os
import std_msgs.msg
import time

rospy.init_node("fsend_recv")

directory = rospy.get_param("~save_to")
if not os.path.exists(directory):
    os.mkdir(directory)

working_on = None
save_to = None
working = False

saved = rospy.Publisher("file_saved", std_msgs.msg.Bool, queue_size=5)


def finish():
    time.sleep(0.5)
    try:
        decompressed = pylzma.decompress(working_on)
    except ValueError, e:
        save_to.close()
        rospy.logerr("Failed to decompress file: {}".format(e.message))
        saved.publish(False)
        return
    save_to.write(decompressed)
    save_to.close()
    saved.publish(True)


def announce(msg):
    global working_on, save_to, working
    if msg.ending and working:
        finish()
        working = False
        working_on = ""
        save_to = None
        rospy.loginfo("Successfully saved file!")
    elif not working and not msg.ending:
        if not os.path.exists(os.path.join(directory, msg.folder)):
            os.makedirs(os.path.join(directory, msg.folder))
        working_on = ""
        save_to = open(os.path.join(directory, msg.folder, msg.filename), "wb")
        rospy.loginfo("Receiving file {}".format(msg.filename))
        working = True
    elif not msg.ending:
        rospy.logwarn("Two file announces came in at once, discarding the second one")
    else:
        saved.publish(False)
        rospy.logwarn("File ended, but I never knew about it or its checksum failed!")


def data(msg):
    global working_on, save_to, working
    if working:
        new_data = msg.data
        crc32_d = binascii.crc32(new_data)
        if crc32_d != msg.crc32:
            rospy.logerr("Failed to verify CRC32 on a chunk. Discarding file")
            save_to.close()
            working = False
        else:
            rospy.loginfo("Got data packet")
            working_on += new_data

announce_sub = rospy.Subscriber("file_announce", filesend.msg.FileBegin, callback=announce, queue_size=10)
data_sub = rospy.Subscriber("file_data", filesend.msg.FileChunk, callback=data, queue_size=1000)

rospy.spin()
