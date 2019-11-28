#include "Object.h"
#include "GLFW/glfw3.h"
#include "Global.h"
#include "Loader.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"

namespace Atlas {

	Object::Object()
		: Mesh(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0), shaderID(0), material(), glInitialized(false), textureDirectory(""), textureName(""), hasLighting(false)
	{

	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting)
		: Mesh(minCorner, maxCorner, type, meshDir, meshName), material(), glInitialized(glInit), textureDirectory(texDir), textureName(texName), hasLighting(lighting)
	{
		if (Global::Variables.textureCache.find(meshDir + meshName) != Global::Variables.textureCache.end()) {
			texID = Global::Variables.textureCache[meshDir + meshName];
		}
		else {
			Global::Variables.textureCache[meshDir + meshName] = Loader::LoadTexture(texDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = Global::Variables.textureCache[meshDir + meshName];
		}

		if (Global::Variables.shaderCache.find(shaderDir + shaderFileName) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			Global::Variables.shaderCache[shaderDir + shaderFileName] = new Shader(shaderDir + shaderFileName);
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: Mesh(minCorner, maxCorner, type, meshDir, meshName, rot, trans, s), material(), glInitialized(glInit), textureDirectory(texDir), textureName(texName), shaderDirectory(shaderDir), shaderName(shaderFileName), hasLighting(lighting)
	{
		if (Global::Variables.textureCache.find(meshDir + meshName) != Global::Variables.textureCache.end()) {
			texID = Global::Variables.textureCache[meshDir + meshName];
		}
		else {
			Global::Variables.textureCache[meshDir + meshName] = Loader::LoadTexture(texDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = Global::Variables.textureCache[meshDir + meshName];
		}

		if (Global::Variables.shaderCache.find(shaderDir + shaderFileName) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			Global::Variables.shaderCache[shaderDir + shaderFileName] = new Shader(shaderDir + shaderFileName);
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat)
		: Mesh(minCorner, maxCorner, type, meshDir, meshName, rot, trans, s), material(mat), glInitialized(glInit), textureDirectory(texDir), textureName(texName), shaderDirectory(shaderDir), shaderName(shaderFileName), hasLighting(lighting)
	{
		if (Global::Variables.textureCache.find(meshDir + meshName) != Global::Variables.textureCache.end()) {
			texID = Global::Variables.textureCache[meshDir + meshName];
		}
		else {
			Global::Variables.textureCache[meshDir + meshName] = Loader::LoadTexture(texDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = Global::Variables.textureCache[meshDir + meshName];
		}

		if (Global::Variables.shaderCache.find(shaderDir + shaderFileName) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			Global::Variables.shaderCache[shaderDir + shaderFileName] = new Shader(shaderDir + shaderFileName);
			shaderID = Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
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

	GLuint Object::GetShaderID()
	{
		return shaderID;
	}

	GLuint Object::GetTextureID()
	{
		return texID;
	}

	std::string Object::GetTextureDirectory()
	{
		return textureDirectory;
	}

	std::string Object::GetTextureName()
	{
		return textureName;
	}

	std::string Object::GetShaderDirectory()
	{
		return shaderDirectory;
	}

	std::string Object::GetShaderName()
	{
		return shaderName;
	}

	Material Object::GetMaterial()
	{
		return material;
	}

	bool Object::GetGLInitialized()
	{
		return glInitialized;
	}

	bool Object::GetHasLighting()
	{
		return hasLighting;
	}

	void Object::SetHasLighting(bool newValue)
	{
		hasLighting = newValue;
	}

	std::string Object::GetType()
	{
		return "Object";
	}
}