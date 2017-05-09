#!/usr/bin/env python
import os
import actionlib
import filesend.srv
import rospy
import rover_panorama.msg
import rover_panorama.srv
import std_msgs.msg
import std_srvs.srv

rospy.init_node("panorama_orches")
fsend_recv_save_dir = rospy.get_param("~image_save_dir")

take_image = rospy.ServiceProxy("take_image", rover_panorama.srv.TakeImage)
send_file = rospy.ServiceProxy("add_request_queue", filesend.srv.RequestManyFiles)
datawait = False


def fini(b):
    global datawait
    if datawait:
        datawait = False


_fini_sub = rospy.Subscriber("queue_done", std_msgs.msg.Empty, queue_size=5, callback=fini)


class Panorama:
    def __init__(self):
        self.images = []
        self.n = 0
        self.folder = os.path.join(fsend_recv_save_dir, "pano{}".format(self.n))
        self.save_folder = "pano{}".format(self.n)
        self.as_ = actionlib.SimpleActionServer("stitch_panorama", rover_panorama.msg.PanoramaAction, execute_cb=self.stitch,
                                                auto_start=False)
        self.take_image_ = rospy.Service("take_pano_image", std_srvs.srv.Empty, self.take_image)
        self.as_.start()

    # noinspection PyUnusedLocal
    def take_image(self, e):
        global datawait
        rf = take_image(rover_panorama.srv.TakeImageRequest()).result
        n = os.path.split(rf)[1]
        n = os.path.join(self.folder, n)
        self.images.append("\"" + n + "\"")
        rospy.loginfo("Took image, sending to basestation")
        send_file(filesend.srv.RequestManyFilesRequest(
            local_files=[rf],
            folder=self.save_folder
        ))
        datawait = True
        return rover_panorama.srv.TakeImageResponse()

    def call_and_send(self, cmd, toGo):
        feed = rover_panorama.msg.PanoramaFeedback(executing=cmd, commandsToGo=toGo)
        self.as_.publish_feedback(feed)
        os.system(cmd)

    def stitch(self, a):
        if True:
            rospy.loginfo("Running stitcher. THE BASESTATION MIGHT HEAVILY LAG!")
            prev = os.getcwd()
            os.chdir(self.folder)
            print self.images
            # create project file YES I USE self.call_and_send please don't kill me
            self.call_and_send("pto_gen -o pano.pto " + " ".join(self.images), 7)
            # do cpfind
            self.call_and_send("cpfind -o pano.pto --multirow --celeste pano.pto", 6)
            # do clean
            self.call_and_send("cpclean -o pano.pto pano.pto", 5)
            # do vertical lines
            self.call_and_send("linefind -o pano.pto pano.pto", 4)
            # do optimize locations
            self.call_and_send("autooptimiser -a -m -l -s -o pano.pto pano.pto", 3)
            # calculate size
            self.call_and_send("pano_modify --canvas=AUTO --crop=AUTO -o pano.pto pano.pto", 2)
            # stitch
            self.call_and_send("hugin_executor --stitching --prefix=output pano.pto", 1)
            # compress
            self.call_and_send("convert output.tif output.png", 0)
            os.chdir(prev)
            rospy.loginfo("Stitched!")

            result = rover_panorama.msg.PanoramaResult()
            result.resultFilenameBig = os.path.join(self.folder, "output.tif")
            result.resultFilenameSmall = os.path.join(self.folder, "output.png")
            self.as_.set_succeeded(result)
            self.n += 1
            self.images = []
            self.folder = os.path.join(fsend_recv_save_dir, "pano{}".format(self.n))
            self.save_folder = "pano{}".format(self.n)


p = Panorama()
rospy.spin()