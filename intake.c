bool intakeContinuousToggle = false;

void intake_set(int speed) {																								//directly set PWM vals
	motor[rightIntake] = speed;
	motor[leftIntake] = speed;
}

task intake() {																															//main intake loop
	while (true) {
		if(vexRT[Btn5U] || vexRT[Btn5UXmtr2]){
			intake_set(127);
			}else if(vexRT[Btn5D] || vexRT[Btn5DXmtr2]){
			intake_set(-127);
			}else if(intakeContinuousToggle){
			intake_set(127);
			}else{
			intake_set(0);
			}
		wait1Msec(1);
	}
}
