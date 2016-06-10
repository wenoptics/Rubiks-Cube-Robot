#include "electricBase.c"
#include "consts.c"
#include "globalVariables.h"
#include "actions.c"

task task_RT_rotateToLean() {
    action_RTrotateToLean();
}

task task_RT_rotateToFront() {
    action_RTrotateToFront();
}

task task_RT_rotateToBehind() {
    action_RTrotateToBehind();
}

void unite_PT_down_toLimit(int laterSetRTdstTo = state_currentRotatePosition) {

    if (state_currentPlatformPosition < STATE_PLATFORM_AT_LS1)
        return;

    //if(! isCubeAttached())
    //  return;

    int dstRT = laterSetRTdstTo;

    const int confidentialMovedDownVal = 800;
    const int edVal1 = -currentPT_to_LS1_Val() + 230;
    const int edVal2 = -currentPT_to_LS1_Val() + 1052;
    const int edVal3 = -currentPT_to_LS1_Val() + 1466;

    int procedureStep = 1;

    int fromEncoderVal = nMotorEncoder[motorPlatform];

    StartTask(task_RT_rotateToLean);

    do {
        action_PT_goDown();

        /*
        // this is a filtered waiting,
        //      in case of vibration making the wrong state.
        waitUntilCubeDettachedPT_filtered();
        */

        while (isCubeAttachedPT()) {
            int movedVal = nMotorEncoder[motorPlatform] - fromEncoderVal;

            switch(procedureStep){
                case 1:
                    // 1stly, make sure the RT rotated away before the PT move down 'edVal1'
                    if (movedVal >= edVal1) {

                        // we should stop moving down and...
                        action_PT_stop();

                        // wait for the TO-LEAN rotation complete.
                        while(state_currentRotatePosition != STATE_ROTATE_AT_LEAN)
                            { wait1Msec(msForMultiTasking);}

                        action_PT_goDown();

                        procedureStep++;
                    }
                break;
                case 2:
                    // 2ndly, make sure the PT move down to 'edVal2'
                    //       before the RT start rotating the dst position

                    if (movedVal >= edVal2) {
                        // move the RT to the dst position.

                        switch(dstRT) {
                            case STATE_ROTATE_AT_INIT  :
                                StartTask(task_RT_rotateToFront);
                            break;
                            case STATE_ROTATE_AT_BEHIND:
                                StartTask(task_RT_rotateToBehind);
                            break;
                            case STATE_ROTATE_AT_LEAN  :
                                // what?... just to front, default
                                StartTask(task_RT_rotateToFront);
                            break;
                        }

                        procedureStep++;
                    }
                break;
                case 3:
                    // 3rdly, make sure the RT has rotated to the dst position before moved down 'edVal3'
                    if (movedVal >= edVal3) {

                        // we should stop moving down and...
                        action_PT_stop();

                        // wait for the to-dst rotation complete.
                        while(state_currentRotatePosition != dstRT)
                            { wait1Msec(msForMultiTasking);}

                        action_PT_goDown();
                    }
                break;
            }

            wait1Msec(msForMultiTasking);
        }

        action_PT_stop();

        // too early for the platform to stop move down,
        //      assuming that the cube dettached accidentally
        if ( nMotorEncoder[motorPlatform] - fromEncoderVal
                        < confidentialMovedDownVal   )
        {

            setAngleRelative(motorPlatform, 360, 80);

            bool isFirst = true;
            while (! isCubeAttachedPT())
            {
                PlaySound(soundException);
                if (isFirst) {
                    isFirst = false;
                    for(int i=0; i< 5; i++) {
                        setAngleRelative(motorLS, 10*tRatioLS, 50);
                        if ( isCubeAttachedPT()) break;
                        setAngleRelative(motorLS, -10*tRatioLS, 50);
                        if ( isCubeAttachedPT()) break;

                        wait1Msec(msForMultiTasking);
                    }
                }
                wait1Msec(500);
            }
        }else {
            break;
        }
    } while(1);

    // the cube is landed on the RT shelf,
    //      hide(move down) the platform;
    setAngleRelative(motorPlatform, 310, 80);

    state_currentPlatformPosition = STATE_PLATFORM_AT_BOTTOM_LIMIT;

}
