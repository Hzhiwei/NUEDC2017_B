#include "task_AngleControl.h"
#include "driver_mpu6050.h"
#include "driver_AngleControl.h"
#include "driver_steering.h"
#include "OSinclude.h"


Euler_Type E;

float OmegaLimit = 0.05;

float AngleXOffset = 0.7;
float AngleYOffset = -8.3;

float AngleReal[2];

float AngleTarget[2] = {0, 0};

float tempTarget[2], absTarget[2], lastAbsTarget[2];

/**
  * @brief  角度控制任务
  * @param  unused
  * @retval void 
  */
void task_AngleControl(void *param)
{
	TickType_t tick;
	uint32_t dmpresetCounter = 0, PIDcounter = 0;
	
	
	AngleTarget[0] = 0;
	AngleTarget[1] = 0;
	
	vTaskDelay(2000);
	
	while(1)
	{
		tick = xTaskGetTickCount();
		
		//dmp
        if(dmpresetCounter >= 5000)
        {
            dmpresetCounter = 0;
            mpu_set_dmp_state(0);
            mpu_set_dmp_state(1);
        }
        else
        {
            dmpresetCounter++;
        }
		mpu6050_DMPEuler(&E);
		
		//50Hz
//		if(PIDcounter >= 4)
//		{
			PIDcounter = 0;
			
			AngleReal[0] = E.Roll - AngleXOffset;
			AngleReal[1] = E.Pitch - AngleYOffset;
			
			absTarget[0] = AngleTarget[0] - AngleReal[0];
			absTarget[1] = AngleTarget[1] - AngleReal[1];
		
			if(absTarget[0] > lastAbsTarget[0] + OmegaLimit)
			{
				absTarget[0] = lastAbsTarget[0] + OmegaLimit;
			}
			else if(absTarget[0] < lastAbsTarget[0] - OmegaLimit)
			{
				absTarget[0] = lastAbsTarget[0] - OmegaLimit;
			}
		
			if(absTarget[1] > lastAbsTarget[1] + OmegaLimit)
			{
				absTarget[1] = lastAbsTarget[1] + OmegaLimit;
			}
			else if(absTarget[1] < lastAbsTarget[1] - OmegaLimit)
			{
				absTarget[1] = lastAbsTarget[1] - OmegaLimit;
			}
		
			lastAbsTarget[0] = absTarget[0];
			lastAbsTarget[1] = absTarget[1];
			
			steering_AngleControl('X', absTarget[0]);
			steering_AngleControl('Y', absTarget[1]);
//		}
//		else
//		{
//			PIDcounter++;
//		}
		
		vTaskDelayUntil(&tick, 5);
//		vTaskDelay(5);
	}
}
