#include "consts.h"
#include "baseFram.h"
#include "globalVariables.h"

/// RTRotateToLean
void actionFrame_start_RTRotateToLean() {
    switch( state_currentRotatePosition ) {
        case STATE_ROTATE_AT_LEAN:
            return;            

        case STATE_ROTATE_AT_INIT:
            // we should turn a negative angle
            baseFrame_start_rotateToAngleRelatively(motorRotate, -45 * tRatioRT, 40);
            break;
            
        case STATE_ROTATE_AT_BEHIND:
            // we should turn a positive angle
            baseFrame_start_rotateToAngleRelatively(motorRotate, 45 * tRatioRT, 40);
            break;

        default:
            return;
    }
}

void actionFrame_runCondition_RTRotateToLean() {
    return (baseFrame_runCondition_rotateToAngleRelatively(motorRotate));
}

void actionFrame_end_RTRotateToLean() {
    baseFrame_end_rotateToAngleRelatively(motorRotate);
    state_currentRotatePosition = STATE_ROTATE_AT_LEAN;
}

///RTRotateToFront
void actionFrame_start_RTRotateToFront() {
    switch( state_currentRotatePosition ) {
        case STATE_ROTATE_AT_LEAN:            
            baseFrame_start_RTRotateToPosition(motorRotate, 1);
            break;

        case STATE_ROTATE_AT_BEHIND:
            baseFrame_start_RTRotateToPosition(motorRotate, 1);
            break;

        case STATE_ROTATE_AT_INIT:
            return;
            
        default:
            return;
    }
}
void actionFrame_runCondition_RTRotateToFront() {
    return (baseFrame_runCondition_RTRotateToPosition(motorRotate));
}
void actionFrame_end_RTRotateToFront() {
    baseFrame_runCondition_RTRotateToPosition(motorRotate);
    state_currentRotatePosition = STATE_ROTATE_AT_INIT;
}


///RTRotateToBehind
void actionFrame_start_RTRotateToBehind() {
    switch( state_currentRotatePosition ) {
        case STATE_ROTATE_AT_LEAN:            
            baseFrame_start_RTRotateToPosition(motorRotate, -1);
            break;

        case STATE_ROTATE_AT_INIT:
            baseFrame_start_RTRotateToPosition(motorRotate, -1);
            break;

        case STATE_ROTATE_AT_BEHIND:
            return;
            
        default:
            return;
    }
}
void actionFrame_runCondition_RTRotateToBehind() {
    return (baseFrame_runCondition_RTRotateToPosition(motorRotate));
}
void actionFrame_end_RTRotateToBehind() {
    baseFrame_runCondition_RTRotateToPosition(motorRotate);
    state_currentRotatePosition = STATE_ROTATE_AT_BEHIND;
}