#pragma once

#include "Gem/Renderer/VertexArray.h"

namespace Gem
{

	class GEM_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Gem::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Gem::Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Gem::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Gem::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		unsigned int m_RendererID;  // VAO
		std::vector<Gem::Ref<VertexBuffer>> m_VertexBuffers;
		Gem::Ref<IndexBuffer> m_IndexBuffer;
	};

}