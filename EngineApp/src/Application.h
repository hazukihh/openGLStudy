
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Event/Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "ImGuiLayer.h"

namespace Engine
{
	//TEMP
	/*struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			ENGI_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};*/



	class Application
	{
	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		ImGuiLayer* m_ImGuiLayer;
		//ApplicationSpecification m_Specification;



		static Application* s_Instance;

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }


		void Close();

		//ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer;}

		static Application& Get() { return *s_Instance; }

		

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};



	// To be defined in Client
	Application* CreateApplication();
	//TEMP
	//Application* CreateApplication(ApplicationCommandLineArgs args);
}

#endif