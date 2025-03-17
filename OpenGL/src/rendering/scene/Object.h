#pragma once

#include "Mesh.h"
#include "UUID.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

namespace Atlas {

	struct Material {
		glm::vec3 ambient, diffuse, specular;
		int shininess;

		Material()
			: ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f), shininess(32)
		{

		}

		Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, int shin)
			: ambient(amb), diffuse(diff), specular(spec), shininess(shin)
		{

		}
	};

	class Object : public Mesh {
	protected:
		UUID uid;
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
		std::string displayName;

	public:
		Object();
		Object(type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, const UUID& uid);
		Object(type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		Object(type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat);
		Object(type t, std::string meshDir, std::string meshName, Object& objToCopy);
		virtual ~Object();

		void GLInit();
		void Draw();
		void Bind();
		void Unbind();
		void SetShader(GLuint id);
		void SetShader(std::string dir, std::string name);
		void SetTexture(GLuint tex);
		void SetTexture(std::string dir, std::string name);
		void SetMaterial(Material mat);
		void SetHasLighting(bool newValue);

		unsigned int GetNumIndices();
		GLuint GetShaderID();
		GLuint GetTextureID();
		std::string GetTextureDirectory();
		std::string GetTextureName();
		std::string GetShaderDirectory();
		std::string GetShaderName();
		bool GetGLInitialized();
		bool GetHasLighting();
		Material& GetMaterial();
		const Material& GetMaterial() const;
		GLuint GetVBO();
		GLuint GetIBO();

		const UUID& GetUID() const;

		virtual std::string GetType() override;

		static void FlushCache();

		virtual std::string ToString() override;

		const std::string& GetDisplayName() const;
		void SetDisplayName(const std::string& newDisplayName);
	};
}