
#ifndef _WINDOW_H
#define _WINDOW_H



#include "PCH.h"
#include "Event/Event.h"

namespace Engine
{

	struct WindowProps
	{
		std::string Title;
		unsigned int  Width;
		unsigned int  Height;

		WindowProps(const std::string& title = "The Engine",
			unsigned int width = 1600,
			unsigned int height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};



	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());




	};


}


#endif // !_WINDOW_H