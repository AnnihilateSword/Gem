#include "Sandbox2D.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Gem::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	// vertex buffer
	Gem::Ref<Gem::VertexBuffer> squareVB;
	squareVB.reset(Gem::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Gem::ShaderDataType::Float3, "a_Position" }
		});
	// vao add vbo
	m_SquareVA->AddVertexBuffer(squareVB);

	// index buffer
	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Gem::Ref<Gem::IndexBuffer> squareIB;
	squareIB.reset(Gem::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
	// vao add ibo
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Gem::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Gem::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Gem::RenderCommand::Clear();

	Gem::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Gem::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Gem::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Gem::Event& e)
{
	m_CameraController.OnEvent(e);
}