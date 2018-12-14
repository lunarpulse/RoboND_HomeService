#!/bin/sh
SRC_DIR=`pwd`
TURTLEBOT_GAZEBO_WORLD_FILE=${SRC_DIR}/src/World/WindMill/WindMill.world
TURTLEBOT_GAZEBO_MAP_FILE=${SRC_DIR}/src/World/WindMill/WindMill.yaml
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e " roslaunch add_markers view_markers.launch" &
sleep 5
xterm -e " rosrun add_markers add_markers_node" 
