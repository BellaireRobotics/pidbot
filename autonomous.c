#define AUTON_SELECT_THRESHOLD 100

void pre_auton() {
	// ...
}

task autonomous() {

	StartTask(lift);
	StartTask(pidController);
//	jiggle intake and move forward

	drive_set(-127,0);
	wait1Msec(300);
	drive_set(127,0);
	wait1Msec(200);
	drive_set(0,0);


//	intake spin

	intake_set(127);

//	move forward

	drive_set(-127,0);

	wait1Msec(600);

//	turn back and left or back and right

	intake_set(0);

	drive_set(0,0);
	wait1Msec(150);

	drive_set(0,100);		//	TURNING LINE, BLUE IS RIGHT -RED IS LEFT

	wait1Msec(240);
	drive_set(0,0);

//	lift all the way

	pidRunning = 1;
	pidRequestedValue = LIFT_HANG_HEIGHT;


	wait1Msec(1500);
//	move back all the way

	drive_set(70,0);

	wait1Msec(2100);
	drive_set(0,0);

//	set pid floor

	pidRequestedValue = LIFT_FLOOR_HEIGHT;


	wait1Msec(1000);

	pidRunning = 0;

	lift_set_override(-127);

	wait1Msec(3000);

			SensorValue[pneumaticLock1] = true;
			SensorValue[pneumaticLock2] = true;

	lift_set_override(0);
//	lock pneumatics

}
