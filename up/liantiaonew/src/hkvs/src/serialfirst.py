#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
import rospy
import serial
from std_msgs.msg import String
import math
import sys
import json
import time
import threading
from hkvs.msg import vel
from geometry_msgs.msg import Twist
import logging
import smach
import smach_ros
from multiprocessing import Process
from time import sleep
logging.basicConfig()
port='/dev/dji_board'
rospy.loginfo("Opening %s...", port)
ser=1

try:
    ser = serial.Serial(port=port, baudrate=115200, timeout=5)
except serial.serialutil.SerialException:
    rospy.logerr("Dji not found at port "+port + ". Did you specify the correct port in the launch file?")
    sys.exit(0)
print("串口初始化完成")

#我先去掉了状态转换部分方便你们测试自瞄，
#这里是视觉linear通信的内容，需要修改名称和起始位终止位和下位机对应
def send_gimbal_hand_angle(hand_pitch,hand_paw):
    data={"hand_angle":[hand_pitch,hand_yaw]}
    data_string=json.dumps(data)
    ser.write('*'+data_string+'<')

def send_gimbal(cv):
    data = { "gimbal":[cv]}
    data_string = json.dumps(data)
    ser.write('*'+ data_string +'?')

#底盘
def send_chassis(vx,vy,vz):
    data = { "chassis":[vx,vy,vz] }
    data_string = json.dumps(data)
    ser.write('*'+ data_string +';')

#在这里发布视觉linear 汤伊静
def callback1(vel_visual):
	cv = vel_visual.vel
	print("i heard visual_vel",cv)
        send_gimbal(int(cv))


def callback2(translate):
        transform =translate.data
        transform=transform.strip()
        if transform=="up": 
           	send_gimbal_hand_angle(1,0)
        if transform=="down": 
           	send_gimbal_hand_angle(-1,0)
        if transform=="left": 
        	send_gimbal_hand_angle(0,1)
        if transform=="right": 
             	send_gimbal_hand_angle(0,-1)

def callback3(twist):
        speed_x = twist.linear.x
        speed_y = twist.linear.y
        speed_z = twist.angular.z
        rospy.loginfo("linear_x: %f",speed_x)
        send_chassis(int(speed_x),int(speed_y),int(speed_z))


while not rospy.is_shutdown():
    rospy.init_node('serial', anonymous=True)
    rospy.Subscriber("vel_linear",vel, callback1)
    rospy.Subscriber("schemaTranslation",String, callback2)
    rospy.Subscriber('teleop_twist', Twist, callback3)
    rospy.spin()

send_chassis(0,0,0)
ser.close

