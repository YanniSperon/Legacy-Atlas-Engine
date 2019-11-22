#pragma once

#include <GL/glew.h>
#include "Vertex.h"

namespace Engine {

	struct ShapeData
	{
		ShapeData() :
			vertices(0), numVertices(0), indices(0), numIndices(0) {}
		Vertex* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;

		GLsizeiptr vertexBufferSize() const {
			return numVertices * sizeof(Vertex);
		}
		GLsizeiptr indexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}


		void cleanUp() {
			delete[] vertices;
			delete[] indices;

			numVertices = numIndices = 0;
		}
	};

	struct ShapeData2D
	{
		ShapeData2D() :
			vertices(0), numVertices(0), indices(0), numIndices(0) {}
		Vertex2D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;

		GLsizeiptr vertexBufferSize() const {
			return numVertices * sizeof(Vertex2D);
		}
		GLsizeiptr indexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}


		void cleanUp() {
			delete[] vertices;
			delete[] indices;

			numVertices = numIndices = 0;
		}
	};

	struct TexCoord {
		float u, v;
	};
}