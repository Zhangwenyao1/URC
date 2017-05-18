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


class Panorama:
    def __init__(self):
        self.images = []
        self.waiting_on = {}
        self.trig_waiting = []
        self.n = 0
        self.folder = os.path.join(fsend_recv_save_dir, "pano{}".format(self.n))
        self.save_folder = "pano{}".format(self.n)
        self.as_ = actionlib.SimpleActionServer("stitch_panorama", rover_panorama.msg.PanoramaAction, execute_cb=self.stitch,
                                                        auto_start=False)
        self.req_fini = rospy.Subscriber("file_saved", std_msgs.msg.String, self.do_a_fini, queue_size=10)
        print "hi2"
        self.take_image_ = rospy.Service("take_pano_image", std_srvs.srv.Empty, self.take_image)
        self.p = rospy.Publisher("pano_state", rover_panorama.msg.PanoState, queue_size=3, latch=True)
        print "hi"
        self.as_.start()

    def do_a_fini(self, e):
        print self.trig_waiting
        if e.data in self.trig_waiting:
            self.images.append(self.waiting_on[e.data])
            self.trig_waiting.remove(e.data)
            del self.waiting_on[e.data]
            self.publish_data()

    # noinspection PyUnusedLocal
    def take_image(self, e):
        global datawait
        rf = take_image(rover_panorama.srv.TakeImageRequest()).result
        n = os.path.split(rf)[1]
        n = os.path.join(self.folder, n)
        self.waiting_on[os.path.split(rf)[1]] = "\"" + n + "\""
        self.trig_waiting.append(os.path.split(rf)[1])
        rospy.loginfo("Took image, sending to basestation")
        send_file(filesend.srv.RequestManyFilesRequest(
            local_files=[rf],
            folder=self.save_folder
        ))
        datawait = True
        self.publish_data()
        return rover_panorama.srv.TakeImageResponse()

    def publish_data(self):
        msg = rover_panorama.msg.PanoState()
        msg.in_transfer = self.waiting_on.values()[:]
        msg.transferred = [x.strip("\"") for x in self.images[:]]
        msg.ready = len(self.images) > 2 and len(self.trig_waiting) == 0
        self.p.publish(msg)

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