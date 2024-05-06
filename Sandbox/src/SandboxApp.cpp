#include "Zao.h"

class Sandbox : public Zao::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

Zao::Application* Zao::CreateApplication() {
	return new Sandbox;
}
