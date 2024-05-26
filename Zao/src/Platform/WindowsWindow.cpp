#include "zpch.h"
#include "WindowsWindow.h"

#include "Zao/Event/ApplicationEvent.h"
#include "Zao/Event/Event.h"
#include "Zao/Event/KeyEvent.h"
#include "Zao/Event/MouseEvent.h"

namespace Zao {
	static bool s_GLFWInitialized = false;//static variable is only initialized once

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		ShutdownWindow();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ZAO_CORE_INFO("start to create glfw window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			ZAO_CORE_ASSERT(success, "failed to initialize glfw");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);

		glfwMakeContextCurrent(m_Window); //设置当前线程的上下文为m_Window
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		// Set GLFW callbacks
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			ZAO_CORE_INFO("close window {0}", data->Title);

			WindowCloseEvent e;

			data->EventCallback(e);
		});

	}

	void WindowsWindow::ShutdownWindow() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.Vsync = enabled;
	}

}