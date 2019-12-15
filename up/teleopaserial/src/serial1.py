#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
import rospy
import serial
from std_msgs.msg import String
import math
import sys
import json
import time
from geometry_msgs.msg import Twist
from teleopaserial.msg import angle
import logging
logging.basicConfig()



port='/dev/dji_board'
rospy.loginfo("Opening %s...", port)
#控制电机速度

def send_gimbal(pitch,yaw):
    data = { "gimbal":[pitch,yaw]}
    data_string = json.dumps(data)
    ser.write('*'+ data_string +'?')

def send_chassis(vx,vy,vz):
    data = { "chassis":[vx,vy,vz] }
    data_string = json.dumps(data)
    ser.write('*'+ data_string +';')

def send_translation(translation):
    data ={"translation":[translation]}
    data_string = json.dumps(data)
    ser.write('*'+ data_string +'!')

try:
    ser = serial.Serial(port=port, baudrate=115200, timeout=5)
except serial.serialutil.SerialException:
    rospy.logerr("Dji not found at port "+port + ". Did you specify the correct port in the launch file?")
    sys.exit(0)

#ser.write('t\n')


def callback1(angle):
    #rospy.loginfo("Sending cmd:[%.2f,%.2f,%.2f]", Twist.linear.x,Twist.linear.y,Twist.angular.z)
    pitch=10000*angle.pitch
    yaw=1000*angle.yaw
    z=angle.s
    rospy.loginfo("pitch:%f.. yaw:%f...s:%f.." , angle.pitch,angle.yaw,angle.s)
    send_gimbal(int(pitch),int(yaw))

def callback2(translate):
    translation =translate.data
    rospy.loginfo("translation is:%s",translation)
    translation=translation.strip()
    if translation=="normal": translation=0
    if translation=="dodge": translation=1
    if translation=="motion": translation=2
    if translation=="follow": translation=3
    if translation=="auto": translation=4
    if translation=="load": translation=5
    if translation=="turn": translation=6
    if translation=="side": translation=7
    if translation=="hand": translation=8
    if translation=="shand": translation=9
    if translation=="auto": translation=10
    send_translation(translation)
    
def callback3(twist):
    speed_x = twist.linear.x
    speed_y = twist.linear.y
    speed_z = twist.angular.z
    rospy.loginfo("linear_x: %f",speed_x)
    send_chassis(int(speed_x),int(speed_y),int(speed_z))
    
#rospy.loginfo("linear_x: %f",speed_x)
rospy.Subscriber("control",angle, callback1)
rospy.Subscriber("schemaTranslation",String, callback2)
rospy.Subscriber('teleop_twist', Twist, callback3)
while not rospy.is_shutdown():
    rospy.init_node('serial')
    #pitch=1
    #yaw=2
    #z=3
    #send_gimbal(int(pitch),int(yaw))
   # vx=1
    #vy=2
   # vz=3
    #rospy.loginfo("%d vx",vx)
    #send_chassis(vx,vy,vz)
    line = ser.readline()
    #rospy.loginfo("I have got chassis velicities: " + line)
    #解析字符串为python 对象
    #rospy.loginfo("hello")
    #pub = rospy.Publisher('currant_vel', Twist, queue_size=10)
    #sub1= rospy.Subscriber("teleop_cmd_vel", Twist, callback)
    try:
        de_json = json.loads(line)
        #linear_x = de_json[1][0]
        #linear_y = de_json[1][1]
       # angular_z = de_json[1][2]
       # rospy.loginfo("get_feedback:[" + str(linear_x) + "," + str(linear_y)+ "," + str(angular_z) + "]\n")
        pitch1 = de_json[1][3]
        yaw2 = de_json[1][4]
        vx = de_json[1][0]
        vy = de_json[1][1]
        vz = de_json[1][2]
        a=de_json[1][5]
        b=de_json[1][6]
        c=de_json[1][7]
        d=de_json[1][8]
        #rospy.loginfo("get_feedback:[" + str(pitch1) + "," + str(yaw2)+ ","  +  "]\n")
        #rospy.loginfo("vx:%d,vy:%d,vz:%d",vx,vy,vz)
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
