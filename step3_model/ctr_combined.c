


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

        if(nNxtButtonPressed == BTN_Right_Arrow) {
            action_PT_toLSn_fromBottom(1);
        }
        if(nNxtButtonPressed == BTN_Left_Arrow) {

        }
        if(nNxtButtonPressed == BTN_Orange_Square) {
            PlaySound(soundShortBlip);
            wait1Msec(500);
            while(1) {

                nxtDisplayString(1, "   rotate to:   ");
                nxtDisplayString(2, "<-Behind Front->");

                if(nNxtButtonPressed == BTN_Right_Arrow) {
                    break;
                }
                if(nNxtButtonPressed == BTN_Left_Arrow) {
                    break;
                }

                if(nNxtButtonPressed == BTN_Orange_Square) {
                    break;
                }

            }
            PlaySound(soundUpwardTones);
            wait1Msec(500);
        }
    }
}
