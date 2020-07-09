#pragma once
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#define BIT(x) (1 << x)

namespace Events
{
	/*
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MousButtonPressed, MouseButtonRelease, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	*/

	
	class IEvent
	{
	public:
		virtual const std::string& GetName() const = 0;
	};

	template <typename ..._args>
	class Event : public IEvent
	{
	public:
		using _callback = std::function<void(_args...)>;
	private:
		std::string m_Name;
		_callback const m_cbFunction;
	public:
		explicit Event(const std::string& name, const _callback& cb)
			: m_Name(name), m_cbFunction(cb) {}
		~Event() {}

		void Trigger(_args... a) { m_cbFunction(a...); }

		inline const std::string& GetName() const override { return m_Name; }
	};

	class CallBackEventDispatcher
	{
	private:
		std::unordered_map<std::string, std::vector<IEvent*>> m_EventList;
	public:
		CallBackEventDispatcher() {}
		~CallBackEventDispatcher()
		{
			for (auto el : m_EventList)
			{
				for (auto e : el.second)
					delete e;
			}
		}
		
		void RegisterEvent(IEvent* event)
		{
			if (event)
				m_EventList[event->GetName()].push_back(event);
		}

		template<typename ..._args>
		void DispatchEvent(const std::string& eventName, _args... a)
		{
			auto el = m_EventList.find(eventName);
			if (el == m_EventList.end())
				return;
			for (auto e : el->second)
			{
				if (Event<_args...>* event = dynamic_cast<Event<_args...>*>(e))
					event->Trigger(a...);
			}
		}
	};
}