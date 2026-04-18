#include "IndexMesh.h"
#include <limits>


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
	GLdouble theta1 = angleMax / nSamples;

	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (auto p : profile) // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}

	for (int i = 0; i < nSamples; ++i) // caras i a i + 1
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0) // triángulo inferior
				for (auto [s, t] : { std::pair{i, j}, {i + 1, j}, {i, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // triángulo superior
				for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j}, {i + 1, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
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
		0, 1, 2, 2, 1, 3, 
		2, 3, 4, 4, 3, 5,
		4, 5, 6, 6, 5, 7, 
		6, 7, 0, 0, 7, 1, 
		4, 6, 2, 2, 6, 0,
		1, 7, 3, 3, 7, 5
	};
	mesh->buildNormalVectors();
	return mesh;
}

