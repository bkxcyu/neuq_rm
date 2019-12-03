cmake_minimum_required(VERSION 2.8.3)
project(hkvs)
find_package(catkin REQUIRED)
find_package( OpenCV 3.3.0 REQUIRED )
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  message_generation
  aim
)

find_package(OpenCV REQUIRED)


catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS cv_bridge
                 std_msgs
                 roscpp
                 image_transport
                 
)

 


include_directories(
  include ${catkin_INCLUDE_DIRS}
          ${OpenCV_INCLUDE_DIRS}
# include
# ${catkin_INCLUDE_DIRS}
)
link_directories(/opt/MVS/lib/64)



add_executable(hkvs_sub
  src/hkvs_sub.cpp
)
add_dependencies(hkvs_sub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs_sub
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)


add_executable(hkvs_test
  src/hkvs_test.cpp
)
add_dependencies(hkvs_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs_test -lX11 -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
)

add_executable(ImageProcess
  src/ImageProcess.cpp
)
add_dependencies(ImageProcess ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ImageProcess -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)


add_executable(hkvs
  src/hkvs.cpp
)
add_dependencies(hkvs ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)


add_executable(circle
  src/circle.cpp
)
add_dependencies(circle ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(circle -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(hkvs_light
  src/hkvs_light.cpp
)
add_dependencies(hkvs_light ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs_light -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

add_executable(hkvs_pub
  src/hkvs_pub.cpp
)
add_dependencies(hkvs_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hkvs_pub -lMvCameraControl -lpthread
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)



