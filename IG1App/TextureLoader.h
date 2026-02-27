#ifndef _H_TextureLoader_H_
#define _H_TextureLoader_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "Texture.h"

class TextureLoader
{
public:
	TextureLoader(std::string path = "../assets/images/");

	Texture* getTexture(const std::string& name, GLubyte alpha = 255);

protected:
	std::string texturePath;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};

#endif _H_TextureLoader_H_
