/**************************************************************
 * Writer : HAN NU RIM
 * Date : 2019.09.27 FRI
 * Input : move2goals_node_data.txt
 *         1) Numbers of Goals
 *         2) Goals data (position x, y/orientation z, w)
 * Output : turtlebot3 will round the goals.
 *          and rotate 10 secs(TIME) when it arrived the goal.
 * ************************************************************/

#include "move2goal.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move2goals_node");
  ros::NodeHandle nh;

  ROS_INFO("move2goals_node start");

  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

  while(!ac.waitForServer(ros::Duration(5.0)))
          ROS_INFO("Waiting for the move_base action server to come up");

  move_base_msgs::MoveBaseGoal goalOutput;                          // have a goal data
  geometry_msgs::Twist velOutput;                                   // have a velocity data

  goalOutput.target_pose.header.frame_id = "map";
  velOutput.angular.z = -1;                                         // rotate to clockwise

  class Path p;

  while(ros::ok()) {

      goalOutput.target_pose.header.stamp = ros::Time::now();       // time stamp
      goalOutput.target_pose.pose.position.x = p.returnvar(0);      // input x position that you want
      goalOutput.target_pose.pose.position.y = p.returnvar(1);      // input y position that you want
      goalOutput.target_pose.pose.orientation.z = p.returnvar(2);   // input z orientation that you want
      goalOutput.target_pose.pose.orientation.w = p.returnvar(3);   // input w orientation that you want

      ac.sendGoal(goalOutput);
      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {   // if the robot reached a goal
         ROS_INFO("success!!");
         ros::Time start = ros::Time::now();                        // start time
         while(1) {
           pub.publish(velOutput);                                  // rotate velocity publish
           ros::Duration(1.0).sleep();                              // 1 secs sleep
           if (ros::Time::now() > start + ros::Duration(TIME))
           // 10 secs duration and if the robot reached initial orientation
           { break; }
         }
         p.Pluspoint();                                             // point will change next goal
      }

      ros::spinOnce();
  }

  return 0;
}

// practice github command
<<<<<<< HEAD
// add other change
=======
>>>>>>> 97b5bd614757e79d0b8502de7f4a7a47005b5fdc
