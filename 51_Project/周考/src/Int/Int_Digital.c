#include "Int/Int_Digital.h"


void Int_Digital_StaticDisplay(u8 location, u8 ObjNumber) {
    Int_Digital_Single(location, ObjNumber);
}

void Int_Digital_Single(u8 bit_Sel, u8 Segment_Sel) {
    bit_Sel <<= 3;
    P1 |= 0xC7; //  ob 1100 0111
    P1 &= bit_Sel;

    P0 = Segment_Sel;
}