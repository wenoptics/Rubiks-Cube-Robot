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

}
