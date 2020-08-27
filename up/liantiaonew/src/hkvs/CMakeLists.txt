cmake_minimum_required(VERSION 2.8.3)
project(hkvs)
find_package(catkin REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
find_package( OpenCV 3.3.0 REQUIRED )
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
   message_generation
)
add_message_files(
    FILES
    square.msg
    vel.msg
)
find_package(OpenCV REQUIRED)
generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS cv_bridge
                 std_msgs
                 roscpp
                 image_transport
                 message_generation
)


include_directories(
  include ${catkin_INCLUDE_DIRS}
          ${OpenCV_INCLUDE_DIRS}
# include
# ${catkin_INCLUDE_DIRS}
)
link_directories(/opt/MVS/lib/64)


add_executable(hkvs_pub
  src/hkvs_pub.cpp
)
add_dependencies(hkvs_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs_pub -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(ArmorDetector
  src/ArmorDetector.cpp
)
add_dependencies(ArmorDetector ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ArmorDetector -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(kuangjia
  src/kuangjia.cpp
)
add_dependencies(kuangjia ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(kuangjia -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(main
  src/main.cpp
)
add_dependencies(main ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(main -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(tyj
  src/tyj.cpp
)
add_dependencies(tyj ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(tyj -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
