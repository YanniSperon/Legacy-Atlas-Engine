#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"

namespace Engine {

	Object::Object()
		: Mesh(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0), shaderID(0), material(), glInitialized(false), hasLighting(true)
	{

	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, GLuint tex, GLuint shader, bool glInit, bool lighting)
		: Mesh(minCorner, maxCorner, type, dir, name), shaderID(0), texID(0), material(), glInitialized(false), vertexBufferID(0), indexBufferID(0), hasLighting(lighting)
	{
		texID = tex;
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, bool glInit, bool lighting)
		: Mesh(minCorner, maxCorner, type, dir, name, rot, trans, s), shaderID(shader), texID(0), material(), glInitialized(false), vertexBufferID(0), indexBufferID(0), hasLighting(lighting)
	{
		texID = tex;
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, Material mat, bool glInit, bool lighting)
		: Mesh(minCorner, maxCorner, type, dir, name, rot, trans, s), shaderID(shader), texID(0), material(mat), glInitialized(false), vertexBufferID(0), indexBufferID(0), hasLighting(lighting)
	{
		texID = tex;
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	Object::~Object()
	{
		if (glInitialized) {
			Unbind();
			glDeleteBuffers(1, &vertexBufferID);
			glDeleteBuffers(1, &indexBufferID);
		}
	}

	void Object::GLInit()
	{
		glInitialized = true;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));


		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

		//GetShape().cleanUp();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glFinish();
	}

	void Object::Draw()
	{
		Bind();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void Object::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void Object::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int Object::GetNumIndices()
	{
		return numIndices;
	}

	void Object::SetShader(GLuint id)
	{
		shaderID = id;
	}

	void Object::SetTexture(GLuint tex)
	{
		texID = tex;
	}

	void Object::SetMaterial(Material mat)
	{
		material = mat;
	}

	void Object::SetLighting(bool newValue)
	{
		hasLighting = newValue;
	}

	GLuint Object::GetShaderID()
	{
		return shaderID;
	}

	GLuint Object::GetTextureID()
	{
		return texID;
	}

	Material Object::GetMaterial()
	{
		return material;
	}

	bool Object::GetHasLighting()
	{
		return hasLighting;
	}

	bool Object::GetGLInitialized()
	{
		return glInitialized;
	}

	std::string Object::GetType()
	{
		return "Object";
	}
}