#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>
#include "pose.h"

class Action
{
public:
    Action();
    Action(std::string name, double time,std::vector<Pose> poseList);
    Action(const Action &action);

    std::string getName() const;
    void setName(const std::string &value);


    double getTime() const;
    void setTime(double value);

    std::vector<Pose> getPoseList() const;
    void setPoseList(const std::vector<Pose> &value);

private:
    std::string name; //Action的名字，用于显示按钮名字
    double time;  //Action持续时间。多个Pose连续运动所需要持续的总时间
    std::vector<Pose> poseList; //一个Action包含很多个Pose，这是链表的起始地址
};

#endif // ACTION_H
