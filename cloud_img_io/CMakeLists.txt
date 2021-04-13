cmake_minimum_required(VERSION 2.8.3)
project(cloud_img_io)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rosbag
  std_msgs
  pcl_conversions
  cv_bridge
  image_transport
  message_generation
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES learning_topic
   CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs  message_runtime rosbag pcl_conversions
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

#opencv
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

set( THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${PCL_LIBS}
        ${catkin_LIBRARIES}
        )

add_executable(get_cloud_img_from_rosbag src/get_cloud_img_from_rosbag.cpp)
target_link_libraries(get_cloud_img_from_rosbag ${THIRD_PARTY_LIBS})
