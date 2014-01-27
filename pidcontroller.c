#define PID_MOTOR_SCALE    (-1)
#define PID_DRIVE_MAX       127
#define PID_DRIVE_MIN     (-127)
#define PID_INTEGRAL_LIMIT  40

float  pid_Kp = 1;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

float  pidSensorCurrentValue = 0;
float  pidError = 0;
float  pidLastError = 0;
float  pidIntegral = 0;
float  pidDerivative = 0;
float  pidDrive = 0;

task pidController(){
	while(1){
		if(pidRunning){																														//check if we should run PID

			pidSensorCurrentValue = getMotorEncoder(port6);													//getting current position

			pidError = pidSensorCurrentValue - pidRequestedValue;										//calculating error signal

			if(abs(pidError) < PID_INTEGRAL_LIMIT){																	//calculating integral factor, given it is within bounds
				pidIntegral = pidIntegral + pidError;
				}else{
				pidIntegral = 0;
			}

			pidDerivative = pidError - pidLastError;																//calculate derivative factor
			pidLastError  = pidError;

			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);					//sum all factors

			if(pidDrive > PID_DRIVE_MAX){																						//limit max output
				pidDrive = PID_DRIVE_MAX;
				}if(pidDrive < PID_DRIVE_MIN){
				pidDrive = PID_DRIVE_MIN;
			}

			lift_set_override(pidDrive * PID_MOTOR_SCALE);													//set lift motors

		}
		else{																																			//reset all
			pidError = 0;
			pidLastError = 0;
			pidIntegral = 0;
			pidDerivative = 0;
			lift_set_override(0);
		}
		wait1Msec(25);																														//motor controllers update at 60Hz, hence it is a waste of cycles to run any faster
	}
}
