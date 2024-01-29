
//Window for platform Windows
#ifndef _WINDOWS_WINDOW_H
#define _WINDOWS_WINDOW_H


#include "Window.h"
#include "Renderer/OpenGLContext.h"
namespace Engine
{

	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* m_Window;
		std::unique_ptr<OpenGLContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	};






}


#endif // !_WINDOWS_WINDOW_H