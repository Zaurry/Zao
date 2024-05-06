#pragma once
#include "Core.h"

namespace Zao {

	class ZAO_API Application
	{
	public:
		Application() {}
		virtual ~Application() {}

		void run();
	};

	//在客户端中定义 to be define in client
	Application* CreateApplication();

}
