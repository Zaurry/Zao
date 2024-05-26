#pragma once


#include "Event.h"

namespace Zao {
	class ZAO_API KeyEvent : public Event {
	public:
		int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(const int keycode) : m_KeyCode(keycode) {} //protected 的构造函数使得只能创建其子类对象
		int m_KeyCode;
	};

	class ZAO_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const int keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		bool m_IsRepeat; 
	};

	class ZAO_API KeyReleaseEvent : public KeyEvent {
	public:

		KeyReleaseEvent(const int keycode) 
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleaseEvent : " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class ZAO_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(const int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};


}


