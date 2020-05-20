#include "action.h"

Action::Action()
{
    name = "";
    time = 0;
    poseList.clear();
}

Action::Action(std::string name, double time, std::vector<Pose> poseList)
{
    this->name = name;
    this->time = time;
    this->poseList =  poseList;
}

Action::Action(const Action &action)
{
    this->name = action.name;
    this->time =  action.time;
    this->poseList = action.poseList;
}

std::string Action::getName() const
{
    return name;
}

void Action::setName(const std::string &value)
{
    name = value;
}

double Action::getTime() const
{
    return time;
}

void Action::setTime(double value)
{
    time = value;
}

std::vector<Pose> Action::getPoseList() const
{
    return poseList;
}

void Action::setPoseList(const std::vector<Pose> &value)
{
    poseList = value;
}
