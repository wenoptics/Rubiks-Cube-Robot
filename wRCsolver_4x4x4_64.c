#pragma config(Sensor, S2,     sensorLightLSRotate, sensorLightActive)
#pragma config(Sensor, S3,     sensorLightRotate, sensorLightActive)
#pragma config(Sensor, S4,     sensorCubeAttatch, sensorTouch)
#pragma config(Motor,  motorA,          motorRotate,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorPlatform, tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motorLS,       tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "encoderMotor_improved.h"

const float tRatioRT = (float)56 / 23;
const float tRatioLS = (float)40 / 8;

const int rotateLimitLightThreshold = 76;
const int LSRotateLightThreshold = 65;

const int ENCODERvAL_LS_BASE = -1830;
const int ENCODERvAL_LS_ARRAY[] = {
    ENCODERvAL_LS_BASE,
    // Below is the increasement value of LS
    0,          // LS1
    -380,       // LS2
    -730,       // LS3
    -1110       // LS4
};

void showSensorVal() {
    //while (1) {
        eraseDisplay();

        //nxtDisplayString(2, "%d", nMotorEncoder[motorPlatform]);
        nxtDisplayString(2, "%d", SensorValue[sensorLightLSRotate]);
        //wait1Msec(20);
    //}
}

void setAngleRelative(int motorName, int relativAngle, int moveSpeed)
{
    moveSpeed = abs(moveSpeed);

    nMotorEncoder[motorName] = 0;  //clear the LEGO motor encoders

    nMotorEncoderTarget[motorName] = relativAngle; //set the target stoping position

    if (relativAngle < 0) {
        moveSpeed = -moveSpeed;
    }

    motor[motorName] = moveSpeed; //turn both motors on at 30 percent power

    while (nMotorRunState[motorName] != runStateIdle) //while the encoder wheel turns one revolution
    {
        showSensorVal();
        // This condition waits for motors B + C to come to an idle position. Both motors stop
        // and then jumps out of the loop
    }

    motor[motorName] = 0; //turn both motors off

    //wait1Msec(3000);  // wait 3 seconds to see feedback on the debugger screens
    // open the "NXT Devices" window to see the distance the encoder spins.
    // the robot will come to a stop at the nMotorEncoderTarget position.
}


void action_PT_goUp() {
    motor[motorPlatform] = -100;
}

void action_PT_goDown() {
    motor[motorPlatform] = 100;
}

void action_PT_stop() {
    motor[motorPlatform] = 0;
}


bool isRTAtInitPositon () {
    return (SensorValue[sensorLightRotate] >= rotateLimitLightThreshold);
}

void RTrotateToPosition(int motorName) {

    while ( SensorValue[sensorLightRotate] < rotateLimitLightThreshold) {
        motor[motorName] = 15;
    }
    motor[motorName] = 0;


}

const int BTN_Gray_Rectangle = 0;
const int BTN_Right_Arrow = 1;
const int BTN_Left_Arrow = 2;
const int BTN_Orange_Square = 3;

const int STATE_ROTATE_AT_INIT = 0;
const int STATE_ROTATE_AT_BEHIND = 1;
const int STATE_ROTATE_AT_ELSE = 2;

const char STATE_PLATFORM_AT_BOTTOM_LIMIT = 0;
const char STATE_PLATFORM_AT_LS1 = 101;
const char STATE_PLATFORM_AT_LS2 = 102;
const char STATE_PLATFORM_AT_LS3 = 103;
const char STATE_PLATFORM_AT_LS4 = 104;

int state_currentRotatePosition;
int state_currentPlatformPosition;

void action_rotateToBehind() {
    if (state_currentRotatePosition == STATE_ROTATE_AT_BEHIND)
        return;
    setAngleRelative(motorRotate, -93*tRatioRT, -30);
    state_currentRotatePosition = STATE_ROTATE_AT_BEHIND;
}

void action_rotateToFront() {
    if (state_currentRotatePosition == STATE_ROTATE_AT_INIT)
        return;
    setAngleRelative(motorRotate, 70*tRatioRT, 30);
    RTrotateToPosition(motorRotate);
    state_currentRotatePosition = STATE_ROTATE_AT_INIT;
}

/// Whether the cube is attached to the platform
bool isCubeAttached() {
    return SensorValue[sensorCubeAttatch]   == 1;
}

void waitUntilCubeDettached_filtered() {

    while(isCubeAttached()) {
        while (isCubeAttached()) {}
        wait1Msec(90);
    }
}

bool action_PT_toLSn_fromBottom(int n) {

    if (state_currentPlatformPosition != STATE_PLATFORM_AT_BOTTOM_LIMIT)
        return false;

    int destVal, finalStateVal;

    destVal = ENCODERvAL_LS_BASE + ENCODERvAL_LS_ARRAY[n];
    switch(n) {
        case 1:
            finalStateVal = STATE_PLATFORM_AT_LS1;
            break;
        case 2:
            finalStateVal = STATE_PLATFORM_AT_LS2;
            break;
        case 3:
            finalStateVal = STATE_PLATFORM_AT_LS3;
            break;
        case 4:
            finalStateVal = STATE_PLATFORM_AT_LS4;
            break;
        defaut: return false;
    }

    if (! isCubeAttached())
    {
        // we assume the platform is at the below

        nMotorEncoder[motorPlatform] = 0;

        action_PT_goUp();
        int encoderVal;
        while ( ! isCubeAttached()) {
            encoderVal = nMotorEncoder[motorPlatform];

            // debug display
            eraseDisplay();
            nxtDisplayString(2, "encoder=%d", encoderVal);
            wait1Msec(20);

            if (encoderVal < -800) {
                // still no cube? bad situation.
                break;
            }

        }
        action_PT_stop();
    }
    if (! isCubeAttached())
    {
        // nothing hit? I assume there's no cube on the platform!
        PlaySound(soundException);
        wait1Msec(600);

        // move the platform to the origin position
        setAngleRelative(motorPlatform, -nMotorEncoder[motorPlatform], 95);
        return false;
    }
    else
    {
        // the platform now just hit the cube
        setAngleRelative(motorPlatform, destVal, 95);

        /*
        while(1) {
            eraseDisplay();
            nxtDisplayString(2, "encoder=%d", nMotorEncoder[motorPlatform]);
            wait1Msec(20);
        }
        */

    }

    state_currentPlatformPosition = finalStateVal;
    return true;
}


void swingTheLS() {

    for(int i=0; i< 5; i++) {
            setAngleRelative(motorLS, 10*tRatioLS, 50);
            //wait1Msec(50);
            setAngleRelative(motorLS, -10*tRatioLS, 50);
            //wait1Msec(50);
    }

    //LSRotateToPosition(motorLS, -1);
}

void action_PT_toBottomLimit(bool ignoreCurrentPos=false) {

    if ( !ignoreCurrentPos )
        if (state_currentPlatformPosition < STATE_PLATFORM_AT_LS1)
            return;

    //if(! isCubeAttached())
    //  return;

    const int confidentialMovedDownVal = 800;

    int fromEncoderVal = nMotorEncoder[motorPlatform];

    do {
            action_PT_goDown();

            // this is a filtered waiting,
            //      in case of vibration making the wrong state.
            waitUntilCubeDettached_filtered();

            action_PT_stop();

            // too early for the platform to stop move down,
            //      assuming that the cube dettached accidentally
            if ( nMotorEncoder[motorPlatform] - fromEncoderVal
                            < confidentialMovedDownVal   )
            {

                setAngleRelative(motorPlatform, 360, 80);

                bool isFirst = true;
                while (! isCubeAttached())
                {
                    PlaySound(soundException);
                    if (isFirst) {
                        isFirst = false;
                        for(int i=0; i< 5; i++) {
                            setAngleRelative(motorLS, 10*tRatioLS, 50);
                            //wait1Msec(50);
                            if ( isCubeAttached()) break;
                            setAngleRelative(motorLS, -10*tRatioLS, 50);
                            //wait1Msec(50);
                            if ( isCubeAttached()) break;
                        }
                    }
                    wait1Msec(500);
                }
            }
            else {
                    break   ;
            }
    } while(1);

    // the cube is landed on the RT shelf,
    //      hide(move down) the platform;
    setAngleRelative(motorPlatform, 350, 80);

    state_currentPlatformPosition = STATE_PLATFORM_AT_BOTTOM_LIMIT;

}


void action_PT_fromLS_toLS(int LSfrom, int LSto) {

    if (state_currentPlatformPosition < STATE_PLATFORM_AT_LS1)
        return;

    //if(! isCubeAttached())
    //  return;

    int encoderVal = ENCODERvAL_LS_ARRAY[LSto] - ENCODERvAL_LS_ARRAY[LSfrom];

    setAngleRelative(motorPlatform, encoderVal, 70);

    bool isFirst = true;
    while (! isCubeAttached())
    {
        PlaySound(soundException);
        if (isFirst) {
            isFirst = false;
            for(int i=0; i< 5; i++) {
                    setAngleRelative(motorLS, 10*tRatioLS, 50);
                    //wait1Msec(50);
                    if ( isCubeAttached()) break;
                    setAngleRelative(motorLS, -10*tRatioLS, 50);
                    //wait1Msec(50);
                    if ( isCubeAttached()) break;
            }
        }
        wait1Msec(500);
    }

    switch(LSto) {
        case 1:
            state_currentPlatformPosition = STATE_PLATFORM_AT_LS1;
            break;
        case 2:
            state_currentPlatformPosition = STATE_PLATFORM_AT_LS2;
            break;
        case 3:
            state_currentPlatformPosition = STATE_PLATFORM_AT_LS3;
            break;
        case 4:
            state_currentPlatformPosition = STATE_PLATFORM_AT_LS4;
            break;
        defaut: return;
    }

}



void LSRotateToPosition(int motorName, int direction, int maxFindAngle=40*tRatioLS) {

    if (direction == 0 ) return;
    direction = direction>0 ? 1 : -1;
    const int minSearchSpeed = 25;
    int speed = 55;
    int _maxAngle, maxAngle = abs(maxFindAngle);

    bool isFirstTime=true;

    while (1) {

        // reset the encoderVal to 0
        nMotorEncoder[motorLS] = 0;

        motor[motorName] = direction * speed;
        while ( SensorValue[sensorLightLSRotate] < LSRotateLightThreshold) {

            showSensorVal();

            if (isFirstTime) {
                _maxAngle = maxAngle / 2;
                isFirstTime = false;
            }else{
                _maxAngle = maxAngle;
            }

            if (abs(nMotorEncoder[motorLS]) > _maxAngle) {
                // rotate too much?
                break;
            }

        }
        motor[motorName] = 0;

        wait1Msec(200);
        if (SensorValue[sensorLightLSRotate] < LSRotateLightThreshold) {
            // I think the rotation is just too much... rotate back
            direction *= -1;

            if (speed <= minSearchSpeed) {
                // still cannot find it. dont speed too much time on this.
                break;
            }

            // gradually decrease the speed.
            speed = speed <= minSearchSpeed ? minSearchSpeed : speed-7;

        }else{
            break;
        }
    }

    // TODO: continue to turn(small), find the largest val


}

/*
void action_LS_turn_90_v2() {
    bool hasLoad =
        (state_currentPlatformPosition >= STATE_PLATFORM_AT_LS1);

    int speed=100;

    int currentVal, destVal = 70*tRatioLS;
    setAngleRelative(motorLS, destVal, speed);

    currentVal = nMotorEncoder[motorLS];
    LSRotateToPosition(motorLS, 90*tRatioLS - currentVal);

    // turn an extra angle because of gap
    setAngleRelative(motorLS, 10*tRatioLS, speed);
    LSRotateToPosition(motorLS, -1);

}*/

void action_LS_turn_90() {
    bool hasLoad =
        (state_currentPlatformPosition >= STATE_PLATFORM_AT_LS1);

    int speed=100;

    int currentVal, destVal = 70*tRatioLS;
    setAngleRelative(motorLS, destVal, speed);

    // wait a short time for the twist force back
    wait1Msec(200);

    showSensorVal();

    currentVal = nMotorEncoder[motorLS];
    LSRotateToPosition(motorLS, 90*tRatioLS - currentVal, ((90+10)*tRatioLS-currentVal)*2 );

    // turn an extra angle because of gap
    wait1Msec(200);
    setAngleRelative(motorLS, 15*tRatioLS, 70);
    //setAngleRelative(motorLS, -10*tRatioLS, speed);
    wait1Msec(200);
    LSRotateToPosition(motorLS, -1);

}

void action_LS_turn_90i() {
    bool hasLoad =
        (state_currentPlatformPosition >= STATE_PLATFORM_AT_LS1);

    int speed=100;

    int currentVal, destVal = -70*tRatioLS;
    setAngleRelative(motorLS, destVal, speed);

    // wait a short time for the twist force back
    wait1Msec(200);

    currentVal = nMotorEncoder[motorLS];
    int deltaVal = (-(90+10)*tRatioLS-currentVal);
    LSRotateToPosition(motorLS, -90*tRatioLS - currentVal, deltaVal*2 );

    // turn an extra angle because of gap
    wait1Msec(200);
    setAngleRelative(motorLS, -15*tRatioLS, 70);
    //setAngleRelative(motorLS, 10*tRatioLS, speed);
    wait1Msec(200);
    LSRotateToPosition(motorLS, 1);


}


task main()
{

    // warning if the rotatePart is not at the correct position
    while ( ! isRTAtInitPositon ()) {
        //PlaySound(soundException);
        nxtDisplayString(2, "Rotation block is not");
        nxtDisplayString(3, "  at the init position");
        nxtDisplayString(4, "         (%d)         ", SensorValue[sensorLightRotate]);
        wait1Msec(100);
    }
    PlaySound(soundBeepBeep);
    eraseDisplay();

    if ( isCubeAttached() ) {
        // assuming the platform is at LS
        state_currentPlatformPosition = STATE_PLATFORM_AT_LS1;
        action_PT_toBottomLimit();
    }

    // do some initiation
    state_currentRotatePosition = STATE_ROTATE_AT_INIT;
    state_currentPlatformPosition = STATE_PLATFORM_AT_BOTTOM_LIMIT;
    //nMotorPIDSpeedCtrl[motorLS] = mtrSpeedReg;


    while(1) {

        showSensorVal();

        if(nNxtButtonPressed == BTN_Right_Arrow) {
            //action_PT_goDown();
            //wait1Msec(100);
            //action_PT_stop();

            //action_PT_toBottomLimit();
            action_PT_toLSn_fromBottom(4);
        }
        if(nNxtButtonPressed == BTN_Left_Arrow) {
            //action_PT_goUp();
            //wait1Msec(100);
            //action_PT_stop();

            while(1) {
                bool succ =
                    action_PT_toLSn_fromBottom(2);
                if (!succ) break;
                action_LS_turn_90();
                action_PT_fromLS_toLS(2, 1);
                action_LS_turn_90i();
                //action_rotateToBehind();
                action_PT_toBottomLimit();
                //action_rotateToFront();
            }

        }
        if(nNxtButtonPressed == BTN_Orange_Square) {
            PlaySound(soundShortBlip);
            wait1Msec(500);
            while(1) {

              nxtDisplayString(1, "rotate to:");
                nxtDisplayString(2, "<-Behind Front->");

                if(nNxtButtonPressed == BTN_Right_Arrow) {
                    //action_rotateToFront();
                    action_LS_turn_90();

                    break;
                }
                if(nNxtButtonPressed == BTN_Left_Arrow) {
                    //action_rotateToBehind();
                    action_LS_turn_90i();

                    break;
                }

                if(nNxtButtonPressed == BTN_Orange_Square) {
                    swingTheLS();
                    break;
                }

            }
            PlaySound(soundUpwardTones);
            wait1Msec(500);
        }
    }
}
