#pragma once

#include "Gem/Core/Layer.h"

#include "Gem/Events/ApplicationEvent.h"
#include "Gem/Events/KeyEvent.h"
#include "Gem/Events/MouseEvent.h"

enum ImGuiKey;
struct ImGuiContext;

namespace Gem
{
	class GEM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}