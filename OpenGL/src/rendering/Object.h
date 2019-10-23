#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

struct Material {
	glm::vec3 ambient, diffuse, specular;
	float shininess;

	Material()
		: ambient(0.1f, 0.1f, 0.1f), diffuse(0.25f, 0.25f, 0.25f), specular(0.25f, 0.25f, 0.25f), shininess(32)
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
public:
	Object();
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, GLuint tex, GLuint shader, bool glInit);
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, bool glInit);
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, Material mat, bool glInit);
	virtual ~Object();

	void GLInit();
	void Draw();
	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	void SetShader(GLuint id);
	void SetTexture(GLuint tex);
	void SetMaterial(Material mat);
	GLuint GetShaderID();
	GLuint GetTextureID();
	Material GetMaterial();

	virtual std::string GetType() override;
};