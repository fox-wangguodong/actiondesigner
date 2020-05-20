#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include "modeinverse.h"
#include "objloader.h"


#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <GL/glu.h> //若要使用gluPerspective函数则需引入该头文件


namespace Ui {
class OpenglView;
}


class OpenglView : public QOpenGLWidget , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenglView(QWidget *parent = 0);
    ~OpenglView();

    //void setPoseSettingWidget(PoseSettingWidget *posesettingWidget);


    ObjLoader body, //身体
    neck, // 脖子
    head,  // 头
    tail, //尾巴
    leftShoulder,rightShoulder, // 左右肩
    leftLargeArm, rightLargeArm, //左右大臂
    leftBrachialArm, rightBrachialArm, // 左右小臂
    leftHip, rightHip,   //左右胯
    leftThigh, rightThigh,  // 左右大腿
    leftShank, rightShank; // 左右小腿


    double g_HeadTheta, g_NeckTheta, // 头和脖子的角度
    g_dLFTheta1, g_dLFTheta2, g_dLFTheta3,	//左前腿三个伺服电机旋转的角度
    g_dRFTheta1, g_dRFTheta2, g_dRFTheta3,  //右前腿
    g_dLHTheta1, g_dLHTheta2, g_dLHTheta3, // 左后腿
    g_dRHTheta1, g_dRHTheta2, g_dRHTheta3;  // 右后腿

    ModeInverse modelInverse;

private:
    Ui::OpenglView *ui;

    /*列表索引号 ， 身体各个部分的绘图部分*/
    GLuint bodyList,
    neckList,
    headList,
    tailList,
    leftShoulderList,
    rightShoulderList,
    leftLargeArmList,
    rightLargeArmList,
    leftBrachialArmList,
    rightBrachialArmList,
    leftHipList,
    rightHipList,
    leftThighList,
    rightThighList,
    leftShankList,
    rightShankList;

    // opengl 光照
    GLfloat	 lightPos[4] = { 0.0f, 10.0f, 10.0f, 1.0f };  // 光源位置
    GLfloat  ambientLight[4] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 环境光
    GLfloat  diffuseLight[4] = { 0.7f, 0.7f, 0.7f, 1.0f }; // 漫射光
    GLfloat  specrefLight[4] = { 0.7f, 0.7f, 0.7f, 1.0f }; // 镜面光

    //相机位置
    double atX = 0;
    double atY = 0;
    double atZ = 500;

    double horizontal_offset = 0; // 水平偏移
    double vertical_offset = 0; // 垂直偏移

    double movedX_offset = 0;// X方向的移动量
    double movedY_offset = 0;// Y方向的移动量


    QPoint pressPos; // 鼠标按下时的点
    QPoint movedPos;// 鼠标移动位置

    int isPicked = 0;// 被选中的关节


    void processHits(GLint hits, GLuint buffer[]);



    GLuint texture[1]; //用来保存 纹理贴图


    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


    bool eventFilter(QObject *watched, QEvent *event);
};


#endif // OPENGLVIEW_H
