#include "TextureLoader.h"

TextureLoader::TextureLoader(std::string path)
 : texturePath(std::move(path))
{
}

Texture*
TextureLoader::getTexture(const std::string& name, GLubyte alpha)
{
	auto it = textures.find(name);

	if (it == textures.end()) { // si no existe, carga la textura
		auto texture = std::make_unique<Texture>();
		texture->load(texturePath + name, alpha);
		it = textures.insert({name, std::move(texture)}).first;
	}

	return it->second.get();
}