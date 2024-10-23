/*
    PID优化：
        比例：常系数KP * 误差E[k]，只会逼近目标值，无法超过目标值
        积分：常系数KI * 所有误差的和SUM(E[k])，让其超过目标值  随着时间的推移，这个小偏差不断被积分，积分项越来越大
        微分：常系数KD * (本次误差-上次误差)(E[k]-E[k-1]) 理解为回偏值，像一个 “预测器”
        PID 计算结果为调整量，需要不断的计算。例如小车目前左偏(右边是正数)，需要修正姿态，那么左轮向前加速(+PID)，右轮反向减速(-PID)，此时PID为正，即可修正本次姿态。如果右偏(左边是负数)，左轮+PID，但是PID是负数，实际是反向，右轮正向加速。

    代码实现:
        三个常数只能调试
        限制PID误差出现极值,例如结果不能大于80(最大正转速度-最大反转速度)，积分同样不能太大，否则修正过头

*/

#include "App_Patrol.h"
#include "Int_Sensor.h"  //光敏电阻模块，计算了误差的加权平均 Int_Sensor_GetError
#include "Int_Motor.h"
#include "Int_OLED.h"

#define KP 1000  //大避免大量小数浮点运算
#define KI 1
#define KD 600

// 记录上一次误差
char last_error;
// 记录本次误差
char now_error;
// 记录误差和
int sum_error;



int App_Patrol_GetPID() {
    int result;
    now_error = Int_Sensor_GetError();
    // 积分部分： 
    sum_error += now_error;
    // 限制积分最大值int
    if (sum_error > 2000)
    {
        sum_error = 2000;
    }
    if (sum_error < -2000)
    {
        sum_error = -2000;
    }

    result = KP * now_error + KI * sum_error + KD * (now_error - last_error);

    // 将本次误差传递给上一次误差
    last_error = now_error;


    // 处理结果
    result /= 50;  // 大避免大量小数浮点运算,再除回来，并且不能大于80(最大正转速度-最大反转速度)
    if (result > 80)
    {
        result = 80;
    }
    if (result < -80)
    {
        result = -80;
    }

    return result;
}


/**
 * @brief 巡线模式的控制函数
 */
void App_Patrol_Control()
{

    char pid = App_Patrol_GetPID();

    Int_Motor_SetLeftSpeed(40 + pid);
    Int_Motor_SetRightSpeed(40 - pid);
}
