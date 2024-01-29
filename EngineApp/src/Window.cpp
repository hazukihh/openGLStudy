
#include <memory>
#include "Window.h"
#ifdef ENGI_PLATFORM_WINDOWS
#include "WindowsWindow.h"
#endif 

namespace Engine
{


	std::unique_ptr<Window> Window::Create(const WindowProps& props /*= WindowProps()*/)
	{
#ifdef ENGI_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(props);
#else
		return nullptr;
#endif 


	}


}


