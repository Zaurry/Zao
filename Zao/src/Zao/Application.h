#pragma once
#include "Core.h"
#include <iostream>

namespace Zao {

	class ZAO_API Application
	{
	public:
		Application() {}
		virtual ~Application() {}

		void run();
	};

	//�ڿͻ����ж��� to be define in client
	Application* CreateApplication();

}
