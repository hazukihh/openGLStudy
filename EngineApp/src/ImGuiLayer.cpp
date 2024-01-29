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
		// 1. ����ImGui Contex
		ImGui::CreateContext();

		// 2. IO��ص�Flag����, Ŀǰ����������롢����Dokcing��������Viewport
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		//ͣ��춱���
		//io.ConfigFlags |= ImGuiCol_DockingEmptyBg; 




		// ����fonts
		//float fontSize = 18.0f;// *2.0f;
		//io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
		//io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);



		// 3. ����������ɫ
		ImGui::StyleColorsDark();
		//SetDarkThemeColors();

		// 4. ���ô���Style�ͱ�����ɫ��͸����
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;// WindowRounding�����ڽ����ֵ, ����Ϊ0.0�����Ǿ��δ���
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;// ���ڱ���͸����
		}

		//SetDarkThemeColors();		

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// 5. glfw,OpenGL��صĳ�ʼ��
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

		/*�ж��Ƿ�Ҫ�����¼�, block: �谭��ֹ
		* true = ImGui ��Ҫ��ֹ�¼��������ݸ�����ϵͳ
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

		// ��glfw�����ȡ ʱ�䡢���λ�á����ں�Viewport��С�Ȳ���, ��ֵ��ImGui::IO
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		//TEMP ??? what is it?
		//ImGuizmo::BeginFrame();

		//����ҕ��ͣ��  important��yes!!
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
	* ���ڻ�ȡ��ǰ�����С������widget���� ID��
	* ���ȣ���ʹ��ȫ�ֱ��� GImGui ��ȡ��ǰ�� ImGui �����ġ�
	* Ȼ��ͨ�����������ĵ� ActiveId ���ԣ���ȡ��ǰ���ڼ���״̬��С������ ID��
	* ��������Ϊ�޷����������ء�
	* ͨ������£�С���� ID ���� ImGui �Զ����ɵġ�
	* ���û���ĳ��С�������н���ʱ����С�����ᱻ���Ϊ����Ծ����active����
	* ������ ImGui ��������������м�¼�¸�С������ ID��
	* ����Ҫ�����С�����������¼�ʱ��ImGui ����ݸ� ID ��Ψһ��ʶ���С��������ִ����Ӧ�Ĳ�����
	* ��ˣ�ͨ����ȡ��ǰ�����С������ ID������ȷ����ǰ�������ĸ�С�������н�����
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
