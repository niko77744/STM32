/**
  **********************************************************************************
  * @file      ebyte_callback.h
  * @brief     EBYTE驱动库的收发完成回调函数 由客户实现自己的逻辑代码
  * @details   详情请参见 https://www.ebyte.com/
  * @author    JiangHeng
  * @date      2021-05-13
  * @version   1.0.0
  **********************************************************************************
  * @copyright BSD License
  *            成都亿佰特电子科技有限公司
  *   ______   ____   __     __  _______   ______
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__
  *  |  __|   |  _ <    \   /      | |    |  __|
  *  | |____  | |_) |    | |       | |    | |____
  *  |______| |____/     |_|       |_|    |______|
  *
  **********************************************************************************
  */
#include "ebyte_callback.h"

  /*= !!!配置目标硬件平台头文件 =======================================*/
#include "ebyte_core.h"
#include "usart.h"
#include <string.h>
/*= !!!配置目标硬件变量       =======================================*/

/*==================================================================*/



/* !
 * @brief 发送完成回调接口 由客户实现自己的发送完成逻辑
 *
 * @param state 上层回调提供的状态码 客户请根据示例注释找到对应区域
 *
 * @note E22x 模块可提供的状态码
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200,
 */
void Ebyte_Port_TransmitCallback(uint16e_t state)
{
    /* 发送: 正常完成 */
    printf("发送状态码=0x%x\r\n", state);
    uint32_t timeout = 0;
    /* 发送完成后切换到接收模式  模块默认进入接收模式 */

    Ebyte_RF.EnterReceiveMode(timeout);

    if (state & 0x0001)
    {
        //To-do 实现自己的逻辑
        printf("发送: 正常完成\n");
    }
    /* 发送: 异常超时 */
    else if (state & 0x0200)
    {
        //To-do 实现自己的逻辑
        printf("数据发送异常超时...\r\n");
    }
    /* 发送: 未知错误 */
    else
    {
        /* 发送状态标识不正确，请检查软硬件
           常见问题 1:SPI通信不正确 2:模块供电不足 */
        printf("数据发送出现未知错误, 请检查硬件...\r\n");
        while (1);
    }
}

/* !
 * @brief 接收完成回调接口 由客户实现自己的发送完成逻辑
 *
 * @param state 上层回调提供的状态码 客户请根据示例注释找到对应区域
 *
 * @note E22x 模块可提供的状态码
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200,
 */
void Ebyte_Port_ReceiveCallback(uint16e_t state, uint8e_t* buffer, uint8e_t length)
{
    printf("接收的状态码为%d\n", state);
    /* 接收: 正常 */
    if (state & 0x0002)
    {
        // To-do 实现自己的逻辑
        printf("接收成功length:%d,data:%s\n", length, buffer);
        memset(buffer, 0, strlen((char*)buffer));
    }
    /* 接收: 异常超时 */
    else if (state & 0x0200)
    {
        // To-do 实现自己的逻辑
        printf("接收异常超时\n");
    }
    /* 接收: 未知错误 */
    else
    {
        /* 发送状态标识不正确，请检查软硬件
           常见问题 1:SPI通信不正确 2:模块供电不足 */
        printf("发送状态标识不正确，请检查软硬件\n");
        while (1)
            ;
    }
}
