
/*
* PCH（Precompiled Header）
* 作为前期需要做的一部分，PCH可以将Header编译成intermediate object，
* 进而只要其不被改变，就可以节省下一次编译的时间，
* 对于几乎每一个.cpp都要用到的#include，我们可以将其放在PCH中进行编译。
*/

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define ENGI_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif

#else
/* Unknown compiler/platform or not supported  */
#error "not supported platform!"
#endif // End of platform detection




#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


#include "Log.h"

#include "Assert.h"


#ifdef ENGI_PLATFORM_WINDOWS
#include <Windows.h>
#endif