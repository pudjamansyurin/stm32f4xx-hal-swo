/*
 * swo.c
 *
 *  Created on: Feb 26, 2022
 *      Author: pujak
 ******************************************************************************
 * @attention
 *
 * This module is not re-entrant, so if you use RTOS, please implement _Lock()
 * and _Unlock() mechanism using Recursive Mutex.
 *
 ******************************************************************************
 */
#include "swo.h"
#include <stdio.h>

/* Private variables */
#ifndef SWO_UNBUFFERED
static char SWO_BUFFER[SWO_BUFFER_SZ];
#endif

/* Private function declarations */
__STATIC_FORCEINLINE void _Lock(void);
__STATIC_FORCEINLINE void _UnLock(void);

/* Public function definitions */
HAL_StatusTypeDef SWO_Init(void)
{
  int rc;

#ifdef SWO_UNBUFFERED
  /* Disable buffering */
  rc = setvbuf(stdout, NULL, _IONBF, 0);
#else
  /* Enable line buffering */
  rc = setvbuf(stdout, SWO_BUFFER, _IOLBF, SWO_BUFFER_SZ);
#endif

  return (rc == 0 ? HAL_OK : HAL_ERROR);
}

void SWO_PrintMatrixFloat(const char *name, const float *data, uint16_t row, uint16_t col)
{
  printf("============================================================================"CRLF);
  printf(" %s[%d][%d] :"CRLF, name, row, col);
  for (uint16_t ro = 0; ro < row; ro++) {
    for (uint16_t co = 0; co < col; co++) {
      printf("%f, ", *(data + (row * col + col)));
    }
    printf(CRLF);
  }
  printf("============================================================================"CRLF);
}

/* Private function definitions */
__STATIC_FORCEINLINE void _Lock(void)
{
  /* Implement me if using RTOS */
}

__STATIC_FORCEINLINE void _UnLock(void)
{
  /* Implement me if using RTOS */
}

/* Replace weak syscall routines */
int __io_putchar(int ch)
{
  _Lock();
  ITM_SendChar(ch);
  _UnLock();

  return (ch);
}

int _write(int file, char *data, int len)
{
  int DataIdx;

  _Lock();
  for (DataIdx = 0; DataIdx < len; DataIdx++)
    __io_putchar(*data++);
  _UnLock();

  return (len);
}

