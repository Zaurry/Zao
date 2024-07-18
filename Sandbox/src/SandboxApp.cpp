#include "Zao.h"

// class exampleLayer : public Zao::Layer {
// public:
// 	exampleLayer()
// 		:Layer() {}
// 
// 	~exampleLayer() {}
// 
// 	void OnEvent(Zao::Event& event) override {
// 		ZAO_TRACE(event.ToString());
// 	}
// 
// 	void OnUpdate() override {
// 		ZAO_INFO("example layer update");
// 	}
// };

class Sandbox : public Zao::Application
{
public:
	Sandbox();
	~Sandbox();
};

Sandbox::Sandbox()
{
	PushLayer(new Zao::ImGuiLayer());
}

Sandbox::~Sandbox()
{
}

Zao::Application* Zao::CreateApplication() {
	return new Sandbox;
}

