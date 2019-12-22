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

translation =1
port='/dev/dji_board'
rospy.loginfo("Opening %s...", port)
#控制电机速度
AUTO_AIM_FINISH=1
FAXIANDIJUN1=0
XUELIANGJIANSHAO1=0
SUIDONGWANCHENG1=1

GIMBAL_FINISH_ANGLE_NINE1=1
GIMBAL_FINISH_ANGLE_HALF1=1

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
class CHASSIS_NORMAL(smach.State):
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['outcome1','keep_normal'])
        

    def execute(self, userdata):
        FAXIANDIJUN=FAXIANDIJUN1
        XUELIANGJIANSHAO=XUELIANGJIANSHAO1
        time.sleep(2)
        send_translation(1)
        rospy.loginfo('Executing state CHASSSIS_NORMAL')
        if FAXIANDIJUN==1 or XUELIANGJIANSHAO==1:
            return 'outcome1'
        else:
            return 'keep_normal'
       


# define state Bar
class CHASSIS_DODGE(smach.State):
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['outcome2','keep_dodge'])

    def execute(self, userdata):
        FAXIANMUBIAO=FAXIANMUBIAO1
        XUELIANGJIANSHAO=XUELIANGJIANSHAO1
        time.sleep(2)
        send_translation(2)
        rospy.loginfo('Executing state CHASSIS_DODGE')
        if FAXIANMUBIAO==0 and XUALIANGJIANSHAO==0:
            return 'outcome2'
	else:
	    return 'keep_dodge'
class CHASSIS_FOLLOW(smach.State):

    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')

    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['outcome3','keep_follow'])
       

    def execute(self, userdata):
        SUIDONGWANCHENG=SUIDONGWANCHENG1
        time.sleep(2)
        send_translation(3)
        rospy.loginfo('Executing state CHSSIS_FOLLOW')
    
        if SUIDONGWANCHENG==1:
           return 'outcome3'
        else:
            return 'keep_follow'
#/////////////////////////////////////////////////////////////////////////////////////////////////
#/////////////////////////////////////////////////////////////////////////////////////////////////
class GIMBAL_AUTO_AIM(smach.State):
    
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_NINE','TRANSLATE_HALF','TRANSLATE_AUTO_FIRE','keep_auto_aim','TRANSLATE_HAND_FIRE','TRANSLATE_LOAD'])


    def execute(self, userdata):
        getformkey=translation
        FAXIANDIJUN=FAXIANDIJUN1
        rospy.loginfo("tasdadasfdgdfhfghrtfhsranslation is the %d",getformkey)
        time.sleep(2)
        send_translation(4)
        rospy.loginfo('Executing state GIMBAL_AUTO_AIM')
        if getformkey ==6:
            return 'TRANSLATE_LOAD'
        elif getformkey==7:
            return 'TRANSLATE_HALF'
        elif getformkey ==8:
            return 'TRANSLATE_NINE'
        elif getformkey ==9:
            return 'TRANSLATE_HAND_FIRE'
        elif AUTO_AIM_FINISH==1 and FAXIANDIJUN==1:
            return 'TRANSLATE_AUTO_FIRE'
        else:
            return'keep_auto_aim'

# define state Bar
class GIMBAL_AUTO_FIRE(smach.State):
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_AUTO_AIM','keep_auto_fire'])

    def execute(self, userdata):
        FAXIANDIJUN=FAXIANDIJUN1
        time.sleep(2)
        send_translation(5)
        rospy.loginfo('Executing state GIMBAL_AUTO_FIRE')
        if FAXIANDIJUN ==0:   
            return 'TRANSLATE_AUTO_AIM'
        else:
             return'keep_auto_fire'

class GIMBAL_AUTO_NINE(smach.State):
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_AUTO_AIM','keep_auto_nine'])

    def execute(self, userdata):
        GIMBAL_FINISH_ANGLE_NINE=GIMBAL_FINISH_ANGLE_NINE1
        time.sleep(2)
        send_translation(6)
        rospy.loginfo('Executing state GIMBAL_NINE')
        if GIMBAL_FINISH_ANGLE_NINE==1:
            translation=5   
            return 'TRANSLATE_AUTO_AIM'
        else:
             return'keep_auto_nine'

class GIMBAL_AUTO_HALF(smach.State):
    def send_translation(translation):
        data ={"translation":[translation]}
        data_string = json.dumps(data)
        ser.write('*'+ data_string +'!')
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_AUTO_AIM','keep_auto_half'])

    def execute(self, userdata):
        GIMBAL_FINISH_ANGLE_HALF= GIMBAL_FINISH_ANGLE_HALF1
        time.sleep(2)
        send_translation(7)
        rospy.loginfo('Executing state GIMBAL_AUTO_HALF')
        if GIMBAL_FINISH_ANGLE_HALF ==1: 
             translation=5  
             return 'TRANSLATE_AUTO_AIM'
        else:
             return'keep_auto_half'

class GIMBAL_HAND_FIRE(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_AUTO_AIM','keep_hand_fire'])

    def execute(self, userdata):
        getformkey=translation
        time.sleep(2)
        rospy.loginfo('Executing state GIMBAL_HAND_FIRE')
        if getformkey==5:   
             return 'TRANSLATE_AUTO_AIM'
        else:
             return'keep_hand_fire'

class GIMBAL_LOAD(smach.State):
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['TRANSLATE_AUTO_AIM','keep_load'])

    def execute(self, userdata):
        getformkey=translation
        rospy.loginfo("tanslation is:%d",translation)
        time.sleep(2)
        rospy.loginfo('Executing state GIMBAL_LOAD')
        if getformkey==5:   
             return 'TRANSLATE_AUTO_AIM'
        else:
             return'keep_load'
########################################################################################################################
####################################################################################################################################
################################################################################################################
########################################################################################################################################
#######################################################################################################

def gimbal(translation,GIMBAL_FINISH_ANGLE_NINE1,GIMBAL_FINISH_ANGLE_HALF1):
    gimbaltranslate = smach.StateMachine(outcomes=[])

    # Open the container
    with gimbaltranslate:
        # Add states to the container
        smach.StateMachine.add('GIMBAL_AUTO_AIM', GIMBAL_AUTO_AIM(),
                               transitions={'TRANSLATE_NINE':'GIMBAL_AUTO_NINE',
                                            'TRANSLATE_HALF':'GIMBAL_AUTO_HALF','TRANSLATE_AUTO_FIRE':'GIMBAL_AUTO_FIRE',
                                            'keep_auto_aim':'GIMBAL_AUTO_AIM','TRANSLATE_HAND_FIRE':'GIMBAL_HAND_FIRE',
                                            'TRANSLATE_LOAD':'GIMBAL_LOAD'})
        smach.StateMachine.add('GIMBAL_AUTO_FIRE', GIMBAL_AUTO_FIRE(),
                               transitions={'TRANSLATE_AUTO_AIM':'GIMBAL_AUTO_AIM','keep_auto_fire':'GIMBAL_AUTO_FIRE'})
        smach.StateMachine.add('GIMBAL_AUTO_NINE', GIMBAL_AUTO_NINE(),
                               transitions={'TRANSLATE_AUTO_AIM':'GIMBAL_AUTO_AIM','keep_auto_nine':'GIMBAL_AUTO_NINE'})
        smach.StateMachine.add('GIMBAL_AUTO_HALF', GIMBAL_AUTO_HALF(),
                               transitions={'TRANSLATE_AUTO_AIM':'GIMBAL_AUTO_AIM','keep_auto_half':'GIMBAL_AUTO_HALF'})
        smach.StateMachine.add('GIMBAL_HAND_FIRE', GIMBAL_HAND_FIRE(),
                               transitions={'TRANSLATE_AUTO_AIM':'GIMBAL_AUTO_AIM','keep_hand_fire':'GIMBAL_HAND_FIRE'})
        smach.StateMachine.add('GIMBAL_LOAD', GIMBAL_LOAD(),
                               transitions={'TRANSLATE_AUTO_AIM':'GIMBAL_AUTO_AIM','keep_load':'GIMBAL_LOAD'})
    # Create and start the introspection server
    sis = smach_ros.IntrospectionServer('my_smach_introspection_server', gimbaltranslate, '/GIMBAL_ROOT')
    sis.start()
    outcome = gimbaltranslate.execute()
    sis.stop()


def chassis(FAXIANDIJUN1,XUELIANGJIANSHAO1,SUIDONGWANCHENG1):
    
    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=[])

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('CHASSIS_NORMAL', CHASSIS_NORMAL(),
                               transitions={'outcome1':'CHASSIS_DODGE','keep_normal':'CHASSIS_NORMAL'})
        smach.StateMachine.add('CHASSIS_DODGE', CHASSIS_DODGE(),
                               transitions={'outcome2':'CHASSIS_FOLLOW','keep_dodge':'CHASSIS_DODGE'})
        smach.StateMachine.add('CHASSIS_FOLLOW', CHASSIS_FOLLOW(),
                               transitions={'outcome3':'CHASSIS_NORMAL','keep_follow':'CHASSIS_FOLLOW'})
    sis1 = smach_ros.IntrospectionServer('my_smach_introspection_server', sm, '/CHASSIS_ROOT')
    sis1.start()
    outcome1 = sm.execute()
    sis1.stop()


try:
    ser = serial.Serial(port=port, baudrate=115200, timeout=5)
except serial.serialutil.SerialException:
    rospy.logerr("Dji not found at port "+port + ". Did you specify the correct port in the launch file?")
    sys.exit(0)

#ser.write('t\n')


rospy.init_node('serial', anonymous=True)

def main():
    def callback1(angle):
        global pitch
        global yaw
        global s
        global FAXIANDIJUN1
        global XUELIANGJIANSHAO1
        pitch=10*angle.pitch
        yaw=10*angle.yaw
        z=angle.s
        send_gimbal(int(pitch),int(yaw))
    
    def callback2(translate):
        global translation
        transform =translate.data
        rospy.loginfo("translation is:%s",translate)
        rospy.loginfo("translation is:11111111111111111111111111111111111111111111111")
        transform=transform.strip()
   
        if transform=="chassis_motion":   #爬坡
             translation=3
             send_translation(translation)
        if transform=="load":  #装载
            translation=6
        if transform=="gimbal_auto_aim":  #装载
            translation=5

        if transform=="gimbal_turn":  #快速回头
            translation=7
     
        if transform=="gimbal_side": #90度
            translation=8

        if transform=="gimbal_hand": #手动单
            translation=9
            send_translation(translation)

        if transform=="gimbal_shand": #手动3连
             translation=10
             send_translation(translation)
        getformkey = translation
    def callback3(twist):
        speed_x = twist.linear.x
        speed_y = twist.linear.y
        speed_z = twist.angular.z
        rospy.loginfo("linear_x: %f",speed_x)
        send_chassis(int(speed_x),int(speed_y),int(speed_z))

    rospy.Subscriber("control",angle, callback1)
    rospy.Subscriber("schemaTranslation",String, callback2)
    rospy.Subscriber('teleop_twist', Twist, callback3)
        #rospy.loginfo("111111111111111111111111111")
    #rospy.spin()
        

#t1 = Process(target=main())
#t2 = Process(target=gimbal)
#t3 = Process(target=chassis)
#t1.join
#t1.daemon = True
#t1.start()
#t2.start()
#t3.start()

threads = []
t1 = threading.Thread(target=main)
threads.append(t1)
t2 = threading.Thread(target=chassis,args=(FAXIANDIJUN1,XUELIANGJIANSHAO1,SUIDONGWANCHENG1,))
threads.append(t2)
t3 = threading.Thread(target=gimbal,args=(translation,GIMBAL_FINISH_ANGLE_NINE1,GIMBAL_FINISH_ANGLE_HALF1,))
threads.append(t3)
if __name__=='__main__':
    for t in threads:
        t.start()
    for t in threads:
        t.join()

  


while not rospy.is_shutdown():
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

#关闭节点时先按control-s再按control-c
