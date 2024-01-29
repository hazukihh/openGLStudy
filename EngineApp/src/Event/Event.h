

#ifndef  _EVENT_H
#define  _EVENT_H




#include <iostream>
#include <functional>
#define BIT(x) 1<<x


namespace Engine
{

	// �¼�����ϸ����
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// �¼��Ĵ�������
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
		bool m_Handled = false;//�����������¼��Ƿ񱻴�����
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

	// logger(e)  ����ֱ�Ӵ�ӡ���¼�������
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}



#define ENGI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn( std::forward<decltype(args)>(args)...);}


	class  EventDispatcher
	{
	private:
		Event& m_Event;//���������ã���������Event��ʵ������ΪEvent���д��麯��

	public:
		EventDispatcher(Event& e)
			:m_Event(e) {}

		// Dispatch��ֱ��ִ����Ӧ�¼���Ӧ�ĺ���ָ���Ӧ�ĺ���
		// Tָ�����¼�����, ������������û��GetStaticType�ᱨ��
		template<typename T, typename F>
		bool Dispatch(const F& Func)
		{
			/*if (m_Event.m_Handled)
				return false;*/

				// ֻ��Event���͸�ģ��Tƥ��ʱ, ����Ӧ�¼� 
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//TEMP??   "=" vs "|="
				//m_Event.m_Handled = Func(*(T*)&m_Event); 

				m_Event.GetHandled() |= Func(static_cast<T&>(m_Event));

				return true;//�ɹ��ַ�
			}
			return false;
		}


	};

}

#endif // _EVENT_H