#ifndef _APPLICATION_EVENT_H
#define _APPLICATION_EVENT_H

#include "Event.h"
#include <sstream>

namespace Engine
{

	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width, m_Height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int  height)
			:m_Width(width), m_Height(height) {}
		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



}

#endif //_APPLICATION_EVENT_H