#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import rospy
import serial
import string
import math
import sys
import json
import time
from geometry_msgs.msg import Twist
from aim.msg import angle
import logging
logging.basicConfig()


port='/dev/dji_board'
rospy.loginfo("Opening %s...", port)
#控制电机速度
def send_command(vx,vy,vz):
    data = { "speed":[vx,vy,vz] }
    data_string = json.dumps(data)
    ser.write('*'+ data_string +';')

try:
    ser = serial.Serial(port=port, baudrate=115200, timeout=5)
except serial.serialutil.SerialException:
    rospy.logerr("Dji not found at port "+port + ". Did you specify the correct port in the launch file?")
    sys.exit(0)

#ser.write('t\n')

def callback(angle):
    #rospy.loginfo("Sending cmd:[%.2f,%.2f,%.2f]", Twist.linear.x,Twist.linear.y,Twist.angular.z)
    x=angle.pitch
    y=angle.yaw
    z=angle.s
    rospy.loginfo("pitch:%f..yaw:%f...s:%f.." , angle.pitch,angle.yaw,angle.s)
    send_command(1,1,1)


while not rospy.is_shutdown():
    #rospy.init_node("serial")
    rospy.init_node('serial')
    rospy.Subscriber("chatter3",angle, callback)
    line = ser.readline()
    #rospy.loginfo("I have got chassis velicities: " + line)
    #解析字符串为python 对象
    rospy.loginfo("hello")
    #pub = rospy.Publisher('currant_vel', Twist, queue_size=10)
    #sub1= rospy.Subscriber("teleop_cmd_vel", Twist, callback)
    try:
        de_json = json.loads(line)
        linear_x = de_json[1][0]
        linear_y = de_json[1][1]
        angular_z = de_json[1][2]
        rospy.loginfo("get_feedback:[" + str(linear_x) + "," + str(linear_y)+ "," + str(angular_z) + "]\n")
        #twist = Twist()

        #speed_mps=(pwm-1.27)/38.61
        #x=-(linear_y-1.27)/38.61
        #y=-(linear_x-1.27)/38.61
        #z=angular_z*2.7
        
        # re   rad/s
        # 0.33 0.918
        # 0.55 1.53
        # 0.7  1.93


        #rospy.loginfo("resive base:[%.2f,%.2f,%.2f]",x,y,z)
        #twist.linear.x = float(x); twist.linear.y =float(y); twist.linear.z = 0
        #twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = float(z)
        #pub.publish(twist)
    except:
        None
    #rospy.loginfo(de_json)
    #控制电机速度
    # speed_x = 0
    # speed_y = 30
    # speed_z = 0
    # send_command(speed_x,speed_y,speed_z)
#关闭节点时停止电机
#time.sleep(1)
send_command(0,0,0)
ser.close

#关闭节点时先按control-s再按control-c
