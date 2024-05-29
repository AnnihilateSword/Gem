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
		if (Gem::Input::IsKeyPressed(GEM_KEY_TAB))
			GEM_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Gem::Event& e) override
	{
		if (e.GetEventType() == Gem::EventType::KeyPressed)
		{
			Gem::KeyPressedEvent& event = (Gem::KeyPressedEvent&)e;
			if (event.GetKeyCode() == GEM_KEY_TAB)
				GEM_TRACE("Tab key is pressed (event)!");
			GEM_TRACE("{0}", (char)event.GetKeyCode());
		}
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