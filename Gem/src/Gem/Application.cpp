#include "gempch.h"
#include "Application.h"

#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Gem/Renderer/Renderer.h"

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
		: m_Camera(-3.2f, 3.2f, -1.8f, 1.8f)
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

		// vertexArray (triangle) -------------------------------------------------------
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// vertexbuffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// indexbuffer
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// vertex Array (square) --------------------------------------------------------
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		// vertexbuffer
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		// indexbuffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader Source code --------------------------
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			// Draw Object --------------------------
			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(30.0f);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_BlueShader, m_SquareVA);
			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

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