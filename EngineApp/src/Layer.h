#pragma once
#include <iostream>
#include "Timestep.h"
#include "Event/Event.h"


/*
基类的析构函数一定为虚析构函数：


ex：Base* base = new Derived();
(1)如果父类的析构函数不加virtual关键字
当父类的析构函数不声明成虚析构函数的时候，！！当子类继承父类，父类的指针指向子类时，delete掉父类的指针，只调动父类的析构函数，而不调动子类的析构函数。！！
(2)如果父类的析构函数加virtual关键字
当父类的析构函数声明成虚析构函数的时候，当子类继承父类，父类的指针指向子类时，delete掉父类的指针，!!先调动子类的析构函数，再调动父类的析构函数。!!

*/

namespace Engine
{
	class Layer
	{
	protected:

		std::string m_DebugName;
		//TEMP
		// 值为fasle时，该Layer会被禁用，不会绘制画面，也不会接收事件
		bool isEnabled;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {} //Attach 附加, 当layer添加到layer stack的时候会调用此函数
		virtual void OnDetach() {}//Detach 分离, 当layer从layer stack移除的时候会调用此函数
		virtual void OnUpdate(const Timestep&) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		const std::string& GetName() const { return m_DebugName; }

		//temp...
		// 动态创建Imgui渲染
		//virtual void OnImGuiRender(void (*render)()) {};


	};

}

