/* Using Tasks for Arduino */
#include <Tasks.h>
#include <plugins/maestro.h>

/* Tasks are in self-contained folders for cleanliness */
#include "Tasks/Blink/Blink.h"
#include "Tasks/motionControl/motionControl.h"
#include "Tasks/proximitySensing/proximitySensing.h"

/* Schedule configuration and initialisation */
void setup(){
  /* Remember to include plugins in the number of tasks */
  Schedule.begin(4);
  
	Serial.begin(115200);
  Serial.println("Start");

  blink_Init();
	Schedule.addTask("blink", blink_update, 0, 10);

  proximitySensing_Init();
	Schedule.addTask("IR sensors", proximitySensing_update, 1, 500);
 
  motionControl_Init();
  Schedule.enablePlugin(maestro.pluginTask, 5, 10); 
	Schedule.addTask("Motion control", motionControl_update, 3, 100);

  /* 1 ms ticks */
	Schedule.startTicks(1);
}

/* Run tasks according to the configured schedule */
void loop(){
	Schedule.runTasks();
}
