#pragma once

#include <memory>
#include <vector>
#include "Gem/Renderer/Buffer.h"

namespace Gem
{
	class GEM_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Gem::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Gem::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Gem::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Gem::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

}