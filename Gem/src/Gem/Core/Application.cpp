#include "gempch.h"
#include "Application.h"

#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Gem/Renderer/Renderer.h"

namespace Gem
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GEM_PROFILE_FUNCTION();

		GEM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// 这里绑定事件发生时进行处理的函数为 OnEvent（比如按键，鼠标点击，窗口等事件）
		m_Window->SetEventCallback(GEM_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		// ImGui (has show demo window)
		m_ImGuiLayer = new ImGuiLayer();
		// 在尾部插入
		PushOverlay(m_ImGuiLayer);
	}

	void Application::Run()
	{
		GEM_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = (float)glfwGetTime();  // Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				GEM_PROFILE_SCOPE("Laystack OnUpdate");

				// 渲染器层将从前到后，事件层将从后到前
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			// ImGui
			m_ImGuiLayer->Begin();
			{
				GEM_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		GEM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GEM_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GEM_BIND_EVENT_FN(Application::OnWindowResize));

		// 渲染器层将从前到后，事件层将从后到前
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		GEM_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		GEM_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GEM_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}