#include "openglview.h"
#include "ui_openglview.h"
#include <cmath>

#include <QDebug>
#include <QDir>
#include <QMouseEvent>


OpenglView::OpenglView(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::OpenglView)
{
    ui->setupUi(this);
    installEventFilter(this);
    setCursor(Qt::OpenHandCursor);


    //重置模型坐标位置
    modelInverse.ResetPosition();
    // 头
    modelInverse.GetHeadAngle(g_HeadTheta);
    //脖子
    modelInverse.GetNeckAngle(g_NeckTheta);
    g_NeckTheta = 30;
    //左前腿
    modelInverse.GetLFAngle(g_dLFTheta1,g_dLFTheta2,g_dLFTheta3);
    //右前腿
    modelInverse.GetRFAngle(g_dRFTheta1,g_dRFTheta2,g_dRFTheta3);
    // 左后腿
    modelInverse.GetLHAngle(g_dLHTheta1,g_dLHTheta2,g_dLHTheta3);
    // 右后腿
    modelInverse.GetRHAngle(g_dRHTheta1,g_dRHTheta2,g_dRHTheta3);
}

OpenglView::~OpenglView()
{
    removeEventFilter(this);
    delete ui;
}

bool OpenglView::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        if(mouseEvent->button() == Qt::LeftButton)
        {
            setCursor(Qt::ClosedHandCursor);
        }
        if(mouseEvent->button() == Qt::RightButton)
        {
            setCursor(Qt::PointingHandCursor);
        }
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        if(mouseEvent->button() == Qt::LeftButton)
        {
            setCursor(Qt::OpenHandCursor);
        }
        if(mouseEvent->button() == Qt::RightButton)
        {
            setCursor(Qt::PointingHandCursor);
        }
    }
    return QObject::eventFilter(watched,event);
}


void OpenglView::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL函数，否则在window下运行时会出现异常崩溃。

    glEnable( GL_DEPTH_TEST ); // 启用深度测试。(影响绘制深度)

    glEnable(GL_BLEND); //启用混合（将图形颜色同周围颜色相混合）
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);/*启用点抗锯齿*/
    glHint(GL_POINT_SMOOTH, GL_NICEST); //  GL_NICEST 图像质量优先
    glEnable(GL_LINE_SMOOTH);/*启用线抗锯齿*/
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);//  GL_NICEST 图像质量优先
    glEnable(GL_POLYGON_SMOOTH_HINT); /*启用多边形抗锯齿*/
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);//  GL_NICEST 图像质量优先

    glEnable(GL_NORMALIZE); // 启用规范化法向量
    glEnableClientState(GL_VERTEX_ARRAY); //启用客户端状态

    glFrontFace(GL_CCW);		//定义前面和背面多边形  Counter clock-wise polygons face out 逆时针为正面

    glClearColor(0.54509f, 0.77254f, 0.85882f, 0.0f);// 设置清屏时的颜色

    glEnable(GL_LIGHTING);//启用光照
    glEnable(GL_LIGHT1); // 启用光源1
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos); // 光照位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight); // 环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight); // 漫射光
    glLightfv(GL_LIGHT1, GL_SPECULAR, specrefLight); // 镜面光

    glEnable(GL_COLOR_MATERIAL);    //启用颜色追踪（这样环境光会影响材质的颜色）
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);// 设置材质属性来追踪当前颜色值
    glMaterialfv(GL_FRONT, GL_SPECULAR, specrefLight); // 为材料添加镜面反射属性
    glMateriali(GL_FRONT, GL_SHININESS, 100);// 指定镜面指数

    glShadeModel( GL_SMOOTH ); // 设置阴影平滑（smooth shading）
    glClearColor(0.0, 0.0, 0.0, 0.0f);// 设置清除屏幕时所用的颜色(颜色格式RGBA, 取值范围0~1)
    glClearDepth( 1.0 ); // 设置深度缓存。
    glDepthFunc( GL_LEQUAL ); // 所作深度测试的类型。
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); // 真正精细的透视修正。


    /*加载贴图*/
    QImage tex(":/img/ground.jpg"); // 加载一副图片
    glGenTextures( 1, &texture[0] ); // 开辟存储纹理的内存空间，texture为存储纹理的地址索引。
    glBindTexture( GL_TEXTURE_2D, texture[0] ); // 把存储纹理的对象texture绑定到纹理目标target上
    glTexImage2D( GL_TEXTURE_2D,  // 纹理目标
                  0,   // 目标的层次
                  3,   // 数据成分的个数
                  tex.width(),  // 纹理数据的宽
                  tex.height(), // 纹理数据的高
                  0,   // 边框的值
                  GL_RGBA,  //通道格式
                  GL_UNSIGNED_BYTE,  //纹理的数据元素类型
                  tex.bits()); // 数据内容
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );



    /*加载obj文件*/
    body.parse("./data/obj/body.obj"); //身体
    neck.parse("./data/obj/neck.obj"); //脖子
    head.parse("./data/obj/head.obj"); //头
    tail.parse("./data/obj/tail.obj"); //尾巴
    leftShoulder.parse("./data/obj/leftShoulder.obj");//左肩
    leftLargeArm.parse("./data/obj/leftLargeArm.obj");//左大臂
    leftBrachialArm.parse("./data/obj/leftBrachialArm.obj"); //左小臂
    rightShoulder.parse("./data/obj/rightShoulder.obj");//右肩
    rightLargeArm.parse("./data/obj/rightLargeArm.obj"); // 右大臂
    rightBrachialArm.parse("./data/obj/rightBrachialArm.obj");//右小臂
    leftHip.parse("./data/obj/leftHip.obj");//左跨
    leftThigh.parse("./data/obj/leftThigh.obj");//左大腿
    leftShank.parse("./data/obj/leftShank.obj");//左小腿
    rightHip.parse("./data/obj/rightHip.obj");   //右胯
    rightThigh.parse("./data/obj/rightThigh.obj");  //右大腿
    rightShank.parse("./data/obj/rightShank.obj"); //右小腿


    glMatrixMode( GL_MODELVIEW ); // 选择模型观察矩阵。
    glLoadIdentity(); // 恢复默认坐标系

    /*初始化索引列表*/
    bodyList = glGenLists(16);
    neckList = bodyList + 1;
    headList = neckList + 1;
    tailList = headList + 1;
    leftShoulderList = tailList + 1;
    rightShoulderList = leftShoulderList + 1;
    leftLargeArmList = rightShoulderList + 1;
    rightLargeArmList = leftLargeArmList + 1;
    leftBrachialArmList = rightLargeArmList + 1;
    rightBrachialArmList = leftBrachialArmList + 1;
    leftHipList = rightBrachialArmList + 1;
    rightHipList = leftHipList + 1;
    leftThighList = rightHipList + 1;
    rightThighList = leftThighList + 1;
    leftShankList = rightThighList + 1;
    rightShankList = leftShankList + 1;



    /*对各个列表的部分进行初始化*/
    glNewList(bodyList, GL_COMPILE);
    body.draw();
    glEndList();

    glNewList(neckList, GL_COMPILE);
    neck.draw();
    glEndList();

    glNewList(headList, GL_COMPILE);
    head.draw();
    glEndList();

    glNewList(tailList, GL_COMPILE);
    tail.draw();
    glEndList();

    glNewList(leftShoulderList, GL_COMPILE);
    leftShoulder.draw();
    glEndList();

    glNewList(rightShoulderList, GL_COMPILE);
    rightShoulder.draw();
    glEndList();

    glNewList(leftLargeArmList, GL_COMPILE);
    leftLargeArm.draw();
    glEndList();

    glNewList(rightLargeArmList, GL_COMPILE);
    rightLargeArm.draw();
    glEndList();

    glNewList(leftBrachialArmList, GL_COMPILE);
    leftBrachialArm.draw();
    glEndList();

    glNewList(rightBrachialArmList, GL_COMPILE);
    rightBrachialArm.draw();
    glEndList();

    glNewList(leftHipList, GL_COMPILE);
    leftHip.draw();
    glEndList();

    glNewList(rightHipList, GL_COMPILE);
    rightHip.draw();
    glEndList();

    glNewList(leftThighList, GL_COMPILE);
    leftThigh.draw();
    glEndList();

    glNewList(rightThighList, GL_COMPILE);
    rightThigh.draw();
    glEndList();

    glNewList(leftShankList, GL_COMPILE);
    leftShank.draw();
    glEndList();

    glNewList(rightShankList, GL_COMPILE);
    rightShank.draw();
    glEndList();
}


void OpenglView::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height ); // 重置当前的视口（Viewport）。
    glMatrixMode( GL_PROJECTION ); // 选择投影矩阵。
    glLoadIdentity(); // 重置投影矩阵。
    gluPerspective(
                60.0, // 视角角度大小
                (GLfloat)width/(GLfloat)height, // 窗口的宽高比例
                0.1, // 视角的最近距离
                2500.0 ); // 视角的最远距离

    glMatrixMode( GL_MODELVIEW ); // 选择模型观察矩阵。
    glLoadIdentity(); // 恢复默认坐标系
}

void OpenglView::paintGL()
{    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // 清屏、清除深度缓存
    glPushMatrix();

    gluLookAt(
        atX,atY,atZ, // 相机位置
        0,0,0,  // 目标位置
        0,1,0); // 相机头顶朝向


    glTranslated(0,-169,10);
    glEnable(GL_TEXTURE_2D);// 启用贴图
    glBindTexture( GL_TEXTURE_2D, texture[0] ); //使用纹理
    glBegin(GL_QUAD_STRIP);
    glTexCoord2f( 0.0, 0.0 ); // 设置纹理的左上角
    glVertex3f(1000,0,1000);
    glTexCoord2f( 1.0, 0.0 ); // 设置纹理的右上角
    glVertex3f(1000,0,-1000);
    glTexCoord2f( 1.0, 1.0 ); // 设置纹理的右下角
    glVertex3f(-1000,0,1000);
    glTexCoord2f( 0.0, 1.0 ); // 设置纹理的左下角
    glVertex3f(-1000,0,-1000);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glTranslated(0,169,10);

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,500,0);
    glVertex3f(0,-500,0);
    glEnd();

    glInitNames();// 初始化名称栈

    glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    glPushMatrix();
    glCallList(bodyList);	//绘制躯干
    glPopMatrix();

    glPushName(15);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-10, 116, 55);
    glRotatef(-90, 0, 0, 1);
    glRotatef(45, 0, 1, 0);
    if (isPicked == 15){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(tailList);		//绘制尾巴
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(tailList);		//绘制尾巴
    }
    glPopMatrix();
    glPopName();


    glPushName(14);
    glPushMatrix();
    glTranslatef(-99, 34, -10);
    glRotatef(g_NeckTheta, 0, 0, 1);//glRotatef(-30, 0, 1, 0);//
    if (isPicked == 14){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(neckList);   //绘制脖子
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(neckList);   //绘制脖子
    }
    glPopMatrix();
    glPopName();


    glPushName(13);
    glPushMatrix();
    glTranslatef(-98, 69, -10);
    glTranslatef(0,-35,0);
    glRotatef(g_NeckTheta, 0, 0, 1); //glRotatef(30, 0, 1, 0);//
    glTranslatef(0, 35, 0);
    glRotatef(g_HeadTheta, 0, 1, 0); //glRotatef(30, 0, 0, 1); //
    if (isPicked == 13){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(headList);   //绘制头部
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(headList);   //绘制头部
    }
    glPopMatrix();
    glPopName();


    glPushName(9);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(70, -75.5, -10);
    glRotatef(180, 0, 0, 1);
    glRotatef(g_dLFTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0);
    if (isPicked == 9){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftShoulderList);//绘制左肩
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftShoulderList);//绘制左肩
    }
    glPopMatrix();
    glPopName();


    glPushName(5);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(75, -75.5, -38);
    glRotatef(180, 0, 0, 1);
    glTranslatef(0, 0, 28);
    glRotatef(g_dLFTheta1, 1, 0, 0); //glRotatef(50, 1, 0, 0);//
    glRotatef(g_dLFTheta2, 0, 1, 0);//glRotatef(30, 0, 1, 0);//
    glTranslatef(0, 0, -28);
    if (isPicked == 5){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftLargeArmList);//绘制左大臂
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftLargeArmList);//绘制左大臂
    }
    glPopMatrix();
    glPopName();


    glPushName(1);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(75, -75.5, -38);
    glRotatef(180, 0, 0, 1);
    glTranslatef(0, 0, 28);
    glRotatef(g_dLFTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0);//
    glRotatef(g_dLFTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0);//
    glTranslatef(-46, 0, -74);
    glRotatef(g_dLFTheta3, 1, 0, 0);//glRotatef(30, 1, 0, 0); //
    glTranslatef(46, 0, 74);
    glTranslatef(0, 0, -28);
    if (isPicked == 1){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftBrachialArmList);//绘制左小臂
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftBrachialArmList);//绘制左小臂
    }
    glPopMatrix();
    glPopName();

    glPushName(10);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-90, -75.5, -10);
    glRotatef(g_dRFTheta1, 1, 0, 0);//glRotatef(-50, 1, 0, 0);  //
    if (isPicked == 10){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(rightShoulderList);//绘制右肩
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightShoulderList);//绘制右肩
    }
    glPopMatrix();
    glPopName();

    glPushName(6);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-95, -75.5, -38);
    glTranslatef(0, 0, 28);
    glRotatef(g_dRFTheta1, 1, 0, 0);//glRotatef(-50, 1, 0, 0);  //
    glRotatef(g_dRFTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0);  //
    glTranslatef(0, 0, -28);
    if (isPicked == 6){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(rightLargeArmList);//绘制右大臂
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightLargeArmList);//绘制右大臂
    }
    glPopMatrix();
    glPopName();


    glPushName(2);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-95, -75.5, -38);
    glTranslatef(0, 0, 28);
    glRotatef(g_dRFTheta1, 1, 0, 0);//glRotatef(-50, 1, 0, 0);  //
    glRotatef(g_dRFTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0);  //
    glTranslatef(-46, 0, -74);
    glRotatef(g_dRFTheta3, 1, 0, 0); //glRotatef(-30, 1, 0, 0);  //
    glTranslatef(46, 0, 74);
    glTranslatef(0, 0, -28);
    if (isPicked == 2){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(rightBrachialArmList);//绘制右小臂
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightBrachialArmList);//绘制右小臂
    }
    glPopMatrix();
    glPopName();

    glPushName(11);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(70, 74.75, -10);
    glRotatef(180, 0, 0, 1);
    glRotatef(g_dLHTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0);//
    if (isPicked == 11){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftHipList);//绘制左胯
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftHipList);//绘制左胯
    }
    glPopMatrix();
    glPopName();


    glPushName(7);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(75, 74.75, -38);
    glRotatef(180, 0, 0, 1);
    glTranslatef(0, 0, 28);
    glRotatef(g_dLHTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0); //
    glRotatef(g_dLHTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0); //
    glTranslatef(0, 0, -28);
    if (isPicked == 7){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftThighList);//绘制左大腿
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftThighList);//绘制左大腿
    }
    glPopMatrix();
    glPopName();


    glPushName(3);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(75, 74.75, -38);
    glRotatef(180, 0, 0, 1);
    glTranslatef(0, 0, 28);
    glRotatef(g_dLHTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0); //
    glRotatef(g_dLHTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0); //
    glTranslatef(-46, 0, -74);
    glRotatef(g_dLHTheta3, 1, 0, 0);//glRotatef(30, 1, 0, 0);//
    glTranslatef(46, 0, 74);
    glTranslatef(0, 0, -28);
    if (isPicked == 3){
        glColor3f(0.0f, 0.0f, 0.7f); // 设置模型身体着色颜色
        glCallList(leftShankList);//绘制左小腿
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(leftShankList);//绘制左小腿
    }
    glPopMatrix();
    glPopName();


    glPushName(12);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-90, 74.75, -10);
    glRotatef(g_dRHTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0);  //
    if (isPicked == 12){
        glColor3f(0.067f, 0.067f, 0.58f); // 设置模型身体着色颜色
        glCallList(rightHipList);//绘制右胯
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightHipList);//绘制右胯
    }
    glPopMatrix();
    glPopName();


    glPushName(8);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-95, 75.5, -38);
    glTranslatef(0, 0, 28);
    glRotatef(g_dRHTheta1, 1, 0, 0); //glRotatef(50, 1, 0, 0);  //
    glRotatef(g_dRHTheta2, 0, 1, 0); //glRotatef(20, 0, 1, 0);  //
    glTranslatef(0, 0, -28);
    if (isPicked == 8){
        glColor3f(0.067f, 0.067f, 0.58f); // 设置模型身体着色颜色
        glCallList(rightThighList);//绘制右大腿
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightThighList);//绘制右大腿
    }
    glPopMatrix();
    glPopName();


    glPushName(4);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-95, 75.5, -38);
    glTranslatef(0, 0, 28);
    glRotatef(g_dRHTheta1, 1, 0, 0);//glRotatef(50, 1, 0, 0);  //
    glRotatef(g_dRHTheta2, 0, 1, 0);//glRotatef(20, 0, 1, 0);  //
    glTranslatef(-46, 0, -74);
    glRotatef(g_dRHTheta3, 1, 0, 0);//glRotatef(30, 1, 0, 0);  //
    glTranslatef(46, 0, 74);
    glTranslatef(0, 0, -28);
    if (isPicked == 4){
        glColor3f(0.067f, 0.067f, 0.58f); // 设置模型身体着色颜色
        glCallList(rightShankList);//绘制右小腿
        glColor3f(0.9f, 0.9f, 0.9f); // 设置模型身体着色颜色
    }
    else
    {
        glCallList(rightShankList);//绘制右小腿
    }
    glPopMatrix();
    glPopName();


    glPopMatrix();
}

void OpenglView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        pressPos = event->pos();
    }
    else if(event->button() == Qt::RightButton)
    {
        pressPos = event->pos();// 获取鼠标位置

        unsigned int selectBuf[255];
        glSelectBuffer (255, selectBuf);//设置选中缓冲区

        glRenderMode(GL_SELECT);// 设置拾取模式


        glMatrixMode(GL_PROJECTION); //切换到投影矩阵
        glLoadIdentity();

        //创建一个以光标为中心的2*2的拾取区域
        GLint viewport[4] = { 0,0,this->width(),this->height() };
        gluPickMatrix(
            (GLdouble) pressPos.x(),
            (GLdouble) viewport[3] - pressPos.y(),/*将窗口坐标转换到opengl视图坐标*/
            2,
            2,
            viewport);

        /*设置投影*/
        gluPerspective(
            60.0f,
            this->width() / (GLfloat)(this->height()),
            0.1,
            2000.0);

        glMatrixMode(GL_MODELVIEW); // 切换到模型矩阵
        paintGL(); // 绘制物体
        glFlush();// 刷新Opengl

        GLint hits = glRenderMode(GL_RENDER);	// 返回正常的绘制模式，hits 中保留击中信息
        processHits(hits,selectBuf);
        qDebug()<<isPicked;
    }
    update();
}

void OpenglView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint releasePoint = event->pos() - pressPos; // 获取这一次拖拽的偏移量
        horizontal_offset += releasePoint.x(); // 累加水平偏移量
        vertical_offset += releasePoint.y(); // 累加垂直偏移量
    }
    else if(event->button() == Qt::RightButton)
    {
        movedPos = event->pos();
    }
}

void OpenglView::processHits(GLint hits, GLuint buffer[])
{
    GLuint hitName = 0;
    GLuint hitMinZ = 0xffffffff;

    GLuint *ptr = (GLuint *) buffer;
    for (GLint i = 0; i < hits; i++)
    {
        GLuint numberOfNames = *ptr;
        ptr++;
        GLuint minZ = *ptr;
        ptr++;
        GLuint maxZ = *ptr;
        ptr++;

        GLuint *names = new GLuint(numberOfNames);
        for(GLuint j=0;j<numberOfNames;j++)
        {
            *(names+j) = *ptr;
            ptr++;
        }

        if(minZ < hitMinZ){
            hitName = *names;
            hitMinZ = minZ;
        }

        delete names;
    }

    isPicked = hitName;//取出被击中的名字
}

void OpenglView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) // 改变相机视角
    {
        QPoint currentOffset =  event->pos() - pressPos; // 当前的偏移量
        float all_horizontal_offset = currentOffset.x() + horizontal_offset;
        float all_vertical_offset = currentOffset.y() + vertical_offset;
        float R = sqrt(atX*atX + atZ*atZ); // 球半径
        float theta = - all_horizontal_offset / R; //计算水平旋转角度（theta = l / r）
        float delta = all_vertical_offset / R; //计算垂直旋转角度( -90 ~ 90 )（delta = l / r）

        atZ =  R * cos(theta);
        atX =  R * sin(theta);
        atY = R * sin(delta);
    }
    else if(event->buttons() == Qt::RightButton) // 拖动模型
    {
        QPoint currentOffset =  event->pos() - pressPos; // 当前的偏移量
        float all_horizontal_offset = currentOffset.x() + horizontal_offset;
        float R = sqrt(atX*atX + atZ*atZ); // 球半径
        float theta = - all_horizontal_offset / R; //计算水平旋转角度（theta = l / r）

        float angle = theta / 3.1415926 * 180; //计算当前视角角度，将弧度转换为角度
        //获取鼠标移动的偏移量
        QPoint movedOffset = event->pos() - movedPos;
        movedPos = event->pos();
        if(isPicked == 1)
        {
            if ( (angle < 45 && angle >= 0) || angle >= 315){
                modelInverse.g_dLFPositionX -= (movedOffset.x() * (R - 84) / (500.0 - 84));
                modelInverse.g_dLFPositionZ -= (movedOffset.y() * (R - 84) / (500.0 - 84));
            }
            if (angle >= 45 && angle < 135){
                modelInverse.g_dLFPositionY += (movedOffset.x() * (R - 70) / (500.0 - 70));
                modelInverse.g_dLFPositionZ -= (movedOffset.y() * (R - 70) / (500.0 - 70));
            }
            if (angle >= 135 && angle < 225){
                modelInverse.g_dLFPositionX += (movedOffset.x() * (R + 84) / (500.0 + 84));
                modelInverse.g_dLFPositionZ -= (movedOffset.y() * (R + 84) / (500.0 + 84));
            }
            if (angle >= 225 && angle < 315){
                modelInverse.g_dLFPositionY -= (movedOffset.x() * (R + 70) / (500.0 + 70));
                modelInverse.g_dLFPositionZ -= (movedOffset.y() * (R + 70) / (500.0 + 70));
            }
            //左前腿
            modelInverse.GetLFAngle(g_dLFTheta1,g_dLFTheta2,g_dLFTheta3);

            g_dLFTheta1 = -g_dLFTheta1;
            g_dLFTheta3 = -g_dLFTheta3;
            g_dLFTheta2 = g_dLFTheta2;
        }
        else if(isPicked == 2)
        {
            if ((angle < 45 && angle >= 0) || angle >= 315){
                modelInverse.g_dRFPositionX -= (movedOffset.x() * (R + 150) / (500.0 + 150));
                modelInverse.g_dRFPositionZ -= (movedOffset.y() * (R + 150) / (500.0 + 150));
            }
            if (angle >= 45 && angle < 135){
                modelInverse.g_dRFPositionY += (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dRFPositionZ -= (movedOffset.y() * (R - 150) / (500.0 - 150));
            }
            if (angle >= 135 && angle < 225){
                modelInverse.g_dRFPositionX += (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dRFPositionZ -= (movedOffset.y() * (R - 150) / (500.0 - 150));
            }
            if (angle >= 225 && angle < 315){
                modelInverse.g_dRFPositionY -= (movedOffset.x() * (R + 150) / (500.0 + 150));
                modelInverse.g_dRFPositionZ -= (movedOffset.y() * (R + 150) / (500.0 + 150));
            }
            //右前腿
            modelInverse.GetRFAngle(g_dRFTheta1,g_dRFTheta2,g_dRFTheta3);

            g_dRFTheta1 = g_dRFTheta1;
            g_dRFTheta3 = g_dRFTheta3;
            g_dRFTheta2 = -g_dRFTheta2;
        }
        else if(isPicked == 3)
        {
            if ((angle < 45 && angle >= 0) || angle >= 315){
                modelInverse.g_dLHPositionX -= (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dLHPositionZ -= (movedOffset.y() * (R - 150) / (500.0 - 150));
            }
            if (angle >= 45 && angle < 135){
                modelInverse.g_dLHPositionY -= (movedOffset.x() * (R + 150) / (500.0 + 150));
                modelInverse.g_dLHPositionZ -= (movedOffset.y() * (R + 150) / (500.0 + 150));
            }
            if (angle >= 135 && angle < 225){
                modelInverse.g_dLHPositionX += (movedOffset.x() * (R  + 150) / (500.0 + 150));
                modelInverse.g_dLHPositionZ -= (movedOffset.y() * (R  + 150) / (500.0 + 150));
            }
            if (angle >= 225 && angle < 315){
                modelInverse.g_dLHPositionY -= (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dLHPositionZ -= (movedOffset.y() * (R - 150) / (500.0 - 150));
            }
            // 左后腿
            modelInverse.GetLHAngle(g_dLHTheta1,g_dLHTheta2,g_dLHTheta3);

            g_dLHTheta1 = -g_dLHTheta1;
            g_dLHTheta3 = -g_dLHTheta3;
            g_dLHTheta2 = g_dLHTheta2;
        }
        else if(isPicked == 4)            // 右后腿
        {
            if ((angle < 45 && angle >= 0) || angle >= 315){
                modelInverse.g_dRHPositionX -= (movedOffset.x() * (R + 150) / (500.0 + 150));
                modelInverse.g_dRHPositionZ -= (movedOffset.y() * (R + 150) / (500.0 + 150));
            }
            if (angle >= 45 && angle < 135){
                modelInverse.g_dRHPositionY += (movedOffset.x() * (R + 150) / (500.0 + 150));
                modelInverse.g_dRHPositionZ -= (movedOffset.y() * (R + 150) / (500.0 + 150));
            }
            if (angle >= 135 && angle < 225){
                modelInverse.g_dRHPositionX += (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dRHPositionZ -= (movedOffset.y() * (R - 150) / (500.0 - 150));
            }
            if (angle >= 225 && angle < 315){
                modelInverse.g_dRHPositionY -= (movedOffset.x() * (R - 150) / (500.0 - 150));
                modelInverse.g_dRHPositionZ += (movedOffset.y() * (R - 150) / (500.0 - 150));
            }

            modelInverse.GetRHAngle(g_dRHTheta1,g_dRHTheta2,g_dRHTheta3);
            g_dRHTheta1 = g_dRHTheta1;
            g_dRHTheta3 = g_dRHTheta3;
            g_dRHTheta2 = -g_dRHTheta2;
        }
    }
    update();
}

void OpenglView::wheelEvent(QWheelEvent *event)
{
    switch (isPicked) {
    case 1:
        if( event->delta() > 0 ) g_dLFTheta3+=1;
        else g_dLFTheta3-=1;
        break;
    case 2:
        if( event->delta() > 0 ) g_dRFTheta3+=1;
        else g_dRFTheta3-=1;
        break;
    case 3:
        if( event->delta() > 0 ) g_dLHTheta3+=1;
        else g_dLHTheta3-=1;
        break;
    case 4:
        if( event->delta() > 0 ) g_dRHTheta3+=1;
        else g_dRHTheta3-=1;
        break;
    case 5:
        if( event->delta() > 0 ) g_dLFTheta2+=1;
        else g_dLFTheta2-=1;
        break;
    case 6:
        if( event->delta() > 0 ) g_dRFTheta2+=1;
        else g_dRFTheta2-=1;
        break;
    case 7:
        if( event->delta() > 0 ) g_dLHTheta2+=1;
        else g_dLHTheta2-=1;
        break;
    case 8:
        if( event->delta() > 0 ) g_dRHTheta2+=1;
        else g_dRHTheta2-=1;
        break;
    case 9:
        if( event->delta() > 0 ) g_dLFTheta1+=1;
        else g_dLFTheta1-=1;
        break;
    case 10:
        if( event->delta() > 0 ) g_dRFTheta1+=1;
        else g_dRFTheta1-=1;
        break;
    case 11:
        if( event->delta() > 0 ) g_dLHTheta1+=1;
        else g_dLHTheta1-=1;
        break;
    case 12:
        if( event->delta() > 0 ) g_dRHTheta1+=1;
        else g_dRHTheta1-=1;
        break;
    case 13:
        if( event->delta() > 0 ) g_HeadTheta +=1;
        else g_HeadTheta-=1;
        break;
    case 14:
        if( event->delta() > 0 ) g_NeckTheta +=1;
        else g_NeckTheta-=1;
        break;
    case 15:

        break;
    default:

        if(event->delta() > 0){ // 距离拉近
            float k = 1 - 1/ sqrt(atX*atX + atZ*atZ + atY*atY); // 求得缩放系数
            atX = k * atX;
            atY = k * atY;
            atZ = k * atZ;
        }else{ // 距离拉远
            float k = 1 + 1/ sqrt(atX*atX + atZ*atZ + atY*atY); // 求得缩放系数
            atX = k * atX;
            atY = k * atY;
            atZ = k * atZ;
        }
        break;
    }
    update();
}
