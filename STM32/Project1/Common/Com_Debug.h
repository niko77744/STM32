#ifndef __COM_DEBUG_H__
#define __COM_DEBUG_H__
#include <stdio.h>
#include <string.h>
#include "Driver_Usart.h"


/* __FILE__  __LINE__  __DATA__ __TIME__ */

#define DEBUG
#ifdef DEBUG
    #define debug_Init() Debug_Init()
    #define FILENAME (strrchr(__FILE__,'\\') ? strrchr(__FILE__,'\\') + 1 : __FILE__)
    #define debug_print(format,...) printf("[%s  Line:%d  %s]--"format"\r\n",FILENAME,__LINE__,__FUNCTION__,##__VA_ARGS__)
    #else
    #define debug_Init() 
    #define debug_print() 
#endif

void Debug_Init(void);

#endif /* __COM_DEBUG_H__ */

