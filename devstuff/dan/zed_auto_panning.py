#!/usr/bin/env python
import rospy
import tf 
from std_msgs.msg import Float32
 
def movezed():
	rospy.init_node('move', anonymous=True)
	pub = rospy.Publisher('/zed_servo', Float32, queue_size=10)
	rate = rospy.Rate(10) 
	br = tf.TransformBroadcaster()
	steprate = 1
	negsteprate = -1
	while(1):
		for i in range(0,160,steprate):
			pub.publish(i)
			i+=1

			br.sendTransform((0,0,0),
			tf.transformations.quaternion_from_euler(0, 0, steprate),
			rospy.Time.now(), "mast_link", "cam")
			rate.sleep()

		for i in range(160,0,-1):
			pub.publish(i)
			i = i-1		
				
			br.sendTransform((0,0,0),
			tf.transformations.quaternion_from_euler(0, 0, negsteprate),
			rospy.Time.now(), "mast_link", "cam")
			rate.sleep()	

if __name__ == '__main__':
	try:
		movezed()
	except rospy.ROSInterruptException:
		pass
