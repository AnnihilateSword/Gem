#pragma once
#include "Core.h"

#include "Window.h"
#include "Gem/LayerStack.h"
#include "Gem/Events/ApplicationEvent.h"

#include "Gem/ImGui/ImGuiLayer.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		// 获取 ImGui 当前上下文
		inline static ImGuiContext* GetImGuiContext() { return s_ImGuiLayer->GetImGuiContext(); }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		static ImGuiLayer* s_ImGuiLayer;
	};

	// 在客户端中定义
	Application* CreateApplication();
}