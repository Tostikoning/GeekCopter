#include "includes.h"

int main(void)
{

    /* Setup the microcontroller system. Initialize the Embedded Flash Interface,
       initialize the PLL and update the SystemFrequency variable. */
    SystemInit();

	i2cInit();

	uint8_t data[6] = {0,0,0,0,0,0};

	while(1)
	{
		i2cRead(0x53, 0x32, &data, 6);
	}

	while(1);
}
