#pragma once
#include "../Core.h"

namespace Cubes {

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		static Ref<Texture> Create(const std::string& texturePath);

	private:

		static Ref<Texture> SelectAPIAndCreate(const std::string& texturePath);

	};

}
