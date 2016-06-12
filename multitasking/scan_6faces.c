#include "consts.c"
#include "electricBase.c"
#include "globalVariables.h"
#include "actions.c"
#include "actionUnite.c"
#include "wStepContainer.c"

void scanNow() {
	PlaySound(soundShortBlip);
	wait10Msec(100);
}

task main() {


	// scan face 1
	scanNow();

	action_PT_up_fromBottom_toLSn(4);
	action_LS_turn_90();
	unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);
	// scan face 2
	scanNow();

	action_PT_up_fromBottom_toLSn(4);
	action_LS_turn_90();
	unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);
	// scan face 3
	scanNow();

	action_PT_up_fromBottom_toLSn(4);
	action_LS_turn_90();
	unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);
	// scan face 4
	scanNow();

	action_RTrotateToBehind();
	unite_PT_holdTheCube_thenRotateRT(STATE_ROTATE_AT_INIT);
	// scan face 5
	scanNow();

	action_PT_up_fromBottom_toLSn(4);
	action_LS_turn_90();
	action_LS_turn_90();
	unite_PT_down_toLimit(STATE_ROTATE_AT_INIT);
	// scan face 5
	scanNow();


	PlaySound(soundBeepBeep);
	while(1) {;}

}
