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
from geometry_msgs.msg import Twist
from hkvs.msg import vel
from hkvs.msg import downyaw
import logging
import smach
import smach_ros
from multiprocessing import Process
from time import sleep

#交互头文件
from dynamic_reconfigure.server import Server
from teleopaserial.cfg import serialConfig

'''
#串口信息初始化
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
'''
chassis_mode,gimbal_mode,fire_mode = '','',''
#云台yaw速度
def send_gimbal(cv):
    data = { "gimbal":[cv]}
    data_string = json.dumps(data)
    ser.write('*'+ data_string +'?')
#底盘速度
def send_chassis(vx,vy,vz):
    data = { "chassis":[vx,vy,vz] }
    data_string = json.dumps(data)
    ser.write('*'+ data_string +';')
#手动控制云台
def send_gimbal_hand_angle(hand_pitch,hand_yaw):
    data = {"hand_angle":[hand_pitch,hand_yaw]}
    data_string = json.dumps(data)
    ser.write('*' + data_string + '<')
#控制下位机kpki
def control_chassis_kpki(chassis_kp,chassis_ki,gimbal_kp,gimbal_ki,bullet_kp,bullet_ki,gimbal_up,gimbal_left):
    data = {"Pid_param":[chassis_kp,chassis_ki,gimbal_kp,gimbal_ki,bullet_kp,bullet_ki,gimbal_up,gimbal_left]}
    data_string = json.dumps(data)
    ser.write('*' + data_string + '>')


#人机交互
def uptodowncontrol(config, level):
    print("chassis kp,ki  is:{},{}".format(config.chassis_kp,config.chassis_ki))
    print("gimbal  kp,ki  is:{},{}".format(config.gimbal_kp,config.gimbal_ki))
    print("bullet  kp,ki  is:{},{}".format(config.bullet_kp,config.bullet_ki))
    print("gimbal  pwm dl is:{},{}".format(config.gimbal_up,config.gimbal_left))
    print('*'*30)
    #control_chassis_kpki(int(100*config.chassis_kp),int(100*config.chassis_ki),int(100*config.gimbal_kp),int(100*config.gimbal_ki),int(100*config.bullet_kp),int(100*config.bullet_ki),
#int(100*config.gimbal_up),int(100*config.gimbal_left))
    return config

def visualCB(vel_visual):
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

def cmdCB(twist):
        speed_x = twist.linear.x
        speed_y = twist.linear.y
        speed_z = twist.angular.z
        rospy.loginfo("linear_x: %f",speed_x)
        send_chassis(int(speed_x),int(speed_y),int(speed_z))

def chassisCB(chassis_translate):
	global chassis_mode
	chassis_mode = chassis_translate
        rospy.loginfo("chassis_mode:%s ",chassis_mode)

def gimbalCB(gimbal_translate):
	global gimbal_mode
	gimbal_mode = gimbal_translate
        rospy.loginfo("gimbal_mode:%s ",gimbal_mode)

def fireCB(fire_translate):
	global fire_mode
	fire_mode = fire_translate
        rospy.loginfo("fire_mode:%s ",fire_mode)



#主循环
rospy.init_node('serialfirst')
srv = Server(serialConfig, uptodowncontrol)

rospy.Subscriber("chassis_smach",String, chassisCB)
rospy.Subscriber("gimbal_smach",String, gimbalCB)
rospy.Subscriber("fire_smach",vel, fireCB)

rospy.Subscriber("vel_linear",vel, visualCB)

rospy.Subscriber("schemaTranslation",String, callback2)
rospy.Subscriber('teleop_twist_drop', Twist, cmdCB)
downyawpub = rospy.Publisher('downyaw', downyaw, queue_size = 1)

while not rospy.is_shutdown():
    	time.sleep(0.1)
    	#line = ser.readline()
    	try:
        	de_json = json.loads(line)
		current_left_front_wheel = de_json[1][0]
		current_right_front_wheel = de_json[1][1]
		current_left_rear_wheel = de_json[1][2]
		current_right_rear_wheel = de_json[1][3]
		current_vx = de_json[1][4]
		current_vy = de_json[1][5]
		current_angular_z = de_json[1][6]
		current_pitch = de_json[1][7]
		current_yaw = de_json[1][8]
		downyawpub.publish(current_yaw)
		print("i get wheel speed zs,rs,zx,yx:{},{},{},{}".format(current_left_front_wheel,current_right_front_wheel,current_left_rear_wheel,current_right_rear_wheel))
		print("i get current vel:{},{},{}".format(current_vx,current_vy,current_angular_z))
		print("i get current angle:{},{}".format(current_pitch,current_yaw))
    	except:
		pass
        	#print("get data false!!! please check for errors [qsy]")

#rospy.spin()
print("end")
send_chassis(0,0,0)
ser.close


