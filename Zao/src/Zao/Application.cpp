#include "zpch.h"
#include "Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Zao {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		ZAO_CORE_ASSERT(s_Instance == nullptr, "Already has Application!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallbackFn(BIND_EVENT_FN(OnEvent));
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//�¼��Զ����´��ݸ�layer
		for (auto it = m_LayerStack.End(); it != m_LayerStack.Begin();) {
			(*--it)->OnEvent(event);
			if (event.Handled) {
				break;
			}
		}
	}

	void Application::run() {
		while (m_Running) {
			//�����ɫ������ �Ա���һ֡����
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//����layer
			for (auto it = m_LayerStack.Begin(); it != m_LayerStack.End(); it++) {
				(*it)->OnUpdate();
			}

			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer) {
		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}
}