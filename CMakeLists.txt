cmake_minimum_required(VERSION 3.0.2)
project(gazebo_world_api)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  gazebo_msgs
  geometry_msgs
  roscpp
  message_generation
)

find_package(gazebo REQUIRED)

add_service_files(
  FILES
  SpawnModels.srv
  DeleteModels.srv
)
generate_messages(
  DEPENDENCIES
  std_msgs 
  geometry_msgs
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
  gazebo_world_api_plugin
  CATKIN_DEPENDS
    gazebo_ros
    gazebo_msgs
    roscpp
    geometry_msgs
    message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

link_directories(${GAZEBO_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(gazebo_world_api_plugin src/gazebo_world_api_plugin.cpp)
target_link_libraries(gazebo_world_api_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})

install(TARGETS
    gazebo_world_api_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)