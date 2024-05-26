#pragma once

#include "Zao/Window.h"
#include "GLFW/glfw3.h"

namespace Zao {


	class ZAO_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallbackFn(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		inline bool IsVSync() const override { return m_Data.Vsync; }
	private:
		void Init(const WindowProps& props);
		void ShutdownWindow();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data; //∞Û∂®µΩGLFWwindow…œ

	};


}