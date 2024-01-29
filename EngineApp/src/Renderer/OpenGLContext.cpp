
#include "../PCH.h" //TEMP

#include "OpenGLContext.h"




namespace Engine
{

	std::unique_ptr<OpenGLContext> OpenGLContext::Create(void* window)
	{
		/*#ifdef OPENGL..
		#endif */
		return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));

	}



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		ENGI_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGI_CORE_ASSERT(status, "Failed to initialize Glad!");

		ENGI_CORE_INFO("OpenGL Info:");
		ENGI_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ENGI_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ENGI_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
