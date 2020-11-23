cmake_minimum_required(VERSION 3.0)

project(rviz_visualization VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 ${CMAKE_CXX_FLAGS}")
add_compile_options(-std=c++11)

## find ros packages and combine them with catkin
SET(DEPEND_PKGS
		roslib
		roscpp
		std_msgs
		tf
)
 
FIND_PACKAGE(catkin REQUIRED COMPONENTS ${DEPEND_PKGS})

## find system depends libraries
#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

## ros specific cmake command
CATKIN_PACKAGE(
        INCLUDE_DIRS include
        CATKIN_DEPENDS ${DEPEND_PKGS}
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)
#####################################################################
####   add a ros node executable file
#####################################################################

ADD_LIBRARY(rviz_visualization
		src/rviz_visualization.cpp)

TARGET_LINK_LIBRARIES(rviz_visualization
		${catkin_LIBRARIES})

ADD_EXECUTABLE(rviz_visualization_demo_node
  src/rviz_visualization_demo.cpp)

TARGET_LINK_LIBRARIES(rviz_visualization_demo_node
  rviz_visualization
  ${catkin_LIBRARIES}
  )
