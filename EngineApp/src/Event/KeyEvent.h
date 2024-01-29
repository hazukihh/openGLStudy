
#ifndef  _KEY_EVENT_H
#define  _KEY_EVENT_H



#include "Event.h"
#include <sstream>

namespace Engine
{
	class KeyEvent : public Event
	{
	public:

		inline int GetKeyCode() { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)


	protected:
		int m_KeyCode;
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}


	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		bool m_IsRepeat;

	public:
		KeyPressedEvent(const int KeyCode, bool isRepeat = false)
			:KeyEvent(KeyCode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};



}

#endif // _KEY_EVENT_H