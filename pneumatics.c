task pneumatics() {
  while (true) {
    if (vexRT[Btn7U] || vexRT[Btn7UXmtr2]) {
      SensorValue[pneumaticLock1] = 1;
      SensorValue[pneumaticLock2] = 1;
    }

    if (vexRT[Btn7D] || vexRT[Btn7DXmtr2]) {
      SensorValue[pneumaticLock1] = 0;
      SensorValue[pneumaticLock2] = 0;
    }

    wait1Msec(1);
  }
}
