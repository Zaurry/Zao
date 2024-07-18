#pragma once

#include "Core.h"
#include "Zao/Event/Event.h"

namespace Zao {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Zao Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class ZAO_API Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		using EventCallbackFn = std::function<void(Event&)>; //回调函数，用于传递和处理窗口事件

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//窗口属性
		virtual void SetEventCallbackFn(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual	bool IsVSync() const = 0;

	public:
		//应该由每个特定于平台的窗口类实现
		//使用static因为我们想要创建一个窗口而不需要窗口类的实例
		static Window* Create(const WindowProps& props = WindowProps());
	};


}