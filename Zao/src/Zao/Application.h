#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Zao/Window.h"


namespace Zao {

	class ZAO_API Application
	{
	public:
		Application();
		virtual ~Application() {}

		void run();
	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

		void OnEvent(Event& e);
	};

	//在客户端中定义 to be define in client
	Application* CreateApplication();

}
