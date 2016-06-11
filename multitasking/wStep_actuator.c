#include "consts.c"
#include "electricBase.c"
#include "globalVariables.h"
#include "actions.c"
#include "actionUnite.c"
#include "wStepContainer.c"

void push_wSteps() {

    wSequence_pushOne("LS2");
    wSequence_pushOne("LS2");
    wSequence_pushOne("LS1i");
    wSequence_pushOne("LS1i");
    wSequence_pushOne("LS4");
    wSequence_pushOne("LS4");
    wSequence_pushOne("LS3i");
    wSequence_pushOne("LS3i");
    wSequence_pushOne("LS4");
    wSequence_pushOne("RT");
    wSequence_pushOne("LS1i");
    wSequence_pushOne("LS1i");
    wSequence_pushOne("LS3i");
    wSequence_pushOne("LS3i");
    wSequence_pushOne("LS2");
    wSequence_pushOne("LS2");
}

task main() {

    wSequence_reset();
    push_wSteps();

    wStep* thisStep;
    while ( 1 ) {


        thisStep = wSequence_getNext();

        if ( !thisStep )
            // 've read all the sequence
            break;

        writeDebugStream("%d ", thisStep->action);

        switch (thisStep->type) {
            case WsTEP_TYPE_LS:
            // we are dealing with a LS-type action
                if (state_currentPlatformPosition == STATE_PLATFORM_AT_BOTTOM_LIMIT) {
                    // the PT is at bottom
                    //     then we should move the PT up
                    action_PT_up_fromBottom_toLSn(thisStep->value);

                } else {
                    // the PT is at LS..
                    int current_ls = getCurrentPT_LS();
                    action_PT_fromLS_toLS(current_ls, thisStep->value );
                }

                // then we rotate LS
                if ( thisStep->isInverse ) {
                    action_LS_turn_90i();
                } else {
                    action_LS_turn_90();
                }

            break;
            case WsTEP_TYPE_RT:
            // we are dealing with a RT-type action

                if (state_currentPlatformPosition == STATE_PLATFORM_AT_BOTTOM_LIMIT) {
                // the PT is at bottom

                    if ( thisStep->isInverse ) {
                    // according to the instruction, we should rotate the cube to BEHIND

                        if (state_currentRotatePosition == STATE_ROTATE_AT_INIT) {
                        // good, we can directly rotate the RT
                            action_RTrotateToBehind();

                        } else if(state_currentRotatePosition == STATE_ROTATE_AT_BEHIND) {
                        // but the RT is already at BEHIND pos...
                            // then we should first rotate RT to front
                            unite_PT_holdTheCube_thenRotateRT(STATE_ROTATE_AT_INIT);
                            // then we rotate to behind
                            action_RTrotateToBehind();

                        }

                    } else {
                    // else, according to the instruction, we should rotate the cube to FRONT

                        if (state_currentRotatePosition == STATE_ROTATE_AT_INIT) {
                        // but the RT is already at FRONT pos...
                            // then we should first rotate RT to behind
                            unite_PT_holdTheCube_thenRotateRT(STATE_ROTATE_AT_BEHIND);
                            // then we rotate to front
                            action_RTrotateToFront();

                        } else if(state_currentRotatePosition == STATE_ROTATE_AT_BEHIND) {
                        // good, we can directly rotate the RT
                            action_RTrotateToFront();
                        }
                    }


                } else {
                    // the PT is at LS..
                    //      good, we can just sent the PT down
                    if ( thisStep-> isInverse) {
                    // according to the instruction, we should rotate the cube to BEHIND
                        // we first make RT ready at the position of Front
                        unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);
                        // then we rotate to behind
                        action_RTrotateToBehind();

                    }else{
                    // else, according to the instruction, we should rotate the cube to FRONT
                        // we first make RT ready at the position of Behind
                        unite_PT_down_toLimit(STATE_ROTATE_AT_BEHIND);
                        // then we rotate to front
                        action_RTrotateToFront();
                    }
                }

            break;
            default :
                ;
        }

        PlaySound(soundFastUpwardTones);

    }

    PlaySound(soundUpwardTones);

    // all done, sent the PT down
    unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);

    while (1) {
    		wait1Msec(msForMultiTasking);
    }
}
