#include "modeinverse.h"
#include <math.h>


#define BODY_LENGTH             70      //前半身长度
#define BODY_BACK_LENGTH    80     //后半身长度
#define BODY_WIDTH               84      //身宽的一半	（左右两个舵机的中心）
#define CROTCH_LENGTH         0		  //胯关节长度（胯关节舵机  和  大腿关节舵机  的垂直高度差）
#define THIGH_LENGTH            77     //大腿长度（大腿关节舵机  和  小腿关节舵机  的垂直高度差）
#define CRUS_LENGTH              77     //小腿长度（小腿关节舵机 到 足尖 的垂直高度差）

#define PI 3.141592653


ModeInverse::ModeInverse()
{
    /*设置左前腿的初始位置 */
    g_dLFPositionX = BODY_LENGTH;
    g_dLFPositionY = BODY_WIDTH;
    g_dLFPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
    /* 设置右前腿的初始位置 */
    g_dRFPositionX = BODY_LENGTH;
    g_dRFPositionY = -BODY_WIDTH;
    g_dRFPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);

    /* 设置左后腿的初始位置 */
    g_dLHPositionX = -BODY_LENGTH - 10;
    g_dLHPositionY = BODY_WIDTH;
    g_dLHPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
    /* 设置右后腿的初始位置 */
    g_dRHPositionX = -BODY_LENGTH - 10;
    g_dRHPositionY = -BODY_WIDTH;
    g_dRHPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
}

void ModeInverse::ResetPosition()
{
    /*设置左前腿的初始位置 */
    g_dLFPositionX = BODY_LENGTH;
    g_dLFPositionY = BODY_WIDTH;
    g_dLFPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
    /* 设置右前腿的初始位置 */
    g_dRFPositionX = BODY_LENGTH;
    g_dRFPositionY = -BODY_WIDTH;
    g_dRFPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);

    /* 设置左后腿的初始位置 */
    g_dLHPositionX = -BODY_LENGTH - 10;
    g_dLHPositionY = BODY_WIDTH;
    g_dLHPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
    /* 设置右后腿的初始位置 */
    g_dRHPositionX = -BODY_LENGTH - 10;
    g_dRHPositionY = -BODY_WIDTH;
    g_dRHPositionZ = -(THIGH_LENGTH + CRUS_LENGTH);
}



void ModeInverse::GetNeckAngle(double &g_NeckTheta)
{
    //脖子坐标限位
    g_dNeckPositionX = g_dNeckPositionX > 94 ? 94 : g_dNeckPositionX;
    g_dNeckPositionX = g_dNeckPositionX < 0 ? 0 : g_dNeckPositionX;
    g_dNeckPositionY = g_dNeckPositionY >94 ? 94 : g_dNeckPositionY;
    g_dNeckPositionY = g_dNeckPositionY < 0 ? 0 : g_dNeckPositionY;

    //计算弧度制
    float dTheta = atan2(g_dNeckPositionY, g_dNeckPositionX);

    //将弧度转为角度
    g_NeckTheta = dTheta / PI * 180.0;

    //角度限位
    g_NeckTheta = g_NeckTheta >= 60 ? 60 : g_NeckTheta;
}

void ModeInverse::GetHeadAngle(double &g_HeadTheta)
{
    //坐标限位
    g_dHeadPositionX = g_dHeadPositionX > 20 ? 20:g_dHeadPositionX;
    g_dHeadPositionX = g_dHeadPositionX < -20 ? -20:g_dHeadPositionX;

    //计算角度
    g_dHeadPositionX = 0;

    //角度限位
    g_HeadTheta = g_HeadTheta > 90 ? 90 : g_HeadTheta;
    g_HeadTheta = g_HeadTheta < -90 ? -90 : g_HeadTheta;
}



/*=========================================================================
*函数名称：void GetLFAngle(double &g_dLFTheta1, double &g_dLFTheta2, double &g_dLFTheta3)
*功能说明：通过左前腿的足端坐标(x,y,z),反解左前腿三个舵机的角度值
*出口参数：g_dLFTheta1, g_dLFTheta2, g_dLFTheta3
*返回值：无
===========================================================================*/
void ModeInverse::GetLFAngle(double &g_dLFTheta1, double &g_dLFTheta2, double &g_dLFTheta3)
{
    //XYZ三轴坐标限位
    if (g_dLFPositionZ >= CRUS_LENGTH)
        g_dLFPositionZ = CRUS_LENGTH;
    if (g_dLFPositionZ <= -(CRUS_LENGTH + THIGH_LENGTH))
        g_dLFPositionZ = -(CRUS_LENGTH + THIGH_LENGTH);
    if (g_dLFPositionX >= CRUS_LENGTH + BODY_LENGTH + THIGH_LENGTH)
        g_dLFPositionX = CRUS_LENGTH + BODY_LENGTH + THIGH_LENGTH;
    if (g_dLFPositionX <= BODY_LENGTH - CRUS_LENGTH - THIGH_LENGTH)
        g_dLFPositionX = BODY_LENGTH - CRUS_LENGTH - THIGH_LENGTH;
    if (g_dLFPositionY >= BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.866)
        g_dLFPositionY = BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.866;
    if (g_dLFPositionY <= BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.1736)
        g_dLFPositionY = BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.1736;

    double x, y, z;
    x = g_dLFPositionX;
    y = g_dLFPositionY;
    z = g_dLFPositionZ;

    if (pow(y - BODY_WIDTH,2) + pow(z,2) - pow(CROTCH_LENGTH,2) >= 0 && z != 0)
    {
        g_dLFTheta2 = atan((y - BODY_WIDTH) / (-z)) - atan2(CROTCH_LENGTH, sqrt(pow((y - BODY_WIDTH), 2) + pow(z, 2) - pow(CROTCH_LENGTH,2)));
    }
    else
    {
        g_dLFTheta2 = 0;
    }


    double x1, y1, z1;
    x1 = y*sin(g_dLFTheta2) - z*cos(g_dLFTheta2) - BODY_WIDTH*sin(g_dLFTheta2);
    y1 = y*cos(g_dLFTheta2) + z*sin(g_dLFTheta2) - BODY_WIDTH*cos(g_dLFTheta2);
    z1 = x - BODY_LENGTH;
    if (pow(x1, 2) + pow(y1, 2) + pow(z1, 2) > pow(THIGH_LENGTH + CRUS_LENGTH, 2) + pow(CROTCH_LENGTH, 2))
    {
        g_dLFTheta1 = -atan2(z1, x1);
        if (x1 < 0){
            g_dLFTheta2 = atan2(y1, -x1);
        }else{
            g_dLFTheta2 = atan2(y1, x1);
        }
        g_dLFTheta3 = 0;
    }
    else
    {
        g_dLFTheta3 = acos((pow(x1, 2) + pow(z1, 2) - pow(THIGH_LENGTH, 2) - pow(CRUS_LENGTH, 2)) / (2 * THIGH_LENGTH*CRUS_LENGTH));


        double sinTheta = sin(g_dLFTheta3);
        double cosTheta = cos(g_dLFTheta3);

        double atan2_1 = atan(CRUS_LENGTH*sinTheta / (THIGH_LENGTH + CRUS_LENGTH*cosTheta));
        double atan2_2 = 0;
        if (x1 < 0){
            atan2_2 = atan2(BODY_LENGTH - x, -sqrt(pow(CRUS_LENGTH*sinTheta, 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cosTheta, 2) - pow(BODY_LENGTH - x, 2)));
        }else{
            atan2_2 = atan2(BODY_LENGTH - x, sqrt(pow(CRUS_LENGTH*sinTheta, 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cosTheta, 2) - pow(BODY_LENGTH - x, 2)));
        }
        g_dLFTheta1 = atan2_1 + atan2_2;
    }
    g_dLFTheta3 = -g_dLFTheta3;


    //将弧度转换为角度
    g_dLFTheta1 = g_dLFTheta1 / PI*180.0;
    g_dLFTheta3 = g_dLFTheta3 / PI*180.0;
    g_dLFTheta2 = g_dLFTheta2 / PI*180.0;

    /*角度限位*/
    if (g_dLFTheta1 >= 85) g_dLFTheta1 = 85;
    if (g_dLFTheta1 <= -85) g_dLFTheta1 = -85;
    if (g_dLFTheta2 >= 60) g_dLFTheta2 = 60;
    if (g_dLFTheta2 <= -10) g_dLFTheta2 = -10;
    if (g_dLFTheta3 >= 10) g_dLFTheta3 = 10;
    if (g_dLFTheta3 <= -100) g_dLFTheta3 = -100;
}


/*=========================================================================
*函数名称：void GetRFAngle(double &g_dRFTheta1, double &g_dRFTheta2, double &g_dRFTheta3)
*功能说明：通过右前腿的足端坐标(x,y,z),反解右前腿三个舵机的角度值
*出口参数：g_dRFTheta1, g_dRFTheta2, g_dRFTheta3
*返回值：无
===========================================================================*/
void ModeInverse::GetRFAngle(double &g_dRFTheta1, double &g_dRFTheta2, double &g_dRFTheta3)
{
    //XYZ三轴坐标限位
    if (g_dRFPositionZ >= CRUS_LENGTH)
        g_dRFPositionZ = CRUS_LENGTH;
    if (g_dRFPositionZ <= -(CRUS_LENGTH + THIGH_LENGTH))
        g_dRFPositionZ = -(CRUS_LENGTH + THIGH_LENGTH);
    if (g_dRFPositionX >= CRUS_LENGTH + BODY_LENGTH + THIGH_LENGTH)
        g_dRFPositionX = CRUS_LENGTH + BODY_LENGTH + THIGH_LENGTH;
    if (g_dRFPositionX <= BODY_LENGTH - CRUS_LENGTH - THIGH_LENGTH)
        g_dRFPositionX = BODY_LENGTH - CRUS_LENGTH - THIGH_LENGTH;
    if (g_dRFPositionY <= -BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.866)
        g_dRFPositionY = -BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.866;
    if (g_dRFPositionY >= -BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.1736)
        g_dRFPositionY = -BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.1736;



    double x, y, z;
    x = g_dRFPositionX;
    y = g_dRFPositionY;
    z = g_dRFPositionZ;

    if (pow(y + BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH,2) >= 0)
    {
        g_dRFTheta2 = atan((y + BODY_WIDTH) / (-z)) - atan2(-CROTCH_LENGTH, sqrt(pow(y + BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH,2)));
    }
    else
    {
        g_dRFTheta2 = 0;
    }

    double x1, y1, z1;
    x1 = y*sin(g_dRFTheta2) - z*cos(g_dRFTheta2) + BODY_WIDTH*sin(g_dRFTheta2);
    y1 = y*cos(g_dRFTheta2) + z*sin(g_dRFTheta2) + BODY_WIDTH*cos(g_dRFTheta2);
    z1 = x - BODY_LENGTH;
    if (pow(x1, 2) + pow(y1, 2) + pow(z1, 2) > pow(THIGH_LENGTH + CRUS_LENGTH, 2) + pow(CROTCH_LENGTH, 2))
    {

        if (x1 < 0){
            g_dRFTheta2 = atan2(y1, -x1);
        }else{
            g_dRFTheta2 = atan2(y1, x1);
        }
        g_dRFTheta1 = -atan2(z1, x1);
        g_dRFTheta3 = 0;
    }
    else
    {
        g_dRFTheta3 = acos((pow(x1, 2) + pow(z1, 2) - pow(THIGH_LENGTH, 2) - pow(CRUS_LENGTH, 2)) / (2 * THIGH_LENGTH*CRUS_LENGTH));
        if (x1 < 0){
            g_dRFTheta1 = atan(CRUS_LENGTH*sin(g_dRFTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dRFTheta3))) + atan2(BODY_LENGTH - x, -sqrt(pow(CRUS_LENGTH*sin(g_dRFTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dRFTheta3), 2)) - pow(BODY_LENGTH - x, 2));
        }else{
            g_dRFTheta1 = atan(CRUS_LENGTH*sin(g_dRFTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dRFTheta3))) + atan2(BODY_LENGTH - x, sqrt(pow(CRUS_LENGTH*sin(g_dRFTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dRFTheta3), 2)) - pow(BODY_LENGTH - x, 2));
        }
    }

    g_dRFTheta3 = -g_dRFTheta3;

    // 将弧度转换为角度
    g_dRFTheta1 = g_dRFTheta1 / PI*180.0;
    g_dRFTheta3 = g_dRFTheta3 / PI*180.0;
    g_dRFTheta2 = g_dRFTheta2 / PI*180.0;

    // 角度限位
    if (g_dRFTheta1 >= 85) g_dRFTheta1 = 85;
    if (g_dRFTheta1 <= -85) g_dRFTheta1 = -85;
    if (g_dRFTheta2 >= 10) g_dRFTheta2 = 10;
    if (g_dRFTheta2 <= -60) g_dRFTheta2 = -60;
    if (g_dRFTheta3 >= 10) g_dRFTheta3 = 10;
    if (g_dRFTheta3 <= -100) g_dRFTheta3 = -100;
}

/*=========================================================================
*函数名称：GetLHAngle(double &g_dLHTheta1, double &g_dLHTheta2,double &g_dLHTheta3)
*功能说明：通过左后腿的足端坐标(x,y,z),反解左后腿三个舵机的角度值
*出口参数：g_dLHTheta1, g_dLHTheta2, g_dLHTheta3
*返回值：无
===========================================================================*/
void ModeInverse::GetLHAngle(double &g_dLHTheta1, double &g_dLHTheta2,double &g_dLHTheta3)
{
    //XYZ三轴坐标限位
    if (g_dLHPositionZ >= CRUS_LENGTH)
        g_dLHPositionZ = CRUS_LENGTH;
    if (g_dLHPositionZ <= -(CRUS_LENGTH + THIGH_LENGTH))
        g_dLHPositionZ = -(CRUS_LENGTH + THIGH_LENGTH);
    if (g_dLHPositionX >= CRUS_LENGTH - BODY_LENGTH - 10 + THIGH_LENGTH)
        g_dLHPositionX = CRUS_LENGTH - BODY_LENGTH - 10 + THIGH_LENGTH;
    if (g_dLHPositionX <= -BODY_LENGTH - 10 - CRUS_LENGTH - THIGH_LENGTH)
        g_dLHPositionX = -BODY_LENGTH - 10 - CRUS_LENGTH - THIGH_LENGTH;
    if (g_dLHPositionY >= BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.866)
        g_dLHPositionY = BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.866;
    if (g_dLHPositionY <= BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.1736)
        g_dLHPositionY = BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.1736;




    double x, y, z;
    x = g_dLHPositionX;
    y = g_dLHPositionY;
    z = g_dLHPositionZ;

    if (pow(y - BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH,2) >= 0)
    {
        g_dLHTheta2 = atan((y - BODY_WIDTH) / (-z)) - atan2(CROTCH_LENGTH, sqrt(pow(y - BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH, 2)));
    }
    else
    {
        g_dLHTheta2 = 0;
    }

    double x1, y1, z1;
    x1 = y*sin(g_dLHTheta2) - z*cos(g_dLHTheta2) - BODY_WIDTH*sin(g_dLHTheta2);
    y1 = y*cos(g_dLHTheta2) + z*sin(g_dLHTheta2) - BODY_WIDTH*cos(g_dLHTheta2);
    z1 = x + BODY_BACK_LENGTH;
    if (pow(x1, 2) + pow(y1, 2) + pow(z1, 2) > pow(THIGH_LENGTH + CRUS_LENGTH, 2) + pow(CROTCH_LENGTH, 2))
    {
        if (x1 < 0){
            g_dLHTheta2 = atan2(y1, -x1);
        }else{
            g_dLHTheta2 = atan2(y1, x1);
        }
        g_dLHTheta1 = -atan2(z1, x1);
        g_dLHTheta3 = 0;
    }
    else
    {
        g_dLHTheta3 = acos((pow(x1, 2) + pow(z1, 2) - pow(THIGH_LENGTH, 2) - pow(CRUS_LENGTH, 2)) / (2 * THIGH_LENGTH*CRUS_LENGTH));

        if (x1 < 0){
            g_dLHTheta1 = atan(CRUS_LENGTH*sin(g_dLHTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dLHTheta3))) + atan2(-(BODY_BACK_LENGTH + x), -sqrt(pow(CRUS_LENGTH*sin(g_dLHTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dLHTheta3), 2) - pow(BODY_BACK_LENGTH + x, 2)));
        }else{
            g_dLHTheta1 = atan(CRUS_LENGTH*sin(g_dLHTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dLHTheta3))) + atan2(-(BODY_BACK_LENGTH + x), sqrt(pow(CRUS_LENGTH*sin(g_dLHTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dLHTheta3), 2) - pow(BODY_BACK_LENGTH + x, 2)));
        }
    }
    g_dLHTheta3 = -g_dLHTheta3;


    //将弧度转换为角度
    g_dLHTheta1 = g_dLHTheta1 / PI*180.0;
    g_dLHTheta3 = g_dLHTheta3 / PI*180.0;
    g_dLHTheta2 = g_dLHTheta2 / PI*180.0;

    //角度限位
    if (g_dLHTheta1 >= 85) g_dLHTheta1 = 85;
    if (g_dLHTheta1 <= -85) g_dLHTheta1 = -85;
    if (g_dLHTheta2 >= 60) g_dLHTheta2 = 60;
    if (g_dLHTheta2 <= -10) g_dLHTheta2 = -10;
    if (g_dLHTheta3 >= 10) g_dLHTheta3 = 10;
    if (g_dLHTheta3 <= -100) g_dLHTheta3 = -100;
}

/*=========================================================================
*函数名称：GetRHAngle(double &g_dRHTheta1, double &g_dRHTheta2, double &g_dRHTheta3)
*功能说明：通过右后腿的足端坐标(x,y,z),反解右后腿三个舵机的角度值
*出口参数：g_dRHTheta1, g_dRHTheta2, g_dRHTheta3
*返回值：无
===========================================================================*/
void ModeInverse::GetRHAngle(double &g_dRHTheta1, double &g_dRHTheta2, double &g_dRHTheta3)
{
    //XYZ三轴坐标限位
    if (g_dRHPositionZ >= CRUS_LENGTH)
        g_dRHPositionZ = CRUS_LENGTH;
    if (g_dRHPositionZ <= -(CRUS_LENGTH + THIGH_LENGTH))
        g_dRHPositionZ = -(CRUS_LENGTH + THIGH_LENGTH);
    if (g_dRHPositionX >= CRUS_LENGTH - BODY_LENGTH - 10 + THIGH_LENGTH)
        g_dRHPositionX = CRUS_LENGTH - BODY_LENGTH - 10 + THIGH_LENGTH;
    if (g_dRHPositionX <= -BODY_LENGTH - 10 - CRUS_LENGTH - THIGH_LENGTH)
        g_dRHPositionX = -BODY_LENGTH - 10 - CRUS_LENGTH - THIGH_LENGTH;
    if (g_dRHPositionY <= -BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.866)
        g_dRHPositionY = -BODY_WIDTH - (CRUS_LENGTH + THIGH_LENGTH)*0.866;
    if (g_dRHPositionY >= -BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.1736)
        g_dRHPositionY = -BODY_WIDTH + (CRUS_LENGTH + THIGH_LENGTH)*0.1736;


    double x, y, z;
    x = g_dRHPositionX;
    y = g_dRHPositionY;
    z = g_dRHPositionZ;

    if (pow(y + BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH,2) >= 0)
    {
        g_dRHTheta2 = atan((y + BODY_WIDTH) / (-z)) - atan2(-CROTCH_LENGTH, sqrt(pow(y + BODY_WIDTH, 2) + pow(z, 2) - pow(CROTCH_LENGTH, 2)));
    }
    else
    {
        g_dRHTheta2 = 0;
    }

    double x1, y1, z1;
    x1 = y*sin(g_dRHTheta2) - z*cos(g_dRHTheta2) + BODY_WIDTH*sin(g_dRHTheta2);
    y1 = y*cos(g_dRHTheta2) + z*sin(g_dRHTheta2) + BODY_WIDTH*cos(g_dRHTheta2);
    z1 = x + BODY_BACK_LENGTH;
    if (pow(x1, 2) + pow(y1, 2) + pow(z1, 2) > pow(THIGH_LENGTH + CRUS_LENGTH, 2) + pow(CROTCH_LENGTH, 2))
    {
        if (x1 < 0){
            g_dRHTheta2 = atan2(y1, -x1);
        }else{
            g_dRHTheta2 = atan2(y1, x1);
        }
        g_dRHTheta1 = -atan2(z1, x1);
        g_dRHTheta3 = 0;
    }
    else
    {
        g_dRHTheta3 = acos((pow(x1, 2) + pow(z1, 2) - pow(THIGH_LENGTH, 2) - pow(CRUS_LENGTH, 2)) / (2 * THIGH_LENGTH*CRUS_LENGTH));
        if (x1 < 0){
            g_dRHTheta1 = atan(CRUS_LENGTH*sin(g_dRHTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dRHTheta3))) + atan2(-(BODY_BACK_LENGTH + x), -sqrt(pow(CRUS_LENGTH*sin(g_dRHTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dRHTheta3), 2) - pow(BODY_BACK_LENGTH + x, 2)));
        }else{
            g_dRHTheta1 = atan(CRUS_LENGTH*sin(g_dRHTheta3) / (THIGH_LENGTH + CRUS_LENGTH*cos(g_dRHTheta3))) + atan2(-(BODY_BACK_LENGTH + x), sqrt(pow(CRUS_LENGTH*sin(g_dRHTheta3), 2) + pow(THIGH_LENGTH + CRUS_LENGTH*cos(g_dRHTheta3), 2) - pow(BODY_BACK_LENGTH + x, 2)));
        }
    }
    g_dRHTheta3 = -g_dRHTheta3;

    // 将弧度转换为角度
    g_dRHTheta1 = g_dRHTheta1 / PI*180.0;
    g_dRHTheta3 = g_dRHTheta3 / PI*180.0;
    g_dRHTheta2 = g_dRHTheta2 / PI*180.0;

    // 角度限位
    if (g_dRHTheta1 >= 85) g_dRHTheta1 = 85;
    if (g_dRHTheta1 <= -85) g_dRHTheta1 = -85;
    if (g_dRHTheta2 >= 10) g_dRHTheta2 = 10;
    if (g_dRHTheta2 <= -60) g_dRHTheta2 = -60;
    if (g_dRHTheta3 >= 10) g_dRHTheta3 = 10;
    if (g_dRHTheta3 <= -100) g_dRHTheta3 = -100;
}
