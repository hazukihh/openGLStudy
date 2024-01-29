#include "ImGuiLayer.h"


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glfw/glfw3.h>

#include "Application.h"


#define  GLSL_VERSION  "#version 330"

namespace Engine
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}




	void ImGuiLayer::OnAttach()
	{
		//imgui_CheckVersion
		IMGUI_CHECKVERSION();
		// 1. 创建ImGui Contex
		ImGui::CreateContext();

		// 2. IO相关的Flag设置, 目前允许键盘输入、允许Dokcing、允许多个Viewport
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		//停靠於背景
		//io.ConfigFlags |= ImGuiCol_DockingEmptyBg; 




		// 加载fonts
		//float fontSize = 18.0f;// *2.0f;
		//io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
		//io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);



		// 3. 设置主题颜色
		ImGui::StyleColorsDark();
		//SetDarkThemeColors();

		// 4. 设置窗口Style和背景颜色的透明度
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;// WindowRounding代表窗口角落的值, 设置为0.0代表是矩形窗口
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;// 窗口背景透明度
		}

		//SetDarkThemeColors();		

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// 5. glfw,OpenGL相关的初始化
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{

		/*判断是否要拦截事件, block: 阻碍阻止
		* true = ImGui 层要阻止事件继续传递给其他系统
		*/
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.GetHandled() |= e.IsInCategory(EventCategory::EventCategoryMouse) & io.WantCaptureMouse;
			e.GetHandled() |= e.IsInCategory(EventCategory::EventCategoryMouse) & io.WantCaptureKeyboard;
		}


	}


	void ImGuiLayer::OnImGuiRender()
	{
		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);*/
	}



	void ImGuiLayer::Begin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();

		// 从glfw库里获取 时间、鼠标位置、窗口和Viewport大小等参数, 赋值给ImGui::IO
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		//TEMP ??? what is it?
		//ImGuizmo::BeginFrame();

		//創建視口停靠  important？yes!!
		ImGui::DockSpaceOverViewport();

	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

	}

	/*
	* 用于获取当前激活的小部件（widget）的 ID。
	* 首先，它使用全局变量 GImGui 获取当前的 ImGui 上下文。
	* 然后，通过访问上下文的 ActiveId 属性，获取当前处于激活状态的小部件的 ID，
	* 并将其作为无符号整数返回。
	* 通常情况下，小部件 ID 是由 ImGui 自动生成的。
	* 当用户与某个小部件进行交互时，该小部件会被标记为“活跃”（active），
	* 并且在 ImGui 的输入输出对象中记录下该小部件的 ID。
	* 在需要处理该小部件的输入事件时，ImGui 会根据该 ID 来唯一地识别该小部件，并执行相应的操作。
	* 因此，通过获取当前激活的小部件的 ID，可以确定当前正在与哪个小部件进行交互。
	*
	*/
	unsigned int ImGuiLayer::GetActiveWidgetID() const
	{
		return GImGui->ActiveId;
	}


	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}




}
