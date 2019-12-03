由于视觉功能包使用制导功能包内的消息。要修改视觉的cmakelist和package.xml//具体参照https://blog.csdn.net/qq_16775293/article/details/80597763
package.xml添加：<build_depend>B_package</build_depend>
cmakelist添加：find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs  aim )
include_directories(include ${catkin_INCLUDE_DIRS})

hkvs内已修改过
clone后修改cmakelist和package.xml为自己的包名
hkvs内hkvs_light.cpp内头文件引用改为制导功能包
