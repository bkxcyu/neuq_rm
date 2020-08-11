#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String
import math
import sys
import time
import threading
from geometry_msgs.msg import Twist
import logging
import smach
import smach_ros
from multiprocessing import Process
from time import sleep
from hkvs.msg import down
logging.basicConfig()

transform=''
#云台
gimbal_finish_left_nine1,gimbal_finish_right_nine1=0,0
#底盘
deduce_blood1,finish_follow1,finish_climbing1,vel_x,vel_y,vel_z = 0,0,0,0,0,0


chassissmach = rospy.Publisher('chassis_smach', String, queue_size = 1)
gimbalsmach = rospy.Publisher('gimbal_smach', String, queue_size = 1)
firesmach = rospy.Publisher('fire_smach', String, queue_size = 1)
twistpub = rospy.Publisher('teleop_twist_drop', Twist, queue_size = 1)


###################################################底盘状态机
class CHASSIS_NORMAL(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_dodge','chassis_motion','keep_normal','chassis_follow'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(1)
	#底盘普通模式发布速度指令
        twist = Twist()
        twist.linear.x = vel_x; twist.linear.y = vel_y; twist.linear.z = 0
        twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = vel_z
	twistpub.publish(twist)

        if getformkey=='chassis_dodge':
            chassissmach.publish('chassis_dodge')
            return 'chassis_dodge'
        elif getformkey=="chassis_motion":
            chassissmach.publish('chassis_motion')
            return 'chassis_motion'
        elif getformkey=='chassis_follow':
            chassissmach.publish('chassis_follow')
            return 'chassis_follow'
        else:
            return 'keep_normal'
       

class CHASSIS_DODGE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['chassis_normal','keep_dodge'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(1)
        if getformkey == "chassis_normal":
            chassissmach.publish('chassis_normal')
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
        time.sleep(1)
        if finish_follow==1 or getformkey=='chassis_normal':
           chassissmach.publish('chassis_normal')
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
        time.sleep(1)
        if finish_climbing==1 or getformkey=='chassis_normal':
           chassissmach.publish('chassis_normal')
           return 'chassis_normal'
        else:
            return 'keep_climbing' 
###################################################底盘状态机定义完成


###################################################云台状态机
class GIMBAL_AUTO_AIM(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_left_nine','gimbal_right_nine','keep_auto_aim','gimbal_load','gimbal_hand_aim'])


    def execute(self, userdata):
        getformkey=transform
        time.sleep(0.5)
        if getformkey =='gimbal_load':
            gimbalsmach.publish("gimbal_load")
            return 'gimbal_load'
        elif getformkey=='gimbal_left_nine':
            gimbalsmach.publish("gimbal_left_nine")
            return 'gimbal_left_nine'
        elif getformkey =='gimbal_right_nine':
            gimbalsmach.publish("gimbal_right_nine")
            return 'gimbal_right_nine'
        elif getformkey == 'gimbal_hand_aim':
            gimbalsmach.publish("gimbal_hand_aim")
            return 'gimbal_hand_aim'
        else:
            return 'keep_auto_aim'


class GIMBAL_LEFT_NINE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_left_nine'])

    def execute(self, userdata):
        gimbal_finish_left_nine=gimbal_finish_left_nine1
        getformkey=transform
        time.sleep(0.5)
        if gimbal_finish_left_nine==1 or getformkey =='gimbal_auto_aim':
            gimbalsmach.publish("gimbal_auto_aim")
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
        time.sleep(0.5)
        if gimbal_finish_right_nine==1 or getformkey =='gimbal_auto_aim': 
            gimbalsmach.publish("gimbal_auto_aim")
            return 'gimbal_auto_aim'
        else:
             return'keep_right_nine'

class GIMBAL_LOAD(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_load'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(0.5)
        if getformkey=='gimbal_auto_aim': 
             gimbalsmach.publish("gimbal_auto_aim")
             return 'gimbal_auto_aim'
        else:
             return'keep_load'

class GIMBAL_HAND_AIM(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['gimbal_auto_aim','keep_hand_aim'])

    def execute(self, userdata):
        time.sleep(0.5)
        getformkey=transform
        if getformkey=='gimbal_auto_aim':   
             gimbalsmach.publish("gimbal_auto_aim")
             return 'gimbal_auto_aim'
        else:
             return'keep_hand_aim'

###################################################云台状态机定义完成


###################################################开火状态机
class HAND_FIRE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['auto_fire','keep_hand_fire'])

    def execute(self, userdata):
        time.sleep(0.5)
        getformkey=transform
        if getformkey =='auto_fire':
            firesmach.publish("auto_fire")
            return 'auto_fire'
        else:
             return'keep_hand_fire'

class AUTO_FIRE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['keep_auto_fire','hand_fire'])

    def execute(self, userdata):
        getformkey=transform
        time.sleep(0.5)
        if getformkey =='hand_fire':
            firesmach.publish("hand_fire")
            return 'hand_fire'
        else:
             return'keep_auto_fire'
###################################################开火状态机定义完成


def gimbal(transform,gimbal_finish_left_nine1,gimbal_finish_right_nine1):
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


def chassis(transform,deduce_blood1,finish_climbing1,finish_follow1,vel_x,vel_y,vel_z):
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




def transformCB(translate):
    global transform
    transform =translate.data
    rospy.loginfo("translation is:%s",translate)

def downtoupCB(down):
    global gimbal_finish_left_nine1,gimbal_finish_right_nine1,deduce_blood1,finish_follow1,finish_climbing1 
    gimbal_finish_left_nine1 =down.gimbal_finish_left_nine1
    gimbal_finish_right_nine1=down.gimbal_finish_right_nine1
    deduce_blood1,finish_follow1=down.deduce_blood1,finish_follow1
    finish_climbing1 = down.finish_climbing1
    rospy.loginfo("finish climbing is:%s",finish_climbing1)

def cmdCB(twist):
	global vel_x,vel_y,vel_z
        vel_x = twist.linear.x
        vel_y = twist.linear.y
        vel_z = twist.angular.z
        rospy.loginfo("linear_x: %f,%f,%f",vel_x,vel_y,vel_z)


threads = []
t2 = threading.Thread(target=chassis,args=(transform,deduce_blood1,finish_climbing1,finish_follow1,vel_x,vel_y,vel_z))
threads.append(t2)
t3 = threading.Thread(target=gimbal,args=(transform,gimbal_finish_left_nine1,gimbal_finish_right_nine1))
threads.append(t3)
t4 = threading.Thread(target=fire,args=(transform,))
threads.append(t4)


if __name__=='__main__':
    rospy.init_node('translation', anonymous=True)
    rospy.Subscriber("teleopschemaTranslation",String, transformCB)
    rospy.Subscriber("downtoup",down, downtoupCB)
    rospy.Subscriber('teleop_twist', Twist, cmdCB)
    for t in threads:
         t.setDaemon(True)
         t.start()
    t2.join()
    t3.join()
    t4.join()
rospy.spin()

