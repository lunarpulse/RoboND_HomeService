#!/bin/sh
SRC_DIR=`pwd`
TURTLEBOT_GAZEBO_WORLD_FILE=${SRC_DIR}/src/World/WindMill/WindMill.world

xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch scan_height:=20" &
sleep 5
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=$(rospack find wall_follower)/launch/gmapping.launch" &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " rosrun wall_follower wall_follower_node" 
