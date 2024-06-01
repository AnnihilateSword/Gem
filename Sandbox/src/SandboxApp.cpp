#include <Gem/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Gem::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}