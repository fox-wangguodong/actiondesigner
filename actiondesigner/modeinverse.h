#ifndef MODEINVERSE_H
#define MODEINVERSE_H

class ModeInverse
{
public:
    ModeInverse();

    /**
     * @brief ResetPosition 重置模型坐标
     */
    void ResetPosition();

    /**
     * @brief GetNeckAngle 获取脖子角度
     * @param g_NeckTheta
     */
    void GetNeckAngle(double &g_NeckTheta);

    /**
     * @brief GetHeadAngle 获取头部旋转角度
     * @param g_HeadTheta
     */
    void GetHeadAngle(double &g_HeadTheta);

    /*=========================================================================
    *函数名称：void GetLFAngle(double &g_dLFTheta1, double &g_dLFTheta2, double &g_dLFTheta3)
    *功能说明：通过左前腿的足端坐标(x,y,z),反解左前腿三个舵机的角度值
    *出口参数：g_dLFTheta1, g_dLFTheta2, g_dLFTheta3
    *返回值：无
    ===========================================================================*/
    void GetLFAngle(double &g_dLFTheta1, double &g_dLFTheta2, double &g_dLFTheta3);


    /*=========================================================================
    *函数名称：void GetRFAngle(double &g_dRFTheta1, double &g_dRFTheta2, double &g_dRFTheta3)
    *功能说明：通过右前腿的足端坐标(x,y,z),反解右前腿三个舵机的角度值
    *出口参数：g_dRFTheta1, g_dRFTheta2, g_dRFTheta3
    *返回值：无
    ===========================================================================*/
    void GetRFAngle(double &g_dRFTheta1, double &g_dRFTheta2, double &g_dRFTheta3);


    /*=========================================================================
    *函数名称：GetLHAngle(double &g_dLHTheta1, double &g_dLHTheta2,double &g_dLHTheta3)
    *功能说明：通过左后腿的足端坐标(x,y,z),反解左后腿三个舵机的角度值
    *出口参数：g_dLHTheta1, g_dLHTheta2, g_dLHTheta3
    *返回值：无
    ===========================================================================*/
    void GetLHAngle(double &g_dLHTheta1, double &g_dLHTheta2,double &g_dLHTheta3);


    /*=========================================================================
    *函数名称：GetRHAngle(double &g_dRHTheta1, double &g_dRHTheta2, double &g_dRHTheta3)
    *功能说明：通过右后腿的足端坐标(x,y,z),反解右后腿三个舵机的角度值
    *出口参数：g_dRHTheta1, g_dRHTheta2, g_dRHTheta3
    *返回值：无
    ===========================================================================*/
    void GetRHAngle(double &g_dRHTheta1, double &g_dRHTheta2, double &g_dRHTheta3);


    //头部坐标
    double g_dHeadPositionX;
    //脖子坐标
    double g_dNeckPositionX,g_dNeckPositionY;
    //左前腿足端三维坐标 ，相对于坐标系b
    double g_dLFPositionX, g_dLFPositionY, g_dLFPositionZ;
    double g_dRFPositionX, g_dRFPositionY, g_dRFPositionZ;
    double g_dLHPositionX, g_dLHPositionY, g_dLHPositionZ;
    double g_dRHPositionX, g_dRHPositionY, g_dRHPositionZ;
};

#endif // MODEINVERSE_H
