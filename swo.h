/*
 * swo.h
 *
 *  Created on: Feb 26, 2022
 *      Author: pujak
 */

#ifndef STM32F4XX_HAL_SWO_SWO_H_
#define STM32F4XX_HAL_SWO_SWO_H_

#include "stm32f4xx_hal.h"

#define SWO_UART
#define SWO_UNBUFFERED

/* Public macros */
#ifndef SWO_UNBUFFERED
#define SWO_BUFFER_SZ       (512)
#endif

/* Public function declarations */
HAL_StatusTypeDef SWO_Init(void);
#ifdef SWO_UART
HAL_StatusTypeDef SWO_SetUART(UART_HandleTypeDef *huart);
#endif
void SWO_PrintMatrixFloat(const char *name, const float *data, uint16_t row, uint16_t col);

#endif /* STM32F4XX_HAL_SWO_SWO_H_ */
