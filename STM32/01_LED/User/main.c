
#include <stdint.h>

int main() {

	*(uint32_t *)(0x40021000 + 0x18) =4;
	*(uint32_t *)(0x40010800 + 0x00) =3;
	*(uint32_t *)(0x40010800 + 0x0C) =0xFFFE;
	while(1);
}

