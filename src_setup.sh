#!/bin/sh

sudo apt-get remove turtlebot-*

git clone https://github.com/ros-perception/slam_gmapping.git
git clone https://github.com/turtlebot/turtlebot_interactions.git
git clone https://github.com/turtlebot/turtlebot_simulator
git clone https://github.com/turtlebot/turtlebot

source ../devel/setup.bash
rosdep -i install turtlebot
rosdep -i install urtlebot_teleop
rosdep -i install turtlebot_gazebo
rosdep -i install turtlebot_interactions

cd ..
catkin_make
source devel/setup.bash
