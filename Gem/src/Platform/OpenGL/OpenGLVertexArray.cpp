#include "gempch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Gem
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Gem::ShaderDataType::Float:    return GL_FLOAT;
		case Gem::ShaderDataType::Float2:   return GL_FLOAT;
		case Gem::ShaderDataType::Float3:   return GL_FLOAT;
		case Gem::ShaderDataType::Float4:   return GL_FLOAT;
		case Gem::ShaderDataType::Mat3:     return GL_FLOAT;
		case Gem::ShaderDataType::Mat4:     return GL_FLOAT;
		case Gem::ShaderDataType::Int:      return GL_INT;
		case Gem::ShaderDataType::Int2:     return GL_INT;
		case Gem::ShaderDataType::Int3:     return GL_INT;
		case Gem::ShaderDataType::Int4:     return GL_INT;
		case Gem::ShaderDataType::Bool:     return GL_BOOL;
		}

		GEM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		GEM_PROFILE_FUNCTION();

		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GEM_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		GEM_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		GEM_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	//
	// 这个函数还不完善，比如尝试将多个 VBO 绑定到 VAO，只会绘制最后一个绑定的 VBO，那么这个 m_VertexBuffers 就没意义了
	//
	void OpenGLVertexArray::AddVertexBuffer(const Gem::Ref<VertexBuffer>& vertexBuffer)
	{
		GEM_PROFILE_FUNCTION();

		GEM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		unsigned int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Gem::Ref<IndexBuffer>& indexBuffer)
	{
		GEM_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}