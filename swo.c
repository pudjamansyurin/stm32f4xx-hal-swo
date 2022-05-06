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
 *
 ******************************************************************************
 */

#include "swo.h"

/* Private function definitions */
static void stdout_writer(char *str, int len)
{
  for (int i = 0; i < len; i++)
    ITM_SendChar(str[i]);
}

/* Public function definitions */
void SWO_Init(void)
{
  stdout_init(stdout_writer);
}

