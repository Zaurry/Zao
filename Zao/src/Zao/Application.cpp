#include "zpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

namespace Zao {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallbackFn(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::OnEvent(Event& e) {
		if (e.GetEventType() == EventType::WindowClose) {
			m_Window->~Window();
		}
	}

	void Application::run() {

		while (m_Running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}