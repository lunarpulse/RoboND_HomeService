#!/bin/sh
SRC_DIR=`pwd`
TURTLEBOT_GAZEBO_WORLD_FILE=${SRC_DIR}/src/World/WindMill/WindMill.world
TURTLEBOT_GAZEBO_MAP_FILE=${SRC_DIR}/src/World/WindMill/WindMill.yaml
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" 
