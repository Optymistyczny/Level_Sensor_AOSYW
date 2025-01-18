#include "level_sensor_os.h"
#include "SensorManager.h"
#include "string.h"
typedef StaticEventGroup_t osStaticEventGroupDef_t;

osMessageQueueId_t SensorQueueHandle;
osEventFlagsId_t isDataAvailableEventHandle;

const osMessageQueueAttr_t SensorQueue_attributes = {
  .name = "SensorQueue"
};

osStaticEventGroupDef_t isControlBlock;
const osEventFlagsAttr_t isDataAvailableEvent_attributes = {
  .name = "isDataAvailableEvent",
  .cb_mem = &isControlBlock,
  .cb_size = sizeof(isControlBlock),
};



osStatus_t init()
{
	SensorQueueHandle = osMessageQueueNew (10, sizeof(measure_element_t), &SensorQueue_attributes);
	if (SensorQueueHandle == NULL)
	{
		return osError;
	}

	isDataAvailableEventHandle = osEventFlagsNew(&isDataAvailableEvent_attributes);
	if (isDataAvailableEventHandle == NULL)
	{
		return osError;
	}
	if(ERR==initialize())
	{
		return osError;
	}

	return osOK;
}

osStatus_t waitForMeasurement(const measure_element_t* element, uint32_t timeout)
{
	if(NULL == element || NULL == element->value || (uint32_t)element->type >= (uint32_t)measurement_type_num ||
			element->id > 31)
	{
		 return osError; // Błędne dane
	}
	if(osFlagsErrorTimeout == osEventFlagsWait(isDataAvailableEventHandle, 1<<element->id, osFlagsWaitAny, pdMS_TO_TICKS(timeout)))
	{
		return osErrorTimeout;
	}
	else return osOK;
}
osStatus_t measure(const measure_element_t* element)
{
    if(NULL == element || NULL == element->value || (uint32_t)element->type >= (uint32_t)measurement_type_num)
    {
    	 return osError; // Błędne dane
    }

	if(osOK != osMessageQueuePut(SensorQueueHandle, element, 0, 0))
	{
		return osError;
	}

    return osOK;
}

void SensorProcess(void)
{
	measure_element_t element={0};
	uint32_t currentFlags=0;
  for(;;)
  {
	  osDelay(1);
	  memset(&element,0,sizeof(element));

	  if(osOK!=osMessageQueueGet(SensorQueueHandle, &element, NULL, 0))
	  {
		  continue;
	  }
	  else
	  {
		  if(NULL == element.value || (uint32_t)element.type >= (uint32_t)measurement_type_num || element.id>31)
		  {
			  continue;
		  }
		  currentFlags = osEventFlagsGet(isDataAvailableEventHandle);
		  switch(element.type)
		  {
			  case distance_mm:
				  if(currentFlags & 1<<element.id)
				  {
					  break;
				  }
				  getDistance_mm((float*)element.value);
				  osEventFlagsSet(isDataAvailableEventHandle, 1<<element.id);
				  break;

			  case distance_m:
				  if(currentFlags & 1<<element.id)
				  {
					  break;
				  }
				  getDistance_m((float*)element.value);
				  osEventFlagsSet(isDataAvailableEventHandle, 1<<element.id);
				  break;
			  case temperatureC:
				  if(currentFlags & 1<<element.id)
				  {
					  break;
				  }
				  getTemperature_Celcious((float*)element.value);
				  osEventFlagsSet(isDataAvailableEventHandle, 1<<element.id);
				  break;

			  case temperatureF:
				  if(currentFlags & 1<<element.id)
				  {
					  break;
				  }
				  getTemperature_Fahrenheit((float*)element.value);
				  osEventFlagsSet(isDataAvailableEventHandle, 1<<element.id);
				  break;

			  default:
				  break;
		  }
	  }
  }
  //Never reaches this point
  while(1);
}


