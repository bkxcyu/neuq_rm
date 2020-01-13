#!/usr/bin/env python 
import roslib
#roslib.load_manifest('learning_tf')
import rospy
import tf
import math
from geometry_msgs.msg import Twist
from visualization_msgs.msg import *
from geometry_msgs.msg import Point

current_time=0
last_time=0
delta_time=0
x=0
y=0
thetachassis=0
angular_z=0
twist_x=0
position_x =1
position_y =2
position_z =3
zs_x=0
zs_y=0
zx_x=0
zx_y=0
ys_x=0
ys_y=0
yx_x=0
yx_y=0
def callback(twist):
    global twist_x
    global angular_z
    twist_x = twist.linear.x
    angular_z = twist.angular.z
    #rospy.loginfo("%f",twist.linear.x)
    #rospy.loginfo("%f",twist_x)
    #rospy.loginfo("%f",angular_z)  
def positioncallback(position):
	global position_x
	global position_y
	global position_z
	position_x = point.x
	position_y = point.y
	position_z = point.z
def linecallback(square):
	global zs_x
	global zs_y
	global ys_x
	global ys_y
	global yx_x
	global yx_y
	global zx_x
	global zx_y
	zs_x=square.zs_x
	zs_y=square.zs_y
	zx_x=square.zx_x
	zx_y=square.zx_y
	yx_x=square.yx_x
	yx_y=square.yx_y
	ys_x=square.ys_x
	ys_y=square.ys_y




if __name__=="__main__":
	rospy.init_node('my_tf_broadcaster')
	rospy.Subscriber('cmd_vel', Twist, callback)
	topic = 'visualization_marker_array'
	topic2 = 'visualization_marker_line'
	publisher = rospy.Publisher(topic, MarkerArray,queue_size = 100)
	markerArray = MarkerArray()
	publisherline = rospy.Publisher(topic2, Marker,queue_size = 100)
	#count = 0
	#MARKERS_MAX = 100
	rospy.Subscriber("point3d", Point, positioncallback)
	while not rospy.is_shutdown():
		##the position of target
		marker = Marker()
		marker.header.frame_id = "/world"
		marker.type = marker.SPHERE
		#marker.action = marker.ADD
		marker.scale.x = 0.2
		marker.scale.y = 0.2
		marker.scale.z = 0.2
		marker.color.a = 1.0
		marker.color.r = 1.0
		marker.color.g = 1.0
		marker.color.b = 0.0
		marker.pose.orientation.w = 1.0
		marker.pose.position.x = position_x#math.cos(count / 50.0)
		marker.pose.position.y = position_y#math.cos(count / 40.0) 
		marker.pose.position.z = position_z#math.cos(count / 30.0) 
		# We add the new marker to the MarkerArray, removing the oldest
		# marker from it when necessary
		#if(count > MARKERS_MAX):
			#markerArray.markers.pop(0)
		markerArray.markers.append(marker)
		# Renumber the marker IDs
		marker.id = 0
		#for m in markerArray.markers:
			#m.id = id
			#id += 1
		# Publish the MarkerArray
		publisher.publish(markerArray)
		#count += 1

		
		#draw square lines hpljy
		line_list = Marker()
		line_list.header.frame_id = "/world"
		line_list.type = marker.LINE_LIST
		line_list.action = marker.ADD
		line_list.scale.x = 0.02
		line_list.scale.y = 0.02
		line_list.scale.z = 0.02
		line_list.color.a = 5.0
		line_list.color.r = 15.0
		line_list.color.g = 15.0
		line_list.color.b = 5.0
		line_list.pose.orientation.w = 1.0
		line_list.id=1
		# marker position
		# marker line points
		line_list.points = []
		# first point
		first_line_point = Point()
		first_line_point.x = zs_x
		first_line_point.y = zx_y
		first_line_point.z = 3
		line_list.points.append(first_line_point)
		# second point
		second_line_point = Point()
		second_line_point.x = ys_x
		second_line_point.y = ys_y
		second_line_point.z = 6
		line_list.points.append(second_line_point)
		third_line_point = Point()
		third_line_point.x = yx_x
		third_line_point.y = yx_y
		third_line_point.z = 3
		line_list.points.append(third_line_point)
		forth_line_point = Point()
		forth_line_point.x = 2
		forth_line_point.y = 4
		forth_line_point.z = 5
		line_list.points.append(forth_line_point)
    # Publish the Marker
		publisherline.publish(line_list)
		#rospy.loginfo("%f",twist_x)
		#rospy.loginfo("%f",angular_z)



		last_time=current_time
		current_time = rospy.Time.now().to_sec()
		delta_time=current_time-last_time
		br1 = tf.TransformBroadcaster()
		br2 = tf.TransformBroadcaster()
		#theta=theta+angular_z*delta_time
		thetachassis=thetachassis+angular_z*delta_time
		#yaw=
		x=x+delta_time*twist_x*math.cos(thetachassis)
		y=y+delta_time*twist_x*math.sin(thetachassis)
		ninea_y=position_y-y
		ninea_x=position_x-x
		ninea_z=position_z
		rospy.loginfo("nine_y%f",ninea_y)
		theta=math.atan((ninea_y)/(ninea_x))
		if ninea_x<0 and ninea_y>0:
			theta = 3.1415926 + math.atan((ninea_y)/(ninea_x))
		if ninea_x<0 and ninea_y<0:
			theta = 3.1415926 + math.atan((ninea_y)/(ninea_x))
		if ninea_x>0 and ninea_y<0:
			theta =  math.atan((ninea_y)/(ninea_x))
		pitch = -3.1415926/2.0 + math.atan((ninea_z)/(ninea_y))
		rospy.loginfo("%f",theta)
			#rospy.loginfo("%f",delta_time)
			#rospy.loginfo("%f",theta)
			#rospy.loginfo("X%f",x)
		br1.sendTransform((x,y,1.0),
						tf.transformations.quaternion_from_euler(0, pitch,theta),
						rospy.Time.now(),
						"gimbal",
						"world")
		br2.sendTransform((x,y,0.0),
						tf.transformations.quaternion_from_euler(0, 0,thetachassis),
						rospy.Time.now(),
						"chassis",
						"world")
		rospy.sleep(0.01)

