#pragma once

#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

namespace Atlas {

	struct Material {
		glm::vec3 ambient, diffuse, specular;
		float shininess;

		Material()
			: ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f), shininess(32)
		{

		}

		Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin)
			: ambient(amb), diffuse(diff), specular(spec), shininess(shin)
		{

		}
	};

	class Object : public Mesh {
	private:
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
		Material material;
		bool glInitialized;
		std::string textureDirectory;
		std::string textureName;
		std::string shaderDirectory;
		std::string shaderName;
		bool hasLighting;
	public:
		Object();
		Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting);
		Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat);
		virtual ~Object();

		void GLInit();
		void Draw();
		void Bind();
		void Unbind();
		unsigned int GetNumIndices();
		void SetShader(GLuint id);
		void SetShader(std::string dir, std::string name);
		void SetTexture(GLuint tex);
		void SetTexture(std::string dir, std::string name);
		void SetMaterial(Material mat);
		GLuint GetShaderID();
		GLuint GetTextureID();
		std::string GetTextureDirectory();
		std::string GetTextureName();
		std::string GetShaderDirectory();
		std::string GetShaderName();
		Material GetMaterial();
		bool GetGLInitialized();
		bool GetHasLighting();
		void SetHasLighting(bool newValue);

		virtual std::string GetType() override;

		static void FlushCache();
	};
}