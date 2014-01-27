int   pidRunning = 1; 																									//init some PID variables
float pidRequestedValue = 0;

void lift_set_override(int speed) {																			//directly set PWM vals to lift motors
	motor[leftTopLift] = speed;
	motor[leftBottomLift] = speed;
	motor[rightTopLift] = speed;
	motor[rightBottomLift] = speed;
}

//TODO: WAYPOINTS
//do it with PID setpoitns
task lift() {
	while (true) {
		if(vexRT[Btn6UXmtr2] || vexRT[Btn6U]){															//if trigger up, turn PID off and override motors up, then turn PID on for the new position
			pidRunning = 0;
			lift_set_override(127);
			pidRequestedValue = getMotorEncoder(port6);
			}else if(vexRT[Btn6DXmtr2] || vexRT[Btn6D]){											//if trigger up, turn PID off and override motors up, then turn PID on for the new position
			pidRunning = 0;
			lift_set_override(-127);
			pidRequestedValue = getMotorEncoder(port6);
			}else{																														//else keep running PID
			pidRunning = 1;
		}
		wait1Msec(1); 																											//limit update rate of lift control, useful for future PID setpoint changes
	}
}
