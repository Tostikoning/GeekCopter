/*
	C file for I2C driver
	 - Depends: STM Peripheral Library, I2C.h

	File: i2c.c
	 - Version 0.1 (in progress 10%)

	 Written by: Maarten Bakker
	 Date: 7/12/2013

	 Includes code and/or ideas from:
	 - BaseFlightPlus

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


///////////////////////////////////////////////////////////////////////////

#include "includes.h"

I2C_TypeDef *I2Cx;

void i2cInit(void)
{
    /* I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);

    /* GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(I2C_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_PinRemapConfig(GPIO_Remap_I2C1,ENABLE);

    /* Configure I2C_EE pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin =  I2C_SCL | I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

    I2C_InitTypeDef  I2C_InitStructure;

    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;

    /* I2C Peripheral Enable */
    I2C_Cmd(I2C_BUS, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(I2C_BUS, &I2C_InitStructure);

    return;
} // end i2cInit

void i2cWrite(uint8_t device, uint8_t address, uint8_t *data, uint8_t length)
{
	i2cSendAddress(device, WRITE, address);

	int i;
	for(i = 0; i<length; i++)
	{
		/* Send data through I2C bus */
		I2C_BUS->DR = *data;
		data++;

		/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}

    /* Send STOP condition */
    I2C_GenerateSTOP(I2C_BUS, ENABLE);
}

void i2cRead(uint8_t device, uint8_t address, uint8_t *data, uint8_t length)
{
	i2cSendAddress(device, READ, address);

	int i;
	for(i = 0; i<length; i++)
	{
		/* Test on EV7 and clear it */
		while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_BYTE_RECEIVED));

		*data = I2C_ReceiveData(I2C_BUS);
		data++;

		 /* Disable Acknowledgement */
        if(!(i < (length - 1)))
            I2C_AcknowledgeConfig(I2C_BUS, DISABLE);

	}

    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C_BUS, ENABLE);
}

void i2cSendAddress(uint8_t device, uint8_t rw, uint8_t address)
{
	/* Send START condition */
	I2C_GenerateSTART(I2C_BUS, ENABLE);

	/* Test on EV5 and clear it */
	while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_MODE_SELECT));

	/* Send 7bit Address */
	I2C1->DR = (device << 1) + WRITE; // 0 for write

    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/* First send register address */
	I2C_BUS->DR = address;

	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	if(rw == READ)
	{
		/* If user wants to read, generate repeated start */
		I2C_GenerateSTART(I2C1, ENABLE);

		/* Test on EV5 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

		/* Send 7bit Address */
		I2C1->DR = (device << 1) + READ; // 1 for read

		/* Test on EV6 and clear it */
		while(!I2C_CheckEvent(I2C_BUS, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
} // end i2cSendAddress






