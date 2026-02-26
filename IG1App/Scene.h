#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"
#include "Texture.h"

#include <vector>

//#pragma pack(push, 1) // Disable padding
//struct BMPFileHeader {
//	uint16_t bfType = 0x4D42; // 'BM' (BMP signature)
//	uint32_t bfSize; // Total file size
//	uint16_t bfReserved1 = 0;
//	uint16_t bfReserved2 = 0;
//	uint32_t bfOffBits = 54; // Offset to pixel data (14 + 40 = 54 bytes)
//};
//
//struct BMPInfoHeader {
//	uint32_t biSize = 40; // Size of this header
//	int32_t biWidth;
//	int32_t biHeight;
//	uint16_t biPlanes = 1;
//	uint16_t biBitCount = 24; // 24 bits per pixel (RGB)
//	uint32_t biCompression = 0; // No compression
//	uint32_t biSizeImage; // Size of pixel data (with padding)
//	int32_t biXPelsPerMeter = 0;
//	int32_t biYPelsPerMeter = 0;
//	uint32_t biClrUsed = 0;
//	uint32_t biClrImportant = 0;
//};
//#pragma pack(pop)

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	void render(Camera const& cam) const;
	virtual void update();

	// load or unload scene data into the GPU
	void load();
	void unload();

	void saveImage();

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
};

#endif //_H_Scene_H_
