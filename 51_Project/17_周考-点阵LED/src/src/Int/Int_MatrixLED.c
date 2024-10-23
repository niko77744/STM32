#include "Int_MatrixLED.h"
#include "Dri_Tmer0Interruput.h"





// 定义缓存数组储存像素信息
static u8 s_buffers[8];


/**
 * @brief 点阵屏初始化
 *
 */
void Int_MatrixLED_Init()
{
    u8 i;
    // 关闭LED、数码管、打开点阵屏
    P34 = 0; // LED高电平有效
    P36 = 1; // 数码管低电平有效
    P35 = 0; // 点阵屏低电平有效
    // 关闭所有阴极信号
    P0 = 0;

    // 清空缓存数组的信息
    for (i = 0; i < 8; i++)
    {
        s_buffers[i] = 0;
    }

    Dri_Timer0Interrupt_Init();
    //时钟中断注册刷新函数
    Dri_Timer0Interrupt_RegisiterFunction(Int_MatrixLED_Refersh);
}

/**
 * @brief 将像素信息储存进缓存数组
 *
 * @param pixel 像素信息
 */
void Int_MatrixLED_SetPixel(u8 *pixel)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        s_buffers[i] = pixel[i];
    }
}

/**
 * @brief 数码管刷新函数
 *
 */
void Int_MatrixLED_Refersh()
{
    //定义静态变量，用于时钟中断调用时计数
    static u8 i=0;

    //根据i的值给SER进行赋值，仅当i=0时，SER=0
    if (!i)SER =1; 
    else SER = 0;

    //刷新行数
    P0  = 0xFF;
    SCK = 0;
    SCK = 1;
    RCK = 0;
    RCK = 1;
    P0 = ~s_buffers[i];

    //当刷新到最后1行，返回起始行
    i++;
    if (i==8)i=0;
    

    // u8 i;
    // // 在串行输入端口首先输入1
    // SER = 1;
    // // 存入移位寄存器低位：0000 0001
    // SCK = 0;
    // SCK = 1;
    // // 在串行输入端口首先输入0
    // SER = 0;

    // for (i = 0; i < 8; i++)
    // {
    //     // 消除寄生电容的影响
    //     P0 = 0xFF;

    //     // 输出到存储寄存器并输出
    //     RCK = 0;
    //     RCK = 1;
    //     // 显示每行的像素信息
    //     P0 = ~s_buffers[i];

    //     // 存入移位寄存器低位：0000 0010
    //     SCK = 0;
    //     SCK = 1;
    // }
    // if (i == 8)i =0;
    
}


/**
 * @brief 改变缓存数组中的元素
 * 
 * @param line 为数组中的首位元素赋值
 */
void Int_MatrixLE_ShiftPixel(u8 line)
{
    u8 i;

    for ( i = 7; i > 0; i--)
    {
        //数组中的元素后移，此时第一个元素相当于空出来
        s_buffers[i] = s_buffers[i-1];
    }
    //为首位元素赋值
    s_buffers[0] = line;
}

// /**
//  * @brief 更改缓存数组内的元素
//  * @param pic 二维数组
//  */
// void Int_Matrix_ChangeBuffer(u8 *pic)
// {
//     staic u8 i =0;
//     s_buffers = pic+i;
//     i++;
//     if (i == 4)i=0;

// }