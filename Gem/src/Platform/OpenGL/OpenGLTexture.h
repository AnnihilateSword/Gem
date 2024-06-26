#pragma once

#include "Gem/Renderer/Texture.h"

namespace Gem
{
	class GEM_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned int slot = 0) const override;
	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
		unsigned int m_InternalFormat, m_DataFormat;
	};

}