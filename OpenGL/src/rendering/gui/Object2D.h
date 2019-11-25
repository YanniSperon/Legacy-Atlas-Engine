#pragma once

#include "Mesh2D.h"

namespace Atlas {
	class Object2D : public Mesh2D {
	private:
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
	public:
		Object2D();
		Object2D(glm::vec2 minCorner, glm::vec2 maxCorner, float rot, glm::vec2 trans, glm::vec2 s, GLuint tex, GLuint shader, glm::vec2 minTexCoord, glm::vec2 maxTexCoord);
		~Object2D();


		void Draw();
		void Bind();
		void Unbind();
		unsigned int GetNumIndices();
		void SetShader(GLuint id);
		void SetTexture(GLuint tex);
		GLuint GetShaderID();
		GLuint GetTextureID();

		virtual std::string GetType() override;
	};
}