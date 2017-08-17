
#define __HANDLER_GLOBALS

#include "main.h"
#include "OSinclude.h"
#include "Handler.h"
#include "task_SysinitConfig.h"



/**
  * @brief  Ö÷º¯Êý
  * @param  void
  * @retval void
  */
int main(void)
{
    xTaskCreate(task_SysInitConfig,
                "Init",
                350,
                NULL, 
                3,
                NULL);

    vTaskStartScheduler();

    while(1);
}

