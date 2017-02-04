import rospy
import sys
from std_msgs.msg import Float32

   
def listener():

   rospy.init_node('listener', anonymous=True)
   data = rospy.wait_for_message("temp", Float32)

   f = open('Savetemp', 'w')
   f.write(str(data.data))  
   f.close()
   

if __name__ == '__main__':
   listener()