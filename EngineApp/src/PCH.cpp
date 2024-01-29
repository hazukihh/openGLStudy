#include "PCH.h"


/*
* PCH（Precompiled Header）
* 作为前期需要做的一部分，PCH可以将Header编译成intermediate object，
* 进而只要其不被改变，就可以节省下一次编译的时间，
* 对于几乎每一个.cpp都要用到的#include，我们可以将其放在PCH中进行编译。
*/