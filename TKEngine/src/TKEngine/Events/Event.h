#pragma once

#include "spdlog/details/fmt_helper.h"
#include "../Core.h"
#include "spdlog/fmt/ostr.h" // must be included
#include "spdlog/sinks/stdout_sinks.h"

namespace TK
{

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick, AppUpdate,AppRender,KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication		= BIT(0),
		EventCategoryInput				= BIT(1),
		EventCategoryKeyboard			= BIT(2),
		EventCategoryMouse				= BIT(3),
		EventCategoryMouseButton		= BIT(4)
	};

	//宏定义（文本替换）自动化以下的重写操作---------------------------------------------------
#define EVENT_CLASS_TYPE(type) \
			static EventType GetStaticType(){ return EventType::##type; }\
			virtual EventType GetEventType() const override { return GetStaticType(); }\
			virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)\
			virtual int GetCategoryFlags() const override { return category; }

	class TK_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}
		~EventDispatcher()
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	

}

template <typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<TK::Event, T>, char>> :
	fmt::formatter<std::string> {
	auto format(const TK::Event& event, format_context& ctx) const {
		return formatter<std::string>::format(event.ToString(), ctx);
	}
};