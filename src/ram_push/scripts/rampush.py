#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64
import os
import math

class ArmPushBox():
    def __init__(self):
        rospy.init_node('joint_controller', anonymous=True)
        deg = 0.017453293
        self.joint1pub = rospy.Publisher('/ram/joint1_position_controller/command', Float64, queue_size=10)
        self.joint2pub = rospy.Publisher('/ram/joint2_position_controller/command', Float64, queue_size=10)
        self.joint4pub = rospy.Publisher('/ram/joint4_position_controller/command', Float64, queue_size=10)
        self.joint6pub = rospy.Publisher('/ram/joint6_position_controller/command', Float64, queue_size=10)
        self.joint7pub = rospy.Publisher('/ram/joint7_position_controller/command', Float64, queue_size=10)
        self.rate = rospy.Rate(60)
        self.base_shoulder(0,3.62*deg, 0.46*deg)
        self.elbow_wrist(0,3.68*deg, 0.46*deg)
        rospy.sleep(0.5)
        self.push_object(0.05)
        rospy.sleep(1)
    
    def base_shoulder(self, current, vel1, vel2):
        self.j1 = current
        self.j2 = current
        for i in range(0, 26):
          self.j1 = current + vel1 * i
          self.j2 = current - vel2 * i
          self.joint1pub.publish(self.j1)
          self.joint2pub.publish(self.j2)
          print "joint1 position: %.2f" % (self.j1)
          print "joint2 position: %.2f" % (self.j2)
          rospy.sleep(0.05) 

    def elbow_wrist(self, current, vel1, vel2):
        self.j4 = current
        self.j6 = current 
        for i in range(0, 26):
          self.j4 = current - vel1 * i
          self.j6 = current + vel2 * i
          self.joint4pub.publish(self.j4)
          self.joint6pub.publish(self.j6)
          print "joint4 position: %.2f" % (self.j4)
          print "joint6 position: %.2f" % (self.j6)
          rospy.sleep(0.05)     
              
    def push_object(self, vel):
        start = 0
        for i in range(0, 11):
          self.j7 = start + vel * i
          self.joint7pub.publish(self.j7)
          print "joint7 position: %.2f" % (self.j7)
          rospy.sleep(0.05)  
                 
def main():
    obj = ArmPushBox()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

