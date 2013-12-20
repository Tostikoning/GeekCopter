/*
	Header file for I2C driver
	 - Supports I2C.c
	 - Depends: STM Peripheral Library

	File: i2c.h
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

#pragma once

/* Defines */
#define I2C_BUS         I2C1
#define I2C_CLK         RCC_APB1Periph_I2C1
#define I2C_GPIO        GPIOB
#define I2C_GPIO_CLK    RCC_APB2Periph_GPIOB
#define I2C_SCL         GPIO_Pin_8
#define I2C_SDA         GPIO_Pin_9
#define I2C_Speed       400000

#define WRITE 			0
#define READ			1

/* Function Prototypes */
void i2cInit(void);


