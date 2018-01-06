#include "stdafx.h"
#include "Render/Material.h"

Material::Material()
{

}

Material::~Material()
{

}

const std::vector<Material::TextureInfo>& Material::GetTextures() const
{
	return textures;
}

void Material::AddTexture(const std::shared_ptr<Texture>& texture, Render::EFilterMode filterMode, Render::EAddressMode addressMode)
{
	textures.push_back({ texture, filterMode, addressMode });
}

void Material::ChangeTexture(uint8_t idx, const std::shared_ptr<Texture>& texture)
{
	if(idx >= textures.size())
	{
		return;
	}

	textures[idx].texture = texture;
}
