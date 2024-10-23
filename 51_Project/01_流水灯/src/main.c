#include <STC89C5xRC.H>
#include <INTRINS.H>

typedef unsigned char u8;
typedef unsigned int u16;

void Delay_1ms(u16);


void main() {

    u8 temp = 0x01;  //0b00000001
    u8 i, j;
    while (1)
    {
        for (i = 0; i < 7; i++)
        {
            P0 = ~temp;
            temp <<= 1;
            Delay_1ms(100);
        }
        for (j = 0; j < 7; j++)
        {
            P0 = ~temp;
            temp >>= 1;
            Delay_1ms(200);
        }
    }
}

// ÑÓÊ±º¯Êý
void Delay_1ms(u16 ms) {

    unsigned char i, j;
    for (;ms > 0;ms--) {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}