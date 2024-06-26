#pragma once

#include <string>

#include "Gem/Core/Core.h"

namespace Gem
{
	class GEM_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetData(void* data, unsigned int size) = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
	};

	class GEM_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}