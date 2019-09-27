# Move to goals and Rotate
operates turtlebot3 in ROS

You have to make a file("move2goals_node_data.txt").

There is a necessary components.
1) Numbers of goal.
2) Data of goals (position.x position.y orientation.z orientation.w)
   Separator is a space.

If you finish here, Try roslaunch turtlebot3_navigation and rosrun move2goals_node.

Turtlebot3 will round the goals and rotate 10 secs when it arrived the goal.
