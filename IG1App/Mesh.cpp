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
Mesh::generateRegularPolygon(GLuint num, GLdouble r, GLdouble posX, GLdouble posY) {
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

		mesh->vVertices.emplace_back(x + posX, y + posY, 0.0);

		currentAngle += angleInRadians;
	}

	return mesh;
}

Mesh*
Mesh::generateRGBTriangle(GLdouble r, GLdouble posX, GLdouble posY) {
	Mesh* mesh = generateRegularPolygon(3, r, posX, posY);
	mesh->mPrimitive = GL_TRIANGLES;

	// Set vertices
	mesh->mNumVertices = 3;
	mesh->vVertices.reserve(mesh->mNumVertices);

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
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	// Set vertices
	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

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
Mesh::generateCube(GLdouble length)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;

	GLdouble l = length / 2.0;

	glm::vec3 v0(-l, -l, l);
	glm::vec3 v1(l, -l, l);
	glm::vec3 v2(l, l, l);
	glm::vec3 v3(-l, l, l);
	glm::vec3 v4(-l, -l, -l);
	glm::vec3 v5(l, -l, -l);
	glm::vec3 v6(l, l, -l);
	glm::vec3 v7(-l, l, -l);

	mesh->vVertices = {v0, v1, v2,  v0, v2, v3,//delante
		v1, v5, v6,  v1, v6, v2,//der
		v5, v4, v7,  v5, v7, v6,//detras
		v4, v0, v3,  v4, v3, v7,//izq
		v3, v2, v6,  v3, v6, v7,//top
		v4, v5, v1,  v4, v1, v0 //abajp
	};

	mesh->mNumVertices = static_cast<GLuint>(mesh->vVertices.size());

	return mesh;
}
