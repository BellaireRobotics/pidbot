#define PID_DRIVE_MOTOR_SCALE    (-1)
#define PID_DRIVE_DRIVE_MAX       127
#define PID_DRIVE_DRIVE_MIN     (-127)
#define PID_DRIVE_INTEGRAL_LIMIT  40

float  pid_drive_Kp = 1;
float  pid_drive_Ki = 0.04;
float  pid_drive_Kd = 0.0;

float  pidDriveSensorCurrentValue = 0;
float  pidDriveError = 0;
float  pidDriveLastError = 0;
float  pidDriveIntegral = 0;
float  pidDriveDerivative = 0;
float  pidDriveDrive = 0;

task pidDriveController(){
	while(1){
		if(pidStraightDriveRunning){																														//check if we should run PID

			pidDriveError = SensorValue[shaftEncoderLeftDrive] - SensorValue[shaftEncoderRightDrive];										//calculating error signal

			if(abs(pidDriveError) < PID_DRIVE_INTEGRAL_LIMIT){																	//calculating integral factor, given it is within bounds
				pidDriveIntegral = pidDriveIntegral + pidDriveError;
				}else{
				pidDriveIntegral = 0;
			}

			pidDriveDerivative = pidDriveError - pidDriveLastError;																//calculate derivative factor
			pidDriveLastError  = pidDriveError;

			pidDriveDrive = (pid_drive_Kp * pidDriveError) + (pid_drive_Ki * pidDriveIntegral) + (pid_drive_Kd * pidDriveDerivative);					//sum all factors

			if(pidDriveDrive > PID_DRIVE_DRIVE_MAX){																						//limit max output
				pidDriveDrive = PID_DRIVE_DRIVE_MAX;
				}if(pidDriveDrive < PID_DRIVE_DRIVE_MIN){
				pidDriveDrive = PID_DRIVE_DRIVE_MIN;
			}

			drive_set_left(pidDriveDrive * PID_DRIVE_MOTOR_SCALE);															//set drive motor on left side to catch up to right

		}
		else{																																			//reset all
			pidDriveError = 0;
			pidDriveLastError = 0;
			pidDriveIntegral = 0;
			pidDriveDerivative = 0;
		}
		wait1Msec(25);																														//motor controllers update at 60Hz, hence it is a waste of cycles to run any faster
	}
}
