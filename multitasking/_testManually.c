#include "consts.c"
#include "electricBase.c"
#include "globalVariables.h"
#include "actions.c"
#include "actionUnite.c"

void showSensorVal()  {
    //while (1) {
        eraseDisplay();

        //nxtDisplayString(2, "%d", nMotorEncoder[motorPlatform]);
        nxtDisplayString(2, "%d", SensorValue[sensorLightLSRotate]);
        //wait1Msec(20);
    //}
}


void doInit() {

    // warning if the rotatePart is not at the correct position
    while ( ! isRTAtPositon ()) {
        //PlaySound(soundException);
        nxtDisplayString(2, "Rotation block is not");
        nxtDisplayString(3, "  at the init position");
        nxtDisplayString(4, "         (%d)         ", SensorValue[sensorLightRTRotate]);
        wait1Msec(100);
    }
    PlaySound(soundBeepBeep);
    eraseDisplay();

    if ( isCubeAttachedPT() ) {
        // assuming the platform is at LS
        state_currentPlatformPosition = STATE_PLATFORM_AT_LS1;
        action_PT_down_toBottomLimit();
    }

    // do some initiation
    state_currentRotatePosition = STATE_ROTATE_AT_INIT;
    state_currentPlatformPosition = STATE_PLATFORM_AT_BOTTOM_LIMIT;
    //nMotorPIDSpeedCtrl[motorLS] = mtrSpeedReg;

}



task main()
{
    doInit();

    while(1) {

        if(nNxtButtonPressed == BTN_Right_Arrow) {
            action_PT_up_fromBottom_toLSn(1);
        }
        if(nNxtButtonPressed == BTN_Left_Arrow) {

            unite_PT_down_toLimit(STATE_ROTATE_AT_BEHIND);

        }
        if(nNxtButtonPressed == BTN_Orange_Square) {
            PlaySound(soundShortBlip);
            wait1Msec(500);
            while(1) {

                nxtDisplayString(1, "   rotate to:   ");
                nxtDisplayString(2, "<-Behind Front->");

                if(nNxtButtonPressed == BTN_Right_Arrow) {
                    //action_RTrotateToFront();
                    action_LS_turn_90();

                    break;
                }
                if(nNxtButtonPressed == BTN_Left_Arrow) {
                    //action_RTrotateToBehind();
                    action_LS_turn_90i();

                    break;
                }

                if(nNxtButtonPressed == BTN_Orange_Square) {
                    //action_RTrotateToLean();
                    //swingTheLS();
                    break;
                }

            }
            PlaySound(soundUpwardTones);
            wait1Msec(500);
        }
    }
}
