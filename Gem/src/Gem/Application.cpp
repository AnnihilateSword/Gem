#include "gempch.h"
#include "Application.h"

#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Gem
{
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Gem::ShaderDataType::Float:    return GL_FLOAT;
		case Gem::ShaderDataType::Float2:   return GL_FLOAT;
		case Gem::ShaderDataType::Float3:   return GL_FLOAT;
		case Gem::ShaderDataType::Float4:   return GL_FLOAT;
		case Gem::ShaderDataType::Mat3:     return GL_FLOAT;
		case Gem::ShaderDataType::Mat4:     return GL_FLOAT;
		case Gem::ShaderDataType::Int:      return GL_INT;
		case Gem::ShaderDataType::Int2:     return GL_INT;
		case Gem::ShaderDataType::Int3:     return GL_INT;
		case Gem::ShaderDataType::Int4:     return GL_INT;
		case Gem::ShaderDataType::Bool:     return GL_BOOL;
		}

		GEM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		GEM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// 这里绑定事件发生时进行处理的函数为 OnEvent（比如按键，鼠标点击，窗口等事件）
		m_Window->SetEventCallback(GEM_BIND_EVENT_FN(Application::OnEvent));

		// ImGui
		m_ImGuiLayer = new ImGuiLayer();
		// 在尾部插入
		PushOverlay(m_ImGuiLayer);

		// vertexArray
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// vertexbuffer
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		unsigned int index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
			index++;
		}

		// indexbuffer
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		glBindVertexArray(0);

		// Shader Source code
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Use Shader
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_Shader->Unbind();

			// 渲染器层将从前到后，事件层将从后到前
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// ImGui
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

		// 渲染器层将从前到后，事件层将从后到前
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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}