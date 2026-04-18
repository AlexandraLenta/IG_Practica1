#include "IndexMesh.h"
#include <limits>
#include <iostream>

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = std::numeric_limits<GLuint>::max();

IndexMesh::IndexMesh() :Mesh(), mIBO(NONE) {

}

void IndexMesh::draw() const{
	glDrawElements(
		mPrimitive, // primitiva (GL_TRIANGLES, etc.)
		vIndexes.size(), // número de índices
		GL_UNSIGNED_INT, // tipo de los índices
		nullptr // offset en el VBO de índices
	);
}

void IndexMesh::load() {
	Mesh::load(); 
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		vIndexes.size() * sizeof(GLuint),
		vIndexes.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
 }

void IndexMesh::unload() {

	Mesh::unload();
	if (mIBO != NONE) {
		glDeleteBuffers(1, &mIBO);
		mIBO = NONE;
	}
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples,GLfloat angleMax) {

	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);

	// Genera los vértices de las muestras
	GLdouble theta1 = 2 * std::numbers::pi / nSamples;
	for (int i = 0; i < nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (auto p : profile) // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}

	for (auto p : profile) {
		std::cout << p.x << ' ' << p.y << '\n';
	}

	for (int i = 0; i < nSamples; ++i) // caras i a i + 1 
	{
		int nextI = (i + 1) % nSamples;
		for (int j = 0; j < tamPerfil; ++j) {
			int nextJ = (j + 1) % tamPerfil;

			if (profile[j].x != 0.0)
				for (auto [s, t] : { std::pair{i, j}, {nextI, j}, {i, nextJ} })
					mesh->vIndexes.push_back(s * tamPerfil + t);

			if (profile[nextJ].x != 0.0)
				for (auto [s, t] : { std::pair{i, nextJ}, {nextI, j}, {nextI, nextJ} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}


	mesh->mNumVertices = mesh->vVertices.size();
	
	mesh->buildNormalVectors();
	
	return mesh;
}

void IndexMesh::buildNormalVectors() {

	vNormals.resize(vVertices.size(), glm::vec3(0.0f));

	for (int i = 0; i < vIndexes.size(); i += 3)
	{
		// indices de los 3 vert del triangulo
		GLuint i0 = vIndexes[i];
		GLuint i1 = vIndexes[i + 1];
		GLuint i2 = vIndexes[i + 2];

		// vertices del triangulo
		glm::vec3 p0 = vVertices[i0];
		glm::vec3 p1 = vVertices[i1];
		glm::vec3 p2 = vVertices[i2];

		// calcular la normal del triangulo usando producto vectorial
		glm::vec3 edge1 = p1 - p0;
		glm::vec3 edge2 = p2 - p0;
		glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

		// sumar la normal a cada vert del tri
		vNormals[i0] += faceNormal;
		vNormals[i1] += faceNormal;
		vNormals[i2] += faceNormal;
	}
	// normalizar  las normales finales
	for (auto& n : vNormals)
	{
		n = glm::normalize(n);
	}

}

IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l) {

	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 8;

	GLdouble length = l / 2;

	mesh->vVertices = {
		{ length,  length, -length}, {length, -length, -length}, {length,  length, length}, {length, -length, length},
		{-length,  length,  length}, {-length, -length,  length}, { -length,  length, -length}, { -length, -length, -length}
	};

	mesh->vIndexes = {
		0, 2, 1, 2, 3, 1,
		2, 4, 3, 4, 5, 3,
		4, 6, 5, 6, 7, 5,
		6, 0, 7, 0, 1, 7,
		4, 2, 6, 2, 0, 6,
		1, 3, 7, 3, 5, 7
	};

	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* 
IndexMesh::generateIndexedBox(GLdouble l) {
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 24;

	GLdouble length = l / 2;

	mesh->vVertices = {
		// +X
		{ length,  length, -length}, { length, -length, -length}, { length,  length,  length}, { length, -length,  length},
		// -X
		{-length,  length,  length}, {-length, -length,  length}, {-length,  length, -length}, {-length, -length, -length},
		// +Y
		{ length,  length,  length}, {-length,  length,  length}, { length,  length, -length}, {-length,  length, -length},
		// -Y
		{ length, -length, -length}, {-length, -length, -length}, { length, -length,  length}, {-length, -length,  length},
		// +Z
		{ length,  length,  length}, { length, -length,  length}, {-length,  length,  length}, {-length, -length,  length},
		// -Z
		{ length,  length, -length}, { length, -length, -length}, {-length,  length, -length}, {-length, -length, -length},
	};

	mesh->vIndexes = {
		// +X (derecha)
		0, 2, 1,
		2, 3, 1,
		// -X (izquierda)
		4, 6, 5,
		6, 7, 5,
		// +Y (arriba)
		8, 10, 9,
		10, 11, 9,
		// -Y (abajo)
		12, 14, 13,
		14, 15, 13,
		// +Z (frente)
		16, 18, 17,
		18, 19, 17,
		// -Z (atrás)
		20, 22, 21,
		22, 23, 21
	};

	mesh->buildNormalVectors();
	return mesh;
}