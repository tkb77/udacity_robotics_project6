#!/bin/bash

xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/map/yutaWorld.world" &

xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch initial_pose_a:=-1.5708" &

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &

xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch"



