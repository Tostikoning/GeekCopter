/*
	Include file, includes all .h files
	 - Supports Drivers
	 - Depends: STM Peripheral Library

	File: includes.h
	 - Version 0

	 Written by: Maarten Bakker
	 Date: 8/12/2013

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

/* stm lib */
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include <stdbool.h>

/* drivers */
#include "i2c.h"
