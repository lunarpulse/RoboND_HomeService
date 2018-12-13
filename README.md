# Setup

```
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
```

## Test Slam

### build Pkg
run 
```
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```
add launch file : ./src/ShellScrips/test_slam.sh

### Launch commands
- test slam: ./src/ShellScripts/test_slam.sh

## Wall follower

### Make Pkg
```
cd ~/catkin/src
catkin_create_pkg wall_follower roscpp

### Edit *_node.cpp
```
add `./src/wall_follower/src/wall_follower_node.cpp`


### Edit CMakeLists
edit `./src/wall_follower/CMakeLists.txt`

  * uncomment ln8 `add_compile_options(-std=c++11)`
  * uncomment ln 134 `add_executable(${PROJECT_NAME}_node src/wall_follower_node.cpp)`
  * uncomment ln149 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### build Pkg
run 
```
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScrips/wall_follower.sh`

### Launch Pkg commands
- wall follower: `./src/ShellScripts/wall_follower.sh`
### Caution
turn after a map registered during SLAM
