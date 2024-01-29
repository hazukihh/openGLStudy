
/*
* PCH��Precompiled Header��
* ��Ϊǰ����Ҫ����һ���֣�PCH���Խ�Header�����intermediate object��
* ����ֻҪ�䲻���ı䣬�Ϳ��Խ�ʡ��һ�α����ʱ�䣬
* ���ڼ���ÿһ��.cpp��Ҫ�õ���#include�����ǿ��Խ������PCH�н��б��롣
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