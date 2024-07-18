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

		using EventCallbackFn = std::function<void(Event&)>; //�ص����������ڴ��ݺʹ������¼�

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//��������
		virtual void SetEventCallbackFn(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual	bool IsVSync() const = 0;

	public:
		//Ӧ����ÿ���ض���ƽ̨�Ĵ�����ʵ��
		//ʹ��static��Ϊ������Ҫ����һ�����ڶ�����Ҫ�������ʵ��
		static Window* Create(const WindowProps& props = WindowProps());
	};


}