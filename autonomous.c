#define AUTON_SELECT_THRESHOLD 100

void pre_auton() {
	// ...
}

task autonomous() {
	if(SensorBoolean[fieldColor]){			//if jumper is in then we are on the red side
		if(SensorValue[auton_select] < AUTON_SELECT_THRESHOLD){
			//run hanging zone
			}else{
			//run middle zone
		}
		}else{
		if(SensorValue[auton_select] < AUTON_SELECT_THRESHOLD){
			//run hanging zone
			}else{
			//run middle zone
		}
	}
}
