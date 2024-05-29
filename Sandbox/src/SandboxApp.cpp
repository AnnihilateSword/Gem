#include <Gem.h>

#include "imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
	}

	~Sandbox()
	{

	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}