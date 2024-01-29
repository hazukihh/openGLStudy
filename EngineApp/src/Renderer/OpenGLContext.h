#pragma once
#ifndef _OPENGL_CONTEXT_H
#define _OPENGL_CONTEXT_H



#include <memory>
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Engine
{

	/*class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static std::unique_ptr<GraphicsContext> Create(void* window);
	};*/



	class OpenGLContext
	{
	private:
		GLFWwindow* m_WindowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() = default;
		void Init();
		void SwapBuffers();

		static std::unique_ptr<OpenGLContext> Create(void* window);
		
	};




}


#endif // !_OPENGL_CONTEXT_H