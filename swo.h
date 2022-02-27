/*
 * swo.h
 *
 *  Created on: Feb 26, 2022
 *      Author: pujak
 */

#ifndef STM32F4XX_HAL_SWO_SWO_H_
#define STM32F4XX_HAL_SWO_SWO_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>

/* Public function declarations */
HAL_StatusTypeDef SWO_Init(UART_HandleTypeDef *huart);

#endif /* STM32F4XX_HAL_SWO_SWO_H_ */
