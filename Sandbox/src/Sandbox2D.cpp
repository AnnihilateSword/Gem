#include "Sandbox2D.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Gem::Texture2D::Create("assets/textures/Checkerboard.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Gem::Timestep ts)
{
	GEM_PROFILE_FUNCTION();

	// Update
	{
		GEM_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		GEM_PROFILE_SCOPE("Renderer Prep");
		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Gem::RenderCommand::Clear();
	}

	{
		GEM_PROFILE_SCOPE("Renderer Draw");
		Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Gem::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Gem::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		// z = -0.1f (need enable depth test)
		Gem::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Gem::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	GEM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Gem::Event& e)
{
	m_CameraController.OnEvent(e);
}