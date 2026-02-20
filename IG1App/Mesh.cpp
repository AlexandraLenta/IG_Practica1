#include "Mesh.h"
#include<iostream>

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}

		if (vTextureCords.size() > 0) {
			glGenBuffers(1, &mTBO);

			glBindBuffer(GL_ARRAY_BUFFER, mTBO);
			glBufferData(GL_ARRAY_BUFFER,vTextureCords.size() * sizeof(vec2),vTextureCords.data(),GL_STATIC_DRAW);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}
		if (mTBO != NONE) {
			glDeleteBuffers(1, &mTBO);
			mTBO = NONE;
		}
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();

}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* 
Mesh::generateRegularPolygon(GLuint num, GLdouble r) {
	// Calculate necessary angles in radians
	float angleToSum = 360.0 / (float)(num);
	float angleInRadians = radians(angleToSum);
	float currentAngle = radians(90.0);

	// Create mesh
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;

	// Set vertices
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Create vertices
	for (int i = 0; i < num; i++) {
		float x = r * cos(currentAngle);
		float y = r * sin(currentAngle);

		mesh->vVertices.emplace_back(x, y, 0.0);

		currentAngle += angleInRadians;
	}

	return mesh;
}

Mesh*
Mesh::generateRGBTriangle(GLdouble r) {
	Mesh* mesh = generateRegularPolygon(3, r);

	// Cambiar primitiva para poder rellenar la figura
	mesh->mPrimitive = GL_TRIANGLES;

	// Poner colores
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh*
Mesh::generateRectangle(GLdouble w, GLdouble h) {
	// Create mesh
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	// Set vertices
	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble x = w / 2;
	GLdouble y = h / 2;

	// Create vertices
	mesh->vVertices.emplace_back(x, -y, 0.0);
	mesh->vVertices.emplace_back(-x, -y, 0.0);
	mesh->vVertices.emplace_back(x, y, 0.0);
	mesh->vVertices.emplace_back(-x, y, 0.0);

	return mesh;
}

Mesh*
Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {
	// Create mesh
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	return mesh;
}

Mesh*
Mesh::generateCube(GLdouble length)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;

	length /= 2;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Top face
	mesh->vVertices.emplace_back(length, length, -length);
	mesh->vVertices.emplace_back(-length, length, -length);
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(length, length, -length);
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(length, length, length);


	// Bottom face
	mesh->vVertices.emplace_back(length, -length, length);
	mesh->vVertices.emplace_back(-length, -length, length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(length, -length, length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(length, -length, -length);

	// Front face
	mesh->vVertices.emplace_back(length, length, length);
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(-length, -length, length);
	mesh->vVertices.emplace_back(length, length, length);
	mesh->vVertices.emplace_back(-length, -length, length);
	mesh->vVertices.emplace_back(length, -length, length);

	// Back face
	mesh->vVertices.emplace_back(length, -length, -length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(-length, length, -length);
	mesh->vVertices.emplace_back(length, -length, -length);
	mesh->vVertices.emplace_back(-length, length, -length);
	mesh->vVertices.emplace_back(length, length, -length);

	// Left face
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(-length, length, -length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(-length, -length, length);

	// Right face
	mesh->vVertices.emplace_back(length, length, -length);
	mesh->vVertices.emplace_back(length, length, length);
	mesh->vVertices.emplace_back(length, -length, length);
	mesh->vVertices.emplace_back(length, length, -length);
	mesh->vVertices.emplace_back(length, -length, length);
	mesh->vVertices.emplace_back(length, -length, -length);

	return mesh;
}

Mesh*
Mesh::generateRGBCubeTriangles(GLdouble length) {
	Mesh* mesh = generateCube(length);

	mesh->vColors.reserve(mesh->mNumVertices);

	// Top face -> blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	// Bottom Face -> blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	// Front face -> red
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	// Back face -> red
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	// Left face -> green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	// Right face -> green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	return mesh;
}

Mesh*
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {

	Mesh* mesh = generateRectangle(w, h);
	mesh->vTextureCords.reserve(mesh->mNumVertices);

	mesh->vTextureCords.emplace_back(rw, 0);
	mesh->vTextureCords.emplace_back(0, 0);
	mesh->vTextureCords.emplace_back(rw, rh);
	mesh->vTextureCords.emplace_back(0, rh);

	return mesh;
}

Mesh* 
Mesh::generateBoxOutline(GLdouble length) {
	Mesh* mesh = new Mesh(); 
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 10;

	length /= 2;

	mesh->vVertices.emplace_back(-length, -length, length);
	mesh->vVertices.emplace_back(length, -length, length);
	mesh->vVertices.emplace_back(length, length, length);
	mesh->vVertices.emplace_back(length, -length, -length);
	mesh->vVertices.emplace_back(length, length, -length);
	mesh->vVertices.emplace_back(-length, -length, -length);
	mesh->vVertices.emplace_back(-length, length, -length);
	mesh->vVertices.emplace_back(-length, -length, length);
	mesh->vVertices.emplace_back(-length, length, length);
	mesh->vVertices.emplace_back(length, length, length);

	return mesh;
}

Mesh*
Mesh::generateBoxOutlineTexCor(GLdouble length) {
	Mesh* mesh = generateBoxOutline(length);

	mesh->vTextureCords.reserve(mesh->mNumVertices);

	mesh->vTextureCords.emplace_back(0, 0);
	mesh->vTextureCords.emplace_back(1, 0);
	
	mesh->vTextureCords.emplace_back(1, 1);

	mesh->vTextureCords.emplace_back(0, 0);
	mesh->vTextureCords.emplace_back(0, 1);

	mesh->vTextureCords.emplace_back(1, 0);
	mesh->vTextureCords.emplace_back(1, 1);

	mesh->vTextureCords.emplace_back(0, 0);
	mesh->vTextureCords.emplace_back(0, 1);

	mesh->vTextureCords.emplace_back(1, 1);

	return mesh;
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = new Mesh();

	// puntas * 2 (radio mayor y radio menor) + 1 (origen) + 1 (conexión con la primera punta)
	mesh->mNumVertices = np * 2 + 2;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->mPrimitive = GL_TRIANGLE_FAN;

	// origen
	mesh->vVertices.emplace_back(0, 0, 0);

	// calcular angulos
	float angleToSum = 360.0 / (float)(np) / 2.0;
	float angleInRadians = radians(angleToSum);
	float currentAngle = radians(90.0);

	// crear vértices
	for (int i = 0; i < np; i++) {
		float x = re * cos(currentAngle);
		float y = re * sin(currentAngle);

		// punta de radio mayor
		mesh->vVertices.emplace_back(x, y, h);

		currentAngle += angleInRadians;

		x = re / 2.0 * cos(currentAngle);
		y = re / 2.0 * sin(currentAngle);

		// punta de radio menor
		mesh->vVertices.emplace_back(x, y, h);

		currentAngle += angleInRadians;
	}


	float x = re * cos(radians(90.0));
	float y = re * sin(radians(90.0));

	// punta en el mismo lugar que la primera para conectar la figura
	mesh->vVertices.emplace_back(x, y, h);

	return mesh;
}

Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->vTextureCords.reserve(mesh->mNumVertices);

	// el centro en el origen
	mesh->vTextureCords.emplace_back(0.5, 0.5);
	
	mesh->vTextureCords.emplace_back(0, 0);
	mesh->vTextureCords.emplace_back(0, 0.25);
	mesh->vTextureCords.emplace_back(0, 0.5);
	mesh->vTextureCords.emplace_back(0, 0.75);
	mesh->vTextureCords.emplace_back(0, 1);

	mesh->vTextureCords.emplace_back(0.25, 1);
	mesh->vTextureCords.emplace_back(0.5, 1);
	mesh->vTextureCords.emplace_back(0.75, 1);
	mesh->vTextureCords.emplace_back(1, 1);

	mesh->vTextureCords.emplace_back(1, 0.75);
	mesh->vTextureCords.emplace_back(1, 0.5);
	mesh->vTextureCords.emplace_back(1, 0.25);
	mesh->vTextureCords.emplace_back(1, 0);

	mesh->vTextureCords.emplace_back(0.75, 0);
	mesh->vTextureCords.emplace_back(0.5, 0);
	mesh->vTextureCords.emplace_back(0.25, 0);

	return mesh;
}
