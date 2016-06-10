#include "consts.c"
#include "globalVariables.h"

void setAngleRelative(int motorName, int relativeAngle, int moveSpeed)
{
    moveSpeed = abs(moveSpeed);

    nMotorEncoder[motorName] = 0;  //clear the LEGO motor encoders

    nMotorEncoderTarget[motorName] = relativeAngle; //set the target stoping position

    if (relativeAngle < 0) {
        moveSpeed = -moveSpeed;
    }

    motor[motorName] = moveSpeed; //turn both motors on at 30 percent power

    while (nMotorRunState[motorName] != runStateIdle) //while the encoder wheel turns one revolution
    {
        wait1Msec(msForMultiTasking);
    }

    motor[motorName] = 0;

}
