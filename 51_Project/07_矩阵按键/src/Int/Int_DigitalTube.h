#ifndef __Int_DigitalTube_H__
#define __Int_DigitalTube_H__
#include "Com_Util.h"

static DigitalTube_codes[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
static buffer[8];

void Int_DigitalTube_Single(u8, u8);

void Int_DigitalTube_SetBuffer(u32);
void Int_DigitalTube_Refresh(void);


#endif /* __Int_DigitalTube_H__ */
