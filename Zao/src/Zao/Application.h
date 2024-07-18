#pragma once
#include "Core.h"

#include "Zao/Event/Event.h"
#include "Zao/Event/ApplicationEvent.h"

#include "Zao/Window.h"

#include "Zao/Layer.h"
#include "Zao/LayerStack.h"

namespace Zao {


	class ZAO_API Application {

	public:
		Application();
		virtual ~Application() {}

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		void run();

		inline static inline Application& Get() { return *s_Instance; }
		inline  Window& GetWindow() { return *m_Window; }
	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
		void OnEvent(Event& e);
	private:
		static Application* s_Instance;
	};

	//在客户端中定义 to be define in client
	Application* CreateApplication();

}
