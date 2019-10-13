#pragma once
#include <GL/glew.h>
#include "Vertex.h"

struct ShapeData
{
	ShapeData() :
		vertices(0), numVertices(0), indices(0), numIndices(0), texCoords(0), numTexCoords(0) {}
	Vertex* vertices;
	GLuint numVertices;
	GLuint* indices;
	GLuint numIndices;
	GLfloat* texCoords;
	GLuint numTexCoords;

	GLsizeiptr vertexBufferSize() const {
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const {
		return numIndices * sizeof(GLuint);
	}


	void cleanUp() {
		delete[] vertices;
		delete[] indices;
		delete[] texCoords;

		numVertices = numIndices = numTexCoords = 0;
	}
};

struct ShapeData2D
{
	ShapeData2D() :
		vertices(0), numVertices(0), indices(0), numIndices(0), texCoords(0), numTexCoords(0) {}
	Vertex2D* vertices;
	GLuint numVertices;
	GLuint* indices;
	GLuint numIndices;
	GLfloat* texCoords;
	GLuint numTexCoords;

	GLsizeiptr vertexBufferSize() const {
		return numVertices * sizeof(Vertex2D);
	}
	GLsizeiptr indexBufferSize() const {
		return numIndices * sizeof(GLuint);
	}


	void cleanUp() {
		delete[] vertices;
		delete[] indices;
		delete[] texCoords;

		numVertices = numIndices = numTexCoords = 0;
	}
};

struct TexCoord {
	float u, v;
};