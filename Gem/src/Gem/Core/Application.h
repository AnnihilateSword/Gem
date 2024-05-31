#pragma once
#include "Core.h"

#include "Window.h"
#include "Gem/Events/ApplicationEvent.h"

#include "Gem/Core/LayerStack.h"
#include "Gem/ImGui/ImGuiLayer.h"

namespace Gem
{
	class GEM_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		float m_LastFrameTime{ 0.0f };
	private:
		static Application* s_Instance;
	};

	// 在客户端中定义
	Application* CreateApplication();
}