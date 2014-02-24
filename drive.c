#define JOYSTICK_DEADZONE 15  //deadzone per channel

int tempY = 0;
int tempYPartner = 0;
int tempX = 0;
int tempXPartner = 0;

int pidStraightDriveRunning = 1; // init some PID variable

const unsigned int TrueSpeed[256] = { // linearizing array, goes to 256 to save CPU cycles; xmax+ymax = 256
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
  25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
  28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
  33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
  37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
  41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
  46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
  52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
  61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
  71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
  80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
  88, 89, 89, 90, 90, 127, 127, 127,

  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127
};

void update_drive_joyvals(int *Y1, int *X1) {
  //update temp values
  tempX = vexRT[Ch1];
  tempXPartner = vexRT[Ch1Xmtr2];
  tempY = vexRT[Ch3];
  tempYPartner = vexRT[Ch3Xmtr2];

  if (abs(tempYPartner) > JOYSTICK_DEADZONE) { // check if partner overrides Y
    *Y1 = -tempYPartner / 2;
  } else {
    *Y1 = -tempY;
  }

  if (abs(tempXPartner) > JOYSTICK_DEADZONE) { // check if partner overrides X
    *X1 = tempXPartner / 2;
  } else {
    *X1 = tempX;
  }
}

void drive_set(int Y1, int X1) { // set drive speed to linearized PWM
  motor[rightFront] = sgn(Y1 + X1) * TrueSpeed[abs(Y1 + X1)];
  motor[rightBack] =  sgn(Y1 + X1) * TrueSpeed[abs(Y1 + X1)];
  motor[leftFront] = sgn(Y1 - X1) * TrueSpeed[abs(Y1 - X1)];
  motor[leftBack] =  sgn(Y1 - X1) * TrueSpeed[abs(Y1 - X1)];
}

void drive_set_left(int speed) { // directly set left power
  motor[leftFront] = speed;
  motor[leftBack] =  speed;
}

void drive_set_right(int speed) { // directly set right power
  motor[rightFront] = speed;
  motor[rightBack] =  speed;
}

task drive() { // main drive loop
  int Y1 = 0, X1 = 0;

  while (true) {
    update_drive_joyvals(&Y1, &X1);
    drive_set(Y1, X1);
    wait1Msec(1);
  }
}
