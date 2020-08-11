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
from teleopaserial.msg import angle
import logging
import smach
import smach_ros
from multiprocessing import Process
from time import sleep
logging.basicConfig()

transform=''
translation =1

#云台
pitch,yaw =0,0
gimbal_finish_left_nine1,gimbal_finish_right_nine1,auto_fire=0,0,0
#底盘
speed_x,speed_y,speed_z=0,0,0
deduce_blood1,finish_follow1,finish_climbing1 = 0,0,0

class CHASSIS_NORMAL(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_dodge','chassis_motion','keep_normal','chassis_follow'])
        self.normal=0

    def execute(self, userdata):
        self.normal+=1
        deduce_blood=deduce_blood1
        getformkey=transform
        time.sleep(2)
        print(speed_x,speed_y,speed_z)
        if deduce_blood==1 or getformkey=='chassis_dodge':
            self.normal=0
            return 'chassis_dodge'
        elif getformkey=="chassis_motion":
            self.normal=0
            return 'chassis_motion'
        elif getformkey=='chassis_follow':
            self.normal=0
            return 'chassis_follow'
        else:
	        if self.normal==1:
		        print("hehe")
                return 'keep_normal'
       

class CHASSIS_DODGE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_normal','keep_dodge'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(2)
        if getformkey == "chassis_normal":
            return 'chassis_normal'
        else:
            return 'keep_dodge'

class CHASSIS_FOLLOW(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_normal','keep_follow'])
    def execute(self, userdata):
        finish_follow=finish_follow1
        getformkey=transform
        time.sleep(2)
        if finish_follow==1 or getformkey=='chassis_normal':
           return 'chassis_normal'
        else:
            return 'keep_follow'

class CHASSIS_CLIMBING(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_normal','keep_climbing'])
       

    def execute(self, userdata):
        finish_climbing=finish_climbing1
        getformkey=transform
        time.sleep(2)
        if finish_climbing==1 or getformkey=='chassis_normal':
           return 'chassis_normal'
        else:
            return 'keep_climbing' 
#/////////////////////////////////////////////////////////////////////////////////////////////////
#/////////////////////////////////////////////////////////////////////////////////////////////////
# end of chassis smatch
class GIMBAL_AUTO_AIM(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_left_nine','gimbal_right_nine','keep_auto_aim','gimbal_load','gimbal_hand_aim'])


    def execute(self, userdata):
        getformkey=transform
        time.sleep(2)
        print(pitch)
        print(yaw)
        if getformkey =='gimbal_load':
            return 'gimbal_load'
        elif getformkey=='gimbal_left_nine':
            return 'gimbal_left_nine'
        elif getformkey =='gimbal_right_nine':
            return 'gimbal_right_nine'
        elif getformkey == 'gimbal_hand_aim':
            return 'gimbal_hand_aim'
        else:
            return 'keep_auto_aim'

# define state auto_fire

class GIMBAL_LEFT_NINE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_left_nine'])

    def execute(self, userdata):
        gimbal_finish_left_nine=gimbal_finish_left_nine1
        getformkey=transform
        time.sleep(2)
        if gimbal_finish_left_nine==1 or getformkey =='gimbal_auto_aim':
            gimbal_finish_left_nine=1
            return 'gimbal_auto_aim'
        else:
             return'keep_left_nine'

class GIMBAL_RIGHT_NINE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_right_nine'])

    def execute(self, userdata):
        gimbal_finish_right_nine=gimbal_finish_right_nine1
        getformkey=transform
        time.sleep(2)
        if gimbal_finish_right_nine==1 or getformkey =='gimbal_auto_aim': 
            gimbal_finish_right_nine=0
            return 'gimbal_auto_aim'
        else:
             return'keep_right_nine'

class GIMBAL_LOAD(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_load'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(2)
        if getformkey=='gimbal_auto_aim':   
             return 'gimbal_auto_aim'
        else:
             return'keep_load'

class GIMBAL_HAND_AIM(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_hand_aim'])

    def execute(self, userdata):
        global transform
        getformkey=transform
        if transform=="up":
             transform="1" 
             print('云台向上')
             #send_gimbal_hand_angle(1,0)
        if transform=="down": 
             transform="1"
             print('云台向下')
             #send_gimbal_hand_angle(-1,0)
        if transform=="left": 
             transform="1"
             print('云台向左')
             #send_gimbal_hand_angle(0,1)
        if transform=="right": 
             transform="1"
             print('云台向右')
             #send_gimbal_hand_angle(0,-1)
        time.sleep(2)
        if getformkey=='gimbal_auto_aim':   
             return 'gimbal_auto_aim'
        else:
             return'keep_hand_aim'


class HAND_FIRE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['auto_fire','keep_hand_fire'])

    def execute(self, userdata):
        global getformkey
        getformkey=transform
        time.sleep(2)
        if getformkey == 'fire':
            getformkey =='1'
            print('开火，凸凸凸')
        if getformkey =='auto_fire':
            return 'auto_fire'
        else:
             return'keep_hand_fire'

class AUTO_FIRE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['keep_auto_fire','hand_fire'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(2)

        if getformkey =='hand_fire':
            return 'hand_fire'
        else:
             return'keep_auto_fire'
########################################################################################################################
####################################################################################################################################
################################################################################################################
########################################################################################################################################
#######################################################################################################

def gimbal(transform,gimbal_finish_left_nine1,gimbal_finish_right_nine1,pitch,yaw):
    gimbaltranslate = smach.StateMachine(outcomes=[])

    with gimbaltranslate:
        smach.StateMachine.add('GIMBAL_AUTO_AIM', GIMBAL_AUTO_AIM(),
                               transitions={'gimbal_left_nine':'GIMBAL_LEFT_NINE',
                                            'gimbal_right_nine':'GIMBAL_RIGHT_NINE',
                                            'keep_auto_aim':'GIMBAL_AUTO_AIM',
                                            'gimbal_load':'GIMBAL_LOAD',
                                            'gimbal_hand_aim':'GIMBAL_HAND_AIM'})
        smach.StateMachine.add('GIMBAL_LEFT_NINE', GIMBAL_LEFT_NINE(),
                               transitions={'gimbal_auto_aim':'GIMBAL_AUTO_AIM','keep_left_nine':'GIMBAL_LEFT_NINE'})
        smach.StateMachine.add('GIMBAL_RIGHT_NINE', GIMBAL_RIGHT_NINE(),
                               transitions={'gimbal_auto_aim':'GIMBAL_AUTO_AIM','keep_right_nine':'GIMBAL_RIGHT_NINE'})
        smach.StateMachine.add('GIMBAL_LOAD', GIMBAL_LOAD(),
                               transitions={'gimbal_auto_aim':'GIMBAL_AUTO_AIM','keep_load':'GIMBAL_LOAD'})
        smach.StateMachine.add('GIMBAL_HAND_AIM',GIMBAL_HAND_AIM(),
                                transitions={'gimbal_auto_aim':'GIMBAL_AUTO_AIM','keep_hand_aim':'GIMBAL_HAND_AIM'})
    sis = smach_ros.IntrospectionServer('my_smach_introspection_server', gimbaltranslate, '/GIMBAL_ROOT')
    sis.start()
    outcome = gimbaltranslate.execute()
    sis.stop()


def chassis(transform,deduce_blood1,finish_climbing1,finish_follow1,speed_x,speed_y,speed_z):
    chassistranslate = smach.StateMachine(outcomes=[])

    with chassistranslate:
        smach.StateMachine.add('CHASSIS_NORMAL', CHASSIS_NORMAL(),
                               transitions={'chassis_dodge':'CHASSIS_DODGE','keep_normal':'CHASSIS_NORMAL','chassis_motion':'CHASSIS_CLIMBING','chassis_follow':'CHASSIS_FOLLOW'})
        smach.StateMachine.add('CHASSIS_DODGE', CHASSIS_DODGE(),
                               transitions={'chassis_normal':'CHASSIS_NORMAL','keep_dodge':'CHASSIS_DODGE'})
        smach.StateMachine.add('CHASSIS_FOLLOW', CHASSIS_FOLLOW(),
                               transitions={'chassis_normal':'CHASSIS_NORMAL','keep_follow':'CHASSIS_FOLLOW'})
        smach.StateMachine.add('CHASSIS_CLIMBING', CHASSIS_CLIMBING(),
                               transitions={'chassis_normal':'CHASSIS_NORMAL','keep_climbing':'CHASSIS_CLIMBING'})
    sis1 = smach_ros.IntrospectionServer('my_smach_introspection_server', chassistranslate, '/CHASSIS_ROOT')
    sis1.start()
    outcome1 = chassistranslate.execute()
    sis1.stop()

def fire(transform):
    chassistranslate = smach.StateMachine(outcomes=[])
    with chassistranslate:
        smach.StateMachine.add('HAND_FIRE', HAND_FIRE(),
                               transitions={'auto_fire':'AUTO_FIRE','keep_hand_fire':'HAND_FIRE'})
        smach.StateMachine.add('AUTO_FIRE', AUTO_FIRE(),
                               transitions={'hand_fire':'HAND_FIRE','keep_auto_fire':'AUTO_FIRE'})
    sis2 = smach_ros.IntrospectionServer('my_smach_introspection_server', chassistranslate, '/FIRE_ROOT')
    sis2.start()
    outcome2 = chassistranslate.execute()
    sis2.stop()



rospy.init_node('serial', anonymous=True)

def main():
    def callback1(angle):
        global pitch
        global yaw
        global s
        pitch=10*angle.pitch
        yaw=10*angle.yaw
        z=angle.s
    
    def callback2(translate):
        global translation
        global transform
        transform =translate.data
        rospy.loginfo("translation is:%s",translate)
    def callback3(twist):
        global speed_x
        global speed_y
        global speed_z
        speed_x = twist.linear.x
        speed_y = twist.linear.y
        speed_z = twist.angular.z
        print('sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss')
        rospy.loginfo("linear_x: %f",speed_x)

    rospy.Subscriber("control",angle, callback1)
    rospy.Subscriber("schemaTranslation",String, callback2)
    rospy.Subscriber('teleop_twist', Twist, callback3)

def down_to_up():
    while True:
        print('我在接受下位机的消息哦')
        time.sleep(3)
        #de_json = json.loads(line)
        #linear_x = de_json[1][0]
        #linear_y = de_json[1][1]
       # angular_z = de_json[1][2]
       # rospy.loginfo("get_feedback:[" + str(linear_x) + "," + str(linear_y)+ "," + str(angular_z) + "]\n")
        # pitch1 = de_json[1][3]
        # yaw2 = de_json[1][4]
        # vx = de_json[1][0]
        # vy = de_json[1][1]
        # vz = de_json[1][2]
        # finish_climbing1=de_json[1][5]
        # finish_follow1=de_json[1][6]
        # gimbal_finish_left_nine1=de_json[1][7]
        # gimbal_finish_right_nine1=de_json[1][8]



threads = []
t1 = threading.Thread(target=main)
threads.append(t1)
t2 = threading.Thread(target=chassis,args=(transform,deduce_blood1,finish_climbing1,finish_follow1,speed_x,speed_y,speed_z))
threads.append(t2)
t3 = threading.Thread(target=gimbal,args=(transform,gimbal_finish_left_nine1,gimbal_finish_right_nine1,pitch,yaw))
threads.append(t3)
t4 = threading.Thread(target=fire,args=(transform,))
threads.append(t4)
t5 = threading.Thread(target=down_to_up)
threads.append(t5)
if __name__=='__main__':
    for t in threads:
        t.setDaemon(True)
        t.start()
        
    t1.join()
    t2.join()
    t3.join()
    t4.join()


'''while not rospy.is_shutdown():
	print("11111111111111111111111111")
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
        SUIDONGWANCHENG1=a
        GIMBAL_FINISH_ANGLE_NINE1=b
        GIMBAL_FINISH_ANGLE_HALF1=c
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
'''
