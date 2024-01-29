#pragma once
#include "Layer.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Engine
{
	class ImGuiLayer : public Layer
	{
	private:
		//�ж��Ƿ�Ҫ�����¼�, block: �谭��ֹ
		//true = ImGui ��Ҫ��ֹ�¼��������ݸ�����ϵͳ��
		bool m_BlockEvents = true;

		/*TEMP
		bool m_ViewportFocused;
		bool m_ViewportHovered;*/

	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		// OnUpdate() -> Begin(); End();
		void Begin();
		void End();

		virtual void OnImGuiRender() override;

		void BlockEvents(bool block) { m_BlockEvents = block; }

		unsigned int GetActiveWidgetID() const;

		void SetDarkThemeColors();

		/*TEMP
		void SetViewportFocusedStatus(bool b) { m_ViewportFocused = b; }
		void SetViewportHoveredStatus(bool b) { m_ViewportHovered = b; }*/


	};


	class ImGLayer :public Layer
	{

	};



}


