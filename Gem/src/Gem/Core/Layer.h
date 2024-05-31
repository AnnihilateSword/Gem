#pragma once

#include "Gem/Core/Core.h"
#include "Gem/Events/Event.h"
#include "Gem/Core/Timestep.h"

namespace Gem
{

	class GEM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		// 只在调试模式下使用
		std::string m_DebugName;
	};

}