

#ifndef  _EVENT_H
#define  _EVENT_H




#include <iostream>
#include <functional>
#define BIT(x) 1<<x


namespace Engine
{

	// 事件的详细类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// 事件的粗略种类
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }



	class Event
	{
	protected:
		bool m_Handled = false;//用来标记这个事件是否被处理了
	public:
		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool IsHandled() const { return m_Handled; }

		bool& GetHandled() { return m_Handled; }


	};

	// logger(e)  可以直接打印出事件的名字
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}



#define ENGI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn( std::forward<decltype(args)>(args)...);}


	class  EventDispatcher
	{
	private:
		Event& m_Event;//必须是引用，不可以是Event的实例，因为Event带有纯虚函数

	public:
		EventDispatcher(Event& e)
			:m_Event(e) {}

		// Dispatch会直接执行响应事件对应的函数指针对应的函数
		// T指的是事件类型, 如果输入的类型没有GetStaticType会报错
		template<typename T, typename F>
		bool Dispatch(const F& Func)
		{
			/*if (m_Event.m_Handled)
				return false;*/

				// 只有Event类型跟模板T匹配时, 才响应事件 
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//TEMP??   "=" vs "|="
				//m_Event.m_Handled = Func(*(T*)&m_Event); 

				m_Event.GetHandled() |= Func(static_cast<T&>(m_Event));

				return true;//成功分发
			}
			return false;
		}


	};

}

#endif // _EVENT_H