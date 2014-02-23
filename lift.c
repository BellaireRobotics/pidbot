
#define LIFT_MINIMUM_HEIGHT 		0																	//TODO:empirically determined waypoint heights
#define LIFT_FLOOR_HEIGHT 			0
#define LIFT_BUMP_HEIGHT 				150
#define LIFT_STASH_HEIGHT 			1100
#define LIFT_HANG_HEIGHT				1280

int   pidRunning = 1; 																								//init some PID variables
float pidRequestedValue = 0;

void lift_set_override(int speed) {																		//directly set PWM vals to lift motors
	motor[leftTopLift] = speed;
	motor[leftBottomLift] = speed;
	motor[rightTopLift] = speed;
	motor[rightBottomLift] = speed;
}

task lift() {
	while (true) {
		if(vexRT[Btn8UXmtr2] || vexRT[Btn8U]){														//check stash waypoint
			pidRequestedValue = LIFT_STASH_HEIGHT;
		}else if(vexRT[Btn8LXmtr2] || vexRT[Btn8L]){											//check bump waypoint
			pidRequestedValue = LIFT_BUMP_HEIGHT;
		}else if(vexRT[Btn8DXmtr2] || vexRT[Btn8D]){											//check floor waypoint
			pidRequestedValue = LIFT_FLOOR_HEIGHT;
		}else if(vexRT[Btn8RXmtr2] || vexRT[Btn8R]){											//check hang waypoint
			pidRequestedValue = LIFT_HANG_HEIGHT;
		}else if(vexRT[Btn6UXmtr2] || vexRT[Btn6U]){											//if trigger up, turn PID off and override motors up, then turn PID on for the new position
			pidRunning = 0;
			lift_set_override(127);
			pidRequestedValue = nMotorEncoder(leftTopLift);
		}else if(vexRT[Btn6DXmtr2] || vexRT[Btn6D]){											//if trigger up, turn PID off and override motors up, then turn PID on for the new position
			pidRunning = 0;
			lift_set_override(-127);
			pidRequestedValue = nMotorEncoder(leftTopLift);
		}else{																														//else keep running PID
			pidRunning = 1;
		}
		wait1Msec(1); 																										//limit update rate of lift control, useful for future PID setpoint changes
	}
}
