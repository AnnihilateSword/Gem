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
		GEM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// ������¼�����ʱ���д���ĺ���Ϊ OnEvent�����簴��������������ڵ��¼���
		m_Window->SetEventCallback(GEM_BIND_EVENT_FN(Application::OnEvent));

		// ImGui
		m_ImGuiLayer = new ImGuiLayer();
		// ��β������
		PushOverlay(m_ImGuiLayer);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();  // Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// ��Ⱦ���㽫��ǰ�����¼��㽫�Ӻ�ǰ
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			// ImGui (has show demo window)
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GEM_BIND_EVENT_FN(Application::OnWindowClose));

		// ��Ⱦ���㽫��ǰ�����¼��㽫�Ӻ�ǰ
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}