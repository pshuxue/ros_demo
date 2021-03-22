cmake_minimum_required(VERSION 2.8.3)
project(visual_demo)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs
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
   CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs  message_runtime
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

#opencv
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set( THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${catkin_LIBRARIES}
        )

add_executable(visual_voxel_node src/visual/visual_voxel_node.cpp)
target_link_libraries(visual_voxel_node ${THIRD_PARTY_LIBS})

add_executable(visual_img_node src/visual/visual_img_node.cpp)
target_link_libraries(visual_img_node ${THIRD_PARTY_LIBS})
