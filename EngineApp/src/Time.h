#ifndef _TIME_H
#define _TIME_H


#include "glfw/glfw3.h"

namespace Engine
{
	class Time
	{
	public:
		static float GetTime();

	};
	float Time::GetTime()
	{
		return glfwGetTime();
	}


}

#endif // !_TIME_H
