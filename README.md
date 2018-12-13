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
```

### Edit *_node.cpp

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

## pick_objects

### Make Pkg

```
cd ~/catkin/src
catkin_create_pkg pick_objects roscpp move_base_msgs actionlib
```

### Edit *_node.cpp

add `./src/pick_objects/src/pick_objects_node.cpp`

get the goal 1 and goal 2 from rviz click goal and see on the terminal with `rostopic echo /move_base/current_goal -n1`

### Edit CMakeLists
edit `./src/pick_objects/CMakeLists.txt`
  * uncomment ln 119 `include_driectories`
  * uncomment ln 134 `add_executable(${PROJECT_NAME}_node src/pick_objects_node.cpp)`
  * uncomment ln149 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### build Pkg
run 
```
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScrips/pick_objects.sh`

### Launch Pkg commands
- wall follower: `./src/ShellScripts/pick_objects.sh`

## add_markers

### Make Pkg

```
cd ~/catkin/src
catkin_create_pkg add_markers roscpp move_base_msgs actionlib
```

### Edit *_node.cpp

add `./src/add_markers/src/add_markers.cpp`

get the goal 1 and goal 2 from rviz click goal and see on the terminal with `rostopic echo /move_base/current_goal -n1`

### Edit CMakeLists
edit `./src/add_markers/CMakeLists.txt`
  * uncomment ln 119 `include_driectories`
  * uncomment ln 135 `add_executable(${PROJECT_NAME}_node src/add_markers.cpp)`
  * uncomment ln148 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### add rviz cfg
`./src/add_markers/rviz/add_markers_cfg.rviz`

### build Pkg
run 
```
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScrips/add_markers.sh`

### Launch Pkg commands
- wall follower: `./src/ShellScripts/add_markers.sh`



