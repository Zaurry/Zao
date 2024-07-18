#pragma once
/*
当前这个版本的Event实现是阻塞式的，即处理一个事件时，会等待执行完再进行后面的任务。
*/

#include "Zao/Core.h"

namespace Zao {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory //use mask to store multiple categories
	{
		None = 0,
		EventCategoryApplication  = BIT(0),
		EventCategoryInput        = BIT(1),
		EventCategoryKeyboard     = BIT(2),
		EventCategoryMouse        = BIT(3),
		EventCategoryMouseButton  = BIT(4)
	};

	//用一个宏，把子类中需要重复写的代码封装起来了。
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;} \
                                virtual EventType GetEventType() const override {return GetStaticType();} \
                                virtual const char* GetName() const override {return #type;}

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}


	class ZAO_API Event {
		friend class EventDispatcher; //friend 可以让EventDispatcher访问Event的私有成员,但这里没什么鸟用
	public:
		virtual ~Event() = default;

		bool Handled = false; //when event handled, turn true
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {  //报错：如果不写<T>,编译器无法推断类型
			if (m_event.GetEventType() == T::GetStaticType()) {
				m_event.Handled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}