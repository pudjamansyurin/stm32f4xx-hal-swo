# STM32F4xx HAL SWO Module


## How to use the module
#### **`main.c`**

```c
#include "stm32f4xx-hal-swo/swo.h"

int main(void)
{
  /* Initialize SWO-ITM */
  SWO_Init();

  /* Super loop */
  while(1) {
    /* Use stdio from c library */
    printf("Hello World, alman.\r\n");
  }
}
```

## IDE & Debugger Configuration
1. Make sure to connect SWO Pin (PB3) to your ST-Link downloader.

2. (STM32CubeMX) Select "Trace Asynchronous Sw" in Debug Mode.
![Trace Asynchronous Sw](img/trace-async.jpg)

3. (STM32CubeIDE) Enable Serial Wire Viewer (SWV) in debugger configuration, and make sure the Core Clock is same with SYSCLK.
![Debug Configuration](img/debug-config.jpg)

4. (STM32CubeIDE) Enable ITM port 0 in SWV settings.
![SWV Settings](img/swv-settings.jpg)

5. (STM32CubeIDE) Start trace by pressiong R red button.
![SWV ITM Console](img/swv-itm-console.jpg)

