// wStep sequence
#define _maxActionNameLength 5
#define _capcity 1000

const int WsTEP_TYPE_UNKNOWN = -1;
const int WsTEP_TYPE_LS = 0;
const int WsTEP_TYPE_RT = 1;

typedef struct {
    int type;           // LS or RT
    string action;      // the raw string of action, e.g. "LS3i"
    int value;          // extra value for LS, e.g. 3
    bool isInverse;     //
} wStep ;

wStep _oneStctStep;

char _wStepStrArr[_capcity][_maxActionNameLength];
int _nowReadIndex = -1, _nowWriteIndex = -1;

void wSequence_reset() {
    _nowReadIndex = -1;
    _nowWriteIndex = -1;
}

bool wSequence_pushOne(const string & oneStep) {

    if ( _nowWriteIndex + 1 >=  _capcity)
        {return false;}

    ++_nowWriteIndex;

    // string -> char arr
    int len = strlen(oneStep);
    for (int i=0; i<len ; i++) {
        _wStepStrArr[_nowWriteIndex][i] = StringGetChar(oneStep, i);
    }

    return true;
}

wStep* wSequence_parseWStep(const string & strStep) {

    bool isBadInstruction = false;

    if ( StringFind(strStep, "LS")>=0 ) {

        _oneStctStep.type = WsTEP_TYPE_LS;

        // extract the n value of LS
        char charN = StringGetChar(strStep, 2);
        int n = charN - '0';
        if (n >=1 && n <= 4) {
            _oneStctStep.value = n;
        } else {
            // bad instruction
            isBadInstruction = true;
        }

        // is inverse?
        charN = StringGetChar(strStep, 3);
        if ( charN == 'i' ) {
            _oneStctStep.isInverse = true;
        } else {
            _oneStctStep.isInverse = false;
        }

    } else if ( StringFind(strStep, "RT")>=0 ) {
        _oneStctStep.type = WsTEP_TYPE_RT;

        // is inverse?
        char charN = StringGetChar(strStep, 2);
        if ( charN == 'i' ) {
            _oneStctStep.isInverse = true;
        } else {
            _oneStctStep.isInverse = false;
        }

    } else {
        _oneStctStep.type = WsTEP_TYPE_UNKNOWN;
    }

    // TODO: maybe we will have a better implementation here
    //       - dealing with bad situation.
    if (isBadInstruction) {
        _oneStctStep.type = WsTEP_TYPE_UNKNOWN;
    }

    _oneStctStep.action = strStep;

    return &_oneStctStep;
}

wStep* wSequence_getNext() {

    if ( _nowReadIndex  >=  _nowWriteIndex)
        return NULL;

    if ( _nowWriteIndex < 0)
        return NULL;

    _nowReadIndex++;

    char cStep[_maxActionNameLength];
    for (int i=0; i<_maxActionNameLength ; i++) {
        cStep[i] = _wStepStrArr[_nowReadIndex][i];
    }

    string strStep="";
    StringFromChars(strStep, cStep);

    wSequence_parseWStep(strStep);

    return &_oneStctStep;

}
