#include <Gem.h>
#include <Gem/Core/EntryPoint.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Gem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Gem::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Gem::Ref<Gem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gem::VertexBuffer::Create(vertices, sizeof(vertices)));
		Gem::BufferLayout layout = {
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Gem::Ref<Gem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gem::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Gem::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Gem::Ref<Gem::VertexBuffer> squareVB;
		squareVB.reset(Gem::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Gem::Ref<Gem::IndexBuffer> squareIB;
		squareIB.reset(Gem::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
		m_SquareVA->SetIndexBuffer(squareIB);

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
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Gem::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

		m_FlatColorShader = Gem::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Gem::Texture2D::Create("assets/textures/Checkerboard.png");
		m_AwesomefaceTexture = Gem::Texture2D::Create("assets/textures/awesomeface.png");

		std::dynamic_pointer_cast<Gem::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Gem::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Gem::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Gem::RenderCommand::Clear();

		Gem::Renderer::BeginScene(m_CameraController.GetCamera());

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

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Gem::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_AwesomefaceTexture->Bind();
		Gem::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Gem::Renderer::Submit(m_Shader, m_VertexArray);

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
		m_CameraController.OnEvent(e);
	}
private:
	Gem::ShaderLibrary m_ShaderLibrary;
	Gem::Ref<Gem::Shader> m_Shader;
	Gem::Ref<Gem::VertexArray> m_VertexArray;

	Gem::Ref<Gem::Shader> m_FlatColorShader;
	Gem::Ref<Gem::VertexArray> m_SquareVA;

	Gem::Ref<Gem::Texture2D> m_Texture, m_AwesomefaceTexture;

	Gem::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Gem::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}