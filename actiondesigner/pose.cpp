#include "pose.h"

Pose::Pose()
{
    this->name = "";
    this->reachtime = 0;
    this->body = 0;
    this->neck = 0;
    this->head = 0;
    this->tail = 0;

    this->leftShoulder = 0;
    this->rightShoulder = 0;

    this->leftLargeArm = 0;
    this->rightLargeArm = 0;

    this->leftBrachialArm = 0;
    this->rightBrachialArm = 0;

    this->leftHip = 0;
    this->rightHip = 0;

    this->leftThigh = 0;
    this->rightThigh = 0;

    this->leftShank = 0;
    this->rightShank = 0;
}

Pose::Pose(const Pose &srcpose)
{
    this->name = srcpose.name;
    this->reachtime = srcpose.reachtime;
    this->body = srcpose.body;
    this->neck = srcpose.neck;
    this->head = srcpose.head;
    this->tail = srcpose.tail;

    this->leftShoulder = srcpose.leftShoulder;
    this->rightShoulder = srcpose.rightShoulder;

    this->leftLargeArm = srcpose.leftLargeArm;
    this->rightLargeArm = srcpose.rightLargeArm;

    this->leftBrachialArm = srcpose.leftBrachialArm;
    this->rightBrachialArm = srcpose.rightBrachialArm;

    this->leftHip = srcpose.leftHip;
    this->rightHip = srcpose.rightHip;

    this->leftThigh = srcpose.leftThigh;
    this->rightThigh = srcpose.rightThigh;

    this->leftShank = srcpose.leftShank;
    this->rightShank = srcpose.rightShank;
}

Pose::Pose(std::string name, double reachtime,
           double body, double neck, double head, double tail,
           double leftShoulder, double rightShoulder,
           double leftLargeArm, double rightLargeArm,
           double leftBrachialArm, double rightBrachialArm,
           double leftHip, double rightHip,
           double leftThigh, double rightThigh,
           double leftShank, double rightShank)
{
    this->name = name;
    this->reachtime = reachtime;
    this->body = body;
    this->neck = neck;
    this->head = head;
    this->tail = tail;

    this->leftShoulder = leftShoulder;
    this->rightShoulder = rightShoulder;

    this->leftLargeArm = leftLargeArm;
    this->rightLargeArm = rightLargeArm;

    this->leftBrachialArm = leftBrachialArm;
    this->rightBrachialArm = rightBrachialArm;

    this->leftHip = leftHip;
    this->rightHip = rightHip;

    this->leftThigh = leftThigh;
    this->rightThigh = rightThigh;

    this->leftShank = leftShank;
    this->rightShank = rightShank;
}

std::string Pose::getName() const
{
    return name;
}

void Pose::setName(const std::string &value)
{
    name = value;
}

float Pose::getReachtime() const
{
    return reachtime;
}

void Pose::setReachtime(float value)
{
    reachtime = value;
}

double Pose::getBody() const
{
    return body;
}

void Pose::setBody(double value)
{
    body = value;
}

double Pose::getNeck() const
{
    return neck;
}

void Pose::setNeck(double value)
{
    neck = value;
}

double Pose::getHead() const
{
    return head;
}

void Pose::setHead(double value)
{
    head = value;
}

double Pose::getTail() const
{
    return tail;
}

void Pose::setTail(double value)
{
    tail = value;
}

double Pose::getLeftShoulder() const
{
    return leftShoulder;
}

void Pose::setLeftShoulder(double value)
{
    leftShoulder = value;
}

double Pose::getRightShoulder() const
{
    return rightShoulder;
}

void Pose::setRightShoulder(double value)
{
    rightShoulder = value;
}

double Pose::getLeftLargeArm() const
{
    return leftLargeArm;
}

void Pose::setLeftLargeArm(double value)
{
    leftLargeArm = value;
}

double Pose::getRightLargeArm() const
{
    return rightLargeArm;
}

void Pose::setRightLargeArm(double value)
{
    rightLargeArm = value;
}

double Pose::getLeftBrachialArm() const
{
    return leftBrachialArm;
}

void Pose::setLeftBrachialArm(double value)
{
    leftBrachialArm = value;
}

double Pose::getRightBrachialArm() const
{
    return rightBrachialArm;
}

void Pose::setRightBrachialArm(double value)
{
    rightBrachialArm = value;
}

double Pose::getLeftHip() const
{
    return leftHip;
}

void Pose::setLeftHip(double value)
{
    leftHip = value;
}

double Pose::getRightHip() const
{
    return rightHip;
}

void Pose::setRightHip(double value)
{
    rightHip = value;
}

double Pose::getLeftThigh() const
{
    return leftThigh;
}

void Pose::setLeftThigh(double value)
{
    leftThigh = value;
}

double Pose::getRightThigh() const
{
    return rightThigh;
}

void Pose::setRightThigh(double value)
{
    rightThigh = value;
}

double Pose::getLeftShank() const
{
    return leftShank;
}

void Pose::setLeftShank(double value)
{
    leftShank = value;
}

double Pose::getRightShank() const
{
    return rightShank;
}

void Pose::setRightShank(double value)
{
    rightShank = value;
}
