#pragma once

#include "Engine/Core/MemoryBuffer.h"

class Texture
{
public:
	enum EFormat
	{
		UNKNOWN,

		R8,
		RG8,
		RGB8,
		RGBA8,

		RGBA32F,

		// Depth buffer formats
		D24S8
	};

	Texture(uint16_t width, uint16_t height, EFormat format, uint8_t numMipMaps = 0);
	~Texture();

	bool IsDepthFormat() const;

	// Render engine specific data set at bind
	void *renderData = nullptr;

	const uint16_t width;
	const uint16_t height;
	const EFormat format;
	const uint8_t numMipMaps;

	MemoryBuffer data;
};
