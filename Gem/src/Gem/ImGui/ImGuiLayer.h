#pragma once

#include "Gem/Layer.h"

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
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		ImGuiContext* GetImGuiContext();

	private:
		float m_Time = 0.0f;
	};

}