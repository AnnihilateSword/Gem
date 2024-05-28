#include <Gem.h>

class ExampleLayer : public Gem::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GEM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Gem::Event& e) override
	{
		GEM_TRACE("ExamplaeLayer::Event:: {0}", e.ToString());
	}
};

class Sandbox : public Gem::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Gem::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}