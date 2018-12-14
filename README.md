# Home Service Turtle Project

## Description

This repository gives a complete commands to build a homeservice turtlebot, using SLAM, MCL, Path Planner, and other cosmetic C++ codes.

## Setup

```sh
cd ~/catkin_ws/src

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
```

## Test Slam

### build test_slam Pkg

run

```sh
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : ./src/ShellScripts/test_slam.sh

### Launch test_slam commands

- test slam: ./src/ShellScripts/test_slam.sh

## Wall follower

### Make wall_follower Pkg

```sh
cd ~/catkin/src
catkin_create_pkg wall_follower roscpp
```

### Edit wall_follower_node.cpp

add `./src/wall_follower/src/wall_follower_node.cpp`

### Edit wall_follower CMakeLists

edit `./src/wall_follower/CMakeLists.txt`

- uncomment ln8 `add_compile_options(-std=c++11)`
- uncomment ln 134 `add_executable(${PROJECT_NAME}_node src/wall_follower_node.cpp)`
- uncomment ln149 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### build wall_follower Pkg

run

```sh
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScripts/wall_follower.sh`

### Launch wall_follower Pkg commands

- wall follower: `./src/ShellScripts/wall_follower.sh`

### Caution

turn after a map registered during SLAM

## pick_objects

### Make pick_objects Pkg

```sh
cd ~/catkin/src
catkin_create_pkg pick_objects roscpp move_base_msgs actionlib
```

### Edit pick_objects_node.cpp

add `./src/pick_objects/src/pick_objects_node.cpp`

get the goal 1 and goal 2 from rviz click goal and see on the terminal with `rostopic echo /move_base/current_goal -n1`

### Edit pick_objects CMakeLists

edit `./src/pick_objects/CMakeLists.txt`

- uncomment ln 119 `include_driectories`
- uncomment ln 134 `add_executable(${PROJECT_NAME}_node src/pick_objects_node.cpp)`
- uncomment ln149 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### build pick_objects Pkg

run

```sh
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScripts/pick_objects.sh`

### Launch pick_objects Pkg commands

- wall follower: `./src/ShellScripts/pick_objects.sh`

## add_markers

### Make add_markers Pkg

```sh
cd ~/catkin/src
catkin_create_pkg add_markers roscpp move_base_msgs actionlib
```

### Edit add_markers_node.cpp

add `./src/add_markers/src/add_markers.cpp`

Modifed to show marker to the goal position

goal position, not picked up = showing object
while picked up an object, new goal position, = hide object until arrive
the goal and drop off
get the goal 1 and goal 2 from rviz click goal and see on the terminal with`rostopic echo /move_base/current_goal -n2` before issuing a goal in Rviz.

### Edit add_markers CMakeLists

edit `./src/add_markers/CMakeLists.txt`

- uncomment ln 119 `include_driectories`
- uncomment ln 135 `add_executable(${PROJECT_NAME}_node src/add_markers.cpp)`
- uncomment ln148 `target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )`

### add rviz cfg

`./src/add_markers/rviz/add_markers_cfg.rviz`

### build add_markers Pkg

run

```sh
cd ~/catkin/src
catkin_make clean && catkin_make && source devel/setup.bash

```

add launch file : `./src/ShellScripts/add_markers.sh`

### Launch add_markers Pkg commands

- wall follower: `./src/ShellScripts/add_markers.sh`

## home_service Methods

 1. make a building in gazebo edit building
 2. run `wall_follower.sh` to SLAM and create map and save it to ./WORLD/ by `rosrun map_server map_saver -f WindMill`
 3. run `pick_objects.sh` to get new goal position in rviz by 2d goal command and `rostopic info /move_base/current_goal -n2`
 4. run 'home_service.sh` to see it picks up at goal 1 and drops to goal 2.

add launch file : `./src/shellscripts/home_service.sh`

### launch home_service commands

- wall follower: `./src/shellscripts/home_service.sh`
