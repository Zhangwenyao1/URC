import rospy
import rover_science.msg
import rover_science.srv
import sensor_msgs.msg
import std_msgs.msg

rospy.init_node("science_server")

ph_topic = rospy.get_param("~ph_topic")
humid_topic = rospy.get_param("~humid_topic")
temp_topic = rospy.get_param("~temp_topic")
navsat_topic = rospy.get_param("~navsat_topic")


class ScienceDataTracker:
    def __init__(self):
        self.sites = rover_science.msg.Sites()

    def new_site(self, site_name):
        site_id = len(self.sites.sites)
        self.sites.sites.append(
            rover_science.msg.Site(site_name=site_name, has_pano=0)
        )
        return site_id

    def site_name_change(self, site_id, new_site_name):
        self.sites.sites[site_id].site_name = new_site_name

    def take_measurement(self, site_id, to_take):
        current_navsat_fix = rospy.wait_for_message(navsat_topic, sensor_msgs.msg.NavSatFix, timeout=5)
        measurement = rover_science.msg.Measurement()
        measurement.location.latitude = current_navsat_fix.latitude
        measurement.location.latitude = current_navsat_fix.longitude
        measurement.location.altitude = current_navsat_fix.altitude
        measurement.data_completeness = 0x0
        measurement.time_recorded = rospy.Time.now()
        m_id = len(self.sites.sites[site_id].measurements)
        self.sites.sites[site_id].measurements.append(measurement)
        return self.take_measurement(site_id, m_id, to_take)

    def _take_ph_measurement(self, site_id, measurement_id):
        ph = rospy.wait_for_message(ph_topic, std_msgs.msg.Float32, timeout=5)
        self.sites.sites[site_id].measurements[measurement_id].ph = ph.data

    def _take_humid_measurement(self, site_id, measurement_id):
        humid = rospy.wait_for_message(humid_topic, std_msgs.msg.Float32, timeout=5)
        self.sites.sites[site_id].measurements[measurement_id].humidity = humid.data

    def _take_temp_measurement(self, site_id, measurement_id):
        temp = rospy.wait_for_message(temp_topic, std_msgs.msg.Float32, timeout=5)
        self.sites.sites[site_id].measurements[measurement_id].temp = temp.data

    def take_measurements(self, site_id, measurement_id, to_take):
        taken = 0
        if to_take & rover_science.msg.Measurement.HAS_PH == rover_science.msg.Measurement.HAS_PH:
            try:
                self._take_ph_measurement(site_id, measurement_id)
                taken |= rover_science.msg.Measurement.HAS_PH
            except rospy.ROSException:
                rospy.logerr("Failed to take PH reading: couldn't get value in time")
        if to_take & rover_science.msg.Measurement.HAS_HUMIDITY == rover_science.msg.Measurement.HAS_HUMIDITY:
            try:
                self._take_humid_measurement(site_id, measurement_id)
                taken |= rover_science.msg.Measurement.HAS_HUMIDITY
            except rospy.ROSException:
                rospy.logerr("Failed to take humidity reading: couldn't get value in time")
        if to_take & rover_science.msg.Measurement.HAS_TEMP == rover_science.msg.Measurement.HAS_TEMP:
            try:
                self._take_temp_measurement(site_id, measurement_id)
                taken |= rover_science.msg.Measurement.HAS_TEMP
            except rospy.ROSException:
                rospy.logerr("Failed to take temp reading: couldn't get value in time")
        return taken

    def mark_pano(self, site_id):
        self.sites.sites[site_id].has_pano = 1

    def delete_site(self, site_id):
        del self.sites.sites[site_id]


site_manager = ScienceDataTracker()
science = rospy.Publisher("sites", rover_science.msg.Sites, queue_size=15)


def new_site(msg):
    s_id = site_manager.new_site(msg.site_name)
    publish()
    return rover_science.srv.NewSiteResponse(site_name=msg.site_name, site_id=s_id)


def mark_pano(msg):
    try:
        site_manager.mark_pano(msg.site_id)
        publish()
        return rover_science.srv.MarkPanoResponse(success=True)
    except IndexError:
        return rover_science.srv.MarkPanoResponse(success=False)


def delete_site(msg):
    try:
        site_manager.delete_site(msg.site_id)
        return rover_science.srv.DeleteSiteResponse(success=True)
    except IndexError:
        return rover_science.srv.DeleteSiteResponse(success=False)


def site_name_change(msg):
    try:
        site_manager.site_name_change(msg.site_id, msg.site_name)
        publish()
        return rover_science.srv.SiteNameChangeResponse(success=True)
    except IndexError:
        return rover_science.srv.SiteNameChangeResponse(success=False)


def take_measurement(msg):
    r = rover_science.srv.TakeMeasurementResponse(
        measurements_taken=site_manager.take_measurement(msg.site_id, msg.measurements_to_take)
    )
    publish()
    return r


def update_measurement(msg):
    r = rover_science.srv.UpdateMeasurementResponse(
        measurements_taken=site_manager.take_measurements(msg.site_id, msg.measurement.id, msg.measurements_to_retake)
    )
    publish()
    return r


def publish():
    science.publish(site_manager.sites)

s__update_measure_ = rospy.Service("~update_measurement", rover_science.srv.UpdateMeasurement, update_measurement)
s_take_measurement = rospy.Service("~take_measurement", rover_science.srv.TakeMeasurement, take_measurement)
s_site_name_change = rospy.Service("~change_site_name", rover_science.srv.SiteNameChange, site_name_change)
s__mark_panorama__ = rospy.Service("~mark_panorama", rover_science.srv.MarkPano, mark_pano)
s___delete_site___ = rospy.Service("~delete_site", rover_science.srv.DeleteSite, delete_site)
s____new_site_____ = rospy.Service("~new_site", rover_science.srv.NewSite, new_site)

rospy.spin()