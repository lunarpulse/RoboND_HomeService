#!/bin/sh

sudo apt-get remove turtlebot-*

git clone --recurse-submodules -j8 https://github.com/lunarpulse/RoboND_HomeService.git
or
git clone --recurse-submodules -j8 git@lunarpulse.dynu.net:Robotics/homeserviceturtle.git

source ../devel/setup.bash

rosdep -i install turtlebot
rosdep -i install urtlebot_teleop
rosdep -i install turtlebot_gazebo
rosdep -i install turtlebot_interactions

cd ..
catkin_make or catkin build
source devel/setup.bash or source devel_cb/setup.bash



