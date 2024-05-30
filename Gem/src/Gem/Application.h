#pragma once
#include "Core.h"

#include "Window.h"
#include "Gem/Events/ApplicationEvent.h"

#include "Gem/LayerStack.h"
#include "Gem/ImGui/ImGuiLayer.h"
#include "Gem/Renderer/Shader.h"

#include "Gem/Renderer/Buffer.h"
#include "Gem/Renderer/VertexArray.h"

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

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	// 在客户端中定义
	Application* CreateApplication();
}