#pragma once
#include "Core.h"

#include "Window.h"
#include "Gem/LayerStack.h"
#include "Gem/Events/ApplicationEvent.h"

namespace Gem
{
	class GEM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// 在客户端中定义
	Application* CreateApplication();
}