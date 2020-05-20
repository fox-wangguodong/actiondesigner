#ifndef POSE_H
#define POSE_H

#include <string>

class Pose
{
public:
    Pose();
    Pose(std::string name,double reachtime,
         double body, double neck, double head, double tail,
         double leftShoulder, double rightShoulder,
         double leftLargeArm, double rightLargeArm,
         double leftBrachialArm, double rightBrachialArm,
         double leftHip, double rightHip,
         double leftThigh,double rightThigh,
         double leftShank,double rightShank);
    Pose(const Pose &srcpose);


    std::string getName() const;
    void setName(const std::string &value);


    float getReachtime() const;
    void setReachtime(float value);



    double getBody() const;
    void setBody(double value);

    double getNeck() const;
    void setNeck(double value);

    double getHead() const;
    void setHead(double value);

    double getTail() const;
    void setTail(double value);

    double getLeftShoulder() const;
    void setLeftShoulder(double value);

    double getRightShoulder() const;
    void setRightShoulder(double value);

    double getLeftLargeArm() const;
    void setLeftLargeArm(double value);

    double getRightLargeArm() const;
    void setRightLargeArm(double value);

    double getLeftBrachialArm() const;
    void setLeftBrachialArm(double value);

    double getRightBrachialArm() const;
    void setRightBrachialArm(double value);

    double getLeftHip() const;
    void setLeftHip(double value);

    double getRightHip() const;
    void setRightHip(double value);

    double getLeftThigh() const;
    void setLeftThigh(double value);

    double getRightThigh() const;
    void setRightThigh(double value);

    double getLeftShank() const;
    void setLeftShank(double value);

    double getRightShank() const;
    void setRightShank(double value);

private:
    std::string name;//Pose名字，用于显示Pose按钮上的字
    float reachtime;// 到达这一个Pose所用的时间

    double body;
    double neck;
    double head;
    double tail;

    double leftShoulder;
    double rightShoulder;

    double leftLargeArm;
    double rightLargeArm;

    double leftBrachialArm;
    double rightBrachialArm;

    double leftHip;
    double rightHip;

    double leftThigh;
    double rightThigh;

    double leftShank;
    double rightShank;
};

#endif // POSE_H
