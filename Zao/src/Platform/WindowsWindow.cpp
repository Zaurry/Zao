#include "zpch.h"
#include "WindowsWindow.h"

#include "glad/glad.h"

#include "Zao/Event/ApplicationEvent.h"
#include "Zao/Event/Event.h"
#include "Zao/Event/KeyEvent.h"
#include "Zao/Event/MouseEvent.h"

namespace Zao {
	static bool s_GLFWInitialized = false;//static 好像没起什么作用

	static void GLFWErrorCallback(int error_code, const char* description) { 
		ZAO_CORE_ERRER("GLFW ERROR ({0}):{1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);

		glfwMakeContextCurrent(m_Window); //设置当前线程的上下文为m_Window
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			ZAO_CORE_ERRER("Failed to initialize GLAD");
			return;
		}
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		/*********************Set GLFW callbacks***********************/
		glfwSetErrorCallback(GLFWErrorCallback);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data->EventCallback(e);
			});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent e(key, false);
				data->EventCallback(e);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				data->EventCallback(e);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent e(key, true);
				data->EventCallback(e);
				break;
			}
			}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e(keycode);
			data->EventCallback(e);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent e((float)xoffset, (float)yoffset);
			data->EventCallback(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;
			WindowResizeEvent e(width, height);
			data->EventCallback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent e(button);
				data->EventCallback(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent e(button);
				data->EventCallback(e);
				break;
			}
			}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)xpos, (float)ypos);
			data->EventCallback(e);
			});

	}

	void WindowsWindow::Shutdown() {
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