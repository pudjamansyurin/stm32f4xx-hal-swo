/*
 * swo.c
 *
 *  Created on: Feb 26, 2022
 *      Author: pujak
 ******************************************************************************
 * @attention
 *
 * Just call general printf() routine from <stdio.h> to use this module.
 * You have to enable ITM Port 0, and make sure the SWO clock (before prescaler)
 * is same with CPU clock.
 * This module is not re-entrant, if you want to use RTOS, please add your
 * own mutex implementation.
 *
 ******************************************************************************
 */
#include "swo.h"

/* Private variables */
static UART_HandleTypeDef *swo_uart;

/* Public function definitions */
HAL_StatusTypeDef SWO_Init(UART_HandleTypeDef *huart)
{
  int rc;

  /* Disable buffering */
  rc = setvbuf(stdout, NULL, _IONBF, 0);

  /* Use UART instead of ITM */
  if (huart != NULL)
    swo_uart = huart;

  return (rc == 0 ? HAL_OK : HAL_ERROR);
}

/* Replace weak syscalls routines */
int __io_putchar(int ch)
{
  if (swo_uart == NULL)
    ITM_SendChar(ch);
  else
    HAL_UART_Transmit(swo_uart, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
  return (ch);
}

int _write(int file, char *ptr, int len)
{
  if (swo_uart == NULL) {
    for (int DataIdx = 0; DataIdx < len; DataIdx++)
      __io_putchar(*ptr++);
  } else {
    HAL_UART_Transmit(swo_uart, (uint8_t*) ptr, len, HAL_MAX_DELAY);
  }

  return len;
}

