

#ifndef _UTILS_H
#define _UTILS_H

#include <glad/glad.h>

#define ASSERT(x) if (!(x)) __debugbreak() //MSVC
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);




#endif // !_LOG_UTIL_H
