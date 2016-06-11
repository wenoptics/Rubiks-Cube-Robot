// wStep sequence
#define _maxActionNameLength 5
#define _capcity 1000

const int WsTEP_TYPE_UNKNOWN = -1;
const int WsTEP_TYPE_LS = 0;
const int WsTEP_TYPE_RT = 1;

typedef struct {
    int type;
    string action;
} wStep ;

wStep _oneStctStep;

char _wStepStrArr[_capcity][_maxActionNameLength];
int _nowIndex = -1;

void wSequence_reset() {
    _nowIndex = -1;
}

bool wSequence_pushOne(const string & oneStep) {

    if ( _nowIndex + 1 >=  _capcity)
        {return false;}

    ++_nowIndex;

    // string -> char arr
    int len = strlen(oneStep);
    for (int i=0; i<len ; i++) {
        _wStepStrArr[_nowIndex][i] = StringGetChar(oneStep, i);
    }

    return true;
}

wStep* wSequence_getNext() {

    if (_nowIndex < 0)
        return NULL;

    char cStep[_maxActionNameLength];
    for (int i=0; i<_maxActionNameLength ; i++) {
        cStep[i] = _wStepStrArr[_nowIndex][i];
    }

    string strStep="";
    StringFromChars(strStep, cStep);

    if ( StringFind(strStep, "LS")>=0 ) {
        _oneStctStep.type = WsTEP_TYPE_LS;

    } else if ( StringFind(strStep, "RT")>=0 ) {
        _oneStctStep.type = WsTEP_TYPE_RT;

    } else {
        _oneStctStep.type = WsTEP_TYPE_UNKNOWN;
    }

    _oneStctStep.action = strStep;

    _nowIndex--;

    return _oneStctStep;

}
