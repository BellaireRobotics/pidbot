#define INTAKE_JOY_THRESHOLD 15

void intake_set(int speed) {																								//directly set PWM vals
	motor[rightIntake] = speed;
	motor[leftIntake] = speed;
}

task intake() {																															//main intake loop
	while (true) {
		if (vexRT[Btn5U] || vexRT[Btn5UXmtr2] || -vexRT[Ch2Xmtr2] > INTAKE_JOY_THRESHOLD) {
		intake_set(vexRT[Btn5U] || vexRT[Btn5UXmtr2] ? 127 : -vexRT[Ch2Xmtr2]);
			} else if (vexRT[Btn5D] || vexRT[Btn5DXmtr2] || -vexRT[Ch2Xmtr2] < -INTAKE_JOY_THRESHOLD) {
		intake_set(vexRT[Btn5D] || vexRT[Btn5DXmtr2] ? -127 : -vexRT[Ch2Xmtr2]);
			} else {
			intake_set(0);
		}
		wait1Msec(1);
	}
}
