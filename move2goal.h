#ifndef MOVE2GOAL_H
#define MOVE2GOAL_H

#include <ros/ros.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>

#define TIME 10

using namespace std;

class Pose {
    friend class Path;
private:
    float x;
    float y;
    float z;
    float w;
    class Pose *link;
public:
    Pose(float xx=0, float yy=0, float zz=0, float ww=1)
    { x = xx; y = yy; z = zz; w = ww; link=0; }
};

class Path{
private:
    class Pose *first;
    class Pose *last;
    class Pose *point;
    void Pathplan();
    void Push(const float &xx, const float &yy, const float &zz, const float &ww);
public:
    Path() { first=0; last=0; point=0; Pathplan(); }
    float returnvar(const int num) {
        float temp;
        if (num == 0) { temp = point->x; }
        else if (num == 1) { temp = point->y; }
        else if (num == 2) { temp = point->z; }
        else if (num == 3) { temp = point->w; }
        return temp;
    }
    void Pluspoint();
};

void Path::Push(const float &xx, const float &yy, const float &zz, const float &ww)
// x, y, z, w data saved to linked list
{
    if (first) {
        last->link = new Pose(xx, yy, zz, ww);
        last = last->link;
        last->link = first;
    }
    else {
      first = new Pose(xx, yy, zz, ww);
      last = first;
      point = first;
      last->link = first;
    }
}

void Path::Pluspoint()
// change the point to point next goal data
{
    point = point->link;
}

void Path::Pathplan()
// read numbers of goal and data of goals
{
    float x, y, z, w;
    int n;

    string filePath = "move2goals_node_data.txt";
    ifstream openFile(filePath.data());

    if (openFile.is_open()) {
        openFile >> n;
        for (int i = 0; i < n; i++) {
          openFile >> x >> y >> z >> w;
          Push(x, y, z, w);
        }
        openFile.close();
    }
    else {
        ROS_ERROR("NO FILE");
    }
}

#endif // MOVE2GOAL_H
