#!/bin/sh

xterm -e "source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5

SCRIPT_DIR="$(rospack find test_add_markers)"

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$SCRIPT_DIR/../map/yutaWorld.world" &

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$SCRIPT_DIR/../map/map.yaml  initial_pose_a:=-1.5708" &

sleep 5

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun test_add_markers test_add_markers_node"

