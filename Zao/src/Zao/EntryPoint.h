#pragma once


#ifdef ZAO_PLATFORM_WINDOWS

extern Zao::Application* Zao::CreateApplication();

int main(int argc, char* argv[]) {
	printf("fuck");
	auto app = Zao::CreateApplication();
	app->run();
	delete app;
}


#endif // ZAO_PLATFORM_WINDOWS


