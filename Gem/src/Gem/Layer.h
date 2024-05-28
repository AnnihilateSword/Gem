#pragma once

#include "Gem/Core.h"
#include "Gem/Events/Event.h"

namespace Gem
{

	class GEM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		// ֻ�ڵ���ģʽ��ʹ��
		std::string m_DebugName;
	};

}