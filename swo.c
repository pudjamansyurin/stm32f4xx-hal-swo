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
#ifndef SWO_UNBUFFERED
static char swo_buffer[SWO_BUFFER_SZ];
#endif
static UART_HandleTypeDef *swo_uart;

/* Public function definitions */
HAL_StatusTypeDef SWO_Init(void *huart)
{
  int rc;

#ifdef SWO_UNBUFFERED
  /* Disable buffering */
  rc = setvbuf(stdout, NULL, _IONBF, 0);
#else
  /* Enable line buffering */
  rc = setvbuf(stdout, swo_buffer, _IOLBF, SWO_BUFFER_SZ);
#endif

  /* Use UART instead of ITM */
  if (huart != NULL)
    swo_uart = (UART_HandleTypeDef*) huart;

  return (rc == 0 ? HAL_OK : HAL_ERROR);
}

void SWO_PrintMatrixFloat(const char *name, const float *data, uint16_t row, uint16_t col)
{
  printf("%s[%d][%d]:\r\n", name, row, col);
  for (uint16_t r = 0; r < row; r++) {
    for (uint16_t c = 0; c < col; c++)
      printf("%.1f, ", *(data + (r * col + c)));
    printf("\r\n");
  }
  printf("\r\n");
}

/* Replace weak syscall routines */
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

