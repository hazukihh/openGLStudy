#pragma once
#include <iostream>
#include "Timestep.h"
#include "Event/Event.h"


/*
�������������һ��Ϊ������������


ex��Base* base = new Derived();
(1)��������������������virtual�ؼ���
�����������������������������������ʱ�򣬣���������̳и��࣬�����ָ��ָ������ʱ��delete�������ָ�룬ֻ����������������������������������������������
(2)������������������virtual�ؼ���
���������������������������������ʱ�򣬵�����̳и��࣬�����ָ��ָ������ʱ��delete�������ָ�룬!!�ȵ�������������������ٵ������������������!!

*/

namespace Engine
{
	class Layer
	{
	protected:

		std::string m_DebugName;
		//TEMP
		// ֵΪfasleʱ����Layer�ᱻ���ã�������ƻ��棬Ҳ��������¼�
		bool isEnabled;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {} //Attach ����, ��layer��ӵ�layer stack��ʱ�����ô˺���
		virtual void OnDetach() {}//Detach ����, ��layer��layer stack�Ƴ���ʱ�����ô˺���
		virtual void OnUpdate(const Timestep&) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		const std::string& GetName() const { return m_DebugName; }

		//temp...
		// ��̬����Imgui��Ⱦ
		//virtual void OnImGuiRender(void (*render)()) {};


	};

}

