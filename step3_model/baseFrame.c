#include "consts.h"

/// rotateToAngleRelatively 
void baseFrame_start_rotateToAngleRelatively(int motorName, int relativAngle, int moveSpeed) {

	moveSpeed = abs(moveSpeed);

    nMotorEncoder[motorName] = 0;  //clear the LEGO motor encoders

    nMotorEncoderTarget[motorName] = relativAngle; //set the target stoping position

    if (relativAngle < 0) {
        moveSpeed = -moveSpeed;
    }

    motor[motorName] = moveSpeed; //turn both motors on at 30 percent power
}

bool baseFrame_runCondition_rotateToAngleRelatively(int motorName) {
	return nMotorRunState[motorName] != runStateIdle;
}

void baseFrame_end_rotateToAngleRelatively(int motorName) {
    motor[motorName] = 0;
}

/// RTRotateToPosition
void baseFrame_start_RTRotateToPosition(int motorName, int direction) {
	direction = direction>0 ? 1 : -1;
	motor[motorName] = direction * 15;
}

void baseFrame_runCondition_RTRotateToPosition(int motorName) {
    return (SensorValue[sensorLightRotate] < rotateLimitLightThreshold);
}

void baseFrame_end_RTRotateToPosition(int motorName) {
    motor[motorName] = 0;
}