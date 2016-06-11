#include "wStepContainer.c"

task main() {
    wSequence_reset();
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

    wStep* oneStep;
    while ( 1 ) {

        oneStep = wSequence_getNext();

        if ( !oneStep )
            // reach the end
            break;

        writeDebugStream("%d ", oneStep->type);

    }

    while (1) {;}
}
