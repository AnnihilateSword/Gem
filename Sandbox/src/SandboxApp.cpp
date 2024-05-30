#include <Gem.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Gem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f)
	{
		// vertexArray (triangle) -------------------------------------------------------
		m_VertexArray.reset(Gem::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// vertexbuffer
		std::shared_ptr<Gem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gem::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// indexbuffer
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Gem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gem::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// vertex Array (square) --------------------------------------------------------
		m_SquareVA.reset(Gem::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		// vertexbuffer
		std::shared_ptr<Gem::VertexBuffer> squareVB;
		squareVB.reset(Gem::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		// indexbuffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Gem::IndexBuffer> squareIB;
		squareIB.reset(Gem::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader Source code --------------------------
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_Shader.reset(Gem::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;		

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Gem::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(Gem::Timestep ts) override
	{
		GEM_INFO("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		// camera
		if (Gem::Input::IsKeyPressed(GEM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Gem::Input::IsKeyPressed(GEM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Gem::Input::IsKeyPressed(GEM_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Gem::Input::IsKeyPressed(GEM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		// Render
		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Gem::RenderCommand::Clear();

		// Draw Object --------------------------
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Gem::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Gem::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Gem::Renderer::Submit(m_Shader, m_VertexArray);

		Gem::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Gem::Event& e) override
	{
	}

private:
	std::shared_ptr<Gem::Shader> m_Shader;
	std::shared_ptr<Gem::VertexArray> m_VertexArray;

	std::shared_ptr<Gem::Shader> m_FlatColorShader;
	std::shared_ptr<Gem::VertexArray> m_SquareVA;

	Gem::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition{ 0.0f, 0.0f, 0.0f };
	float m_CameraRotation{ 0.0f };
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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