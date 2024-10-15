#include "LoRa.h"

void LoRa_Init(void) {
    /* 模块默认进入接收模式 */
    Ebyte_RF.Init();
}
void LoRa_Start(void) {
    /* 必须被客户周期性调用，否则无法接收到数据  BBYTE 无线模块周期任务 */
    Ebyte_RF.StartPollTask();
}
void LoRa_Send(uint8e_t* buffer, uint8e_t size) {
    /* 将超时时间定义为0  不使用超时检查 */ 
    uint32e_t timeout = 0;
    Ebyte_RF.Send(buffer, size, timeout);
    /* 模块进入发送状态 开始自主发送数据 完成后内部寄存器置位  
    Ebyte_E220x_SetTx(timeout);  使能模块 进行无线发送   timeout 超时时间  @arg 0:不进行超时判断
    */
    
}
