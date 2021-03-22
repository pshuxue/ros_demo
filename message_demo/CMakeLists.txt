cmake_minimum_required(VERSION 3.0.2)
project(message_demo)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  cv_bridge
  sensor_msgs
)

add_message_files(
  FILES
  Test.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
  )

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(message_pub_test src/message_pub_test.cpp)
target_link_libraries(message_pub_test ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(message_sub_test src/message_sub_test.cpp)
target_link_libraries(message_sub_test ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})