#include "actionFrame.h"

void action_PT_toBottomLimit(bool ignoreCurrentPos=false) {

    if ( !ignoreCurrentPos )
        if (state_currentPlatformPosition < STATE_PLATFORM_AT_LS1)
            return;

    //if(! isCubeAttached())
    //  return;

    const int confidentialMovedDownVal = 800;

    int fromEncoderVal = nMotorEncoder[motorPlatform];

    int haveTask = 0;
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
    } while(haveTask);

    // the cube is landed on the RT shelf,
    //      hide(move down) the platform;
    setAngleRelative(motorPlatform, 350, 80);

    state_currentPlatformPosition = STATE_PLATFORM_AT_BOTTOM_LIMIT;

}
