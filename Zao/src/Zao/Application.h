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

	//�ڿͻ����ж��� to be define in client
	Application* CreateApplication();

}
