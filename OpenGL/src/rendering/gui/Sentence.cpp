#include "Sentence.h"
#include "Vertex.h"
#include "glm/gtc/matrix_transform.hpp"

//Sentence::Sentence(Shader& shdr, Font& f, std::string t, float s, glm::vec2 pos, glm::vec3 col)
//	: shader(shdr), font(f), text(t), scale(s), position(pos), color(col)
//{
//
//}

int GetUniformLocationw(const std::string& name, GLuint shaderID)
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	if (location == -1)
		printf("Warning: uniform '%s' doesn't exist!\n", name.c_str());
	return location;
}

void UseProgramw(GLuint program) {
	glUseProgram(program);
}

void SetUniformMat4fw(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
{
	glUniformMatrix4fv(GetUniformLocationw(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
}

void SetUniformVec3w(const std::string& name, const glm::vec3& vector, GLuint shaderID)
{
	glUniform3fv(GetUniformLocationw(name, shaderID), 1, &vector[0]);
}

void SetUniform1fw(const std::string& name, const float& value, GLuint shaderID)
{
	glUniform1f(GetUniformLocationw(name, shaderID), value);
}

Sentence::Sentence(Font& f, std::string t, float s, glm::vec2 pos, glm::vec3 col, GLuint shader)
	: font(f), text(t), scale(s), position(pos), color(col), shaderID(shader)
{
	GenerateVBOs(t);
}

Sentence::~Sentence()
{
	DeleteVBOs();
}

//Shader& Sentence::GetShader()
//{
//	return shader;
//}
//
//void Sentence::SetShader(Shader& shdr)
//{
//	shader = shdr;
//}

Font& Sentence::GetFont()
{
	return font;
}

void Sentence::SetFont(Font& f)
{
	font = f;
}

std::string Sentence::GetText()
{
	return text;
}

void Sentence::SetText(std::string newText)
{
	text = newText;
	DeleteVBOs();
	GenerateVBOs(newText);
}

float Sentence::GetScale()
{
	return scale;
}

void Sentence::SetScale(float s)
{
	scale = s;
}

glm::vec2 Sentence::GetPosition()
{
	return position;
}

void Sentence::SetPosition(glm::vec2 newPos)
{
	position = newPos;
}

glm::vec3 Sentence::GetColor()
{
	return color;
}

void Sentence::SetColor(glm::vec3 newColor)
{
	color = newColor;
}

glm::mat4 Sentence::GetModelTransformMatrix()
{
	return (glm::translate(glm::mat4(), glm::vec3(position, 0.0f)));
}

void Sentence::GenerateVBOs(std::string text)
{
	int x = 0;
	int y = 0;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = font.GetGlyphs()[*c];

		GLfloat xpos = x + ch.Bearing.x;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y);

		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;

		Vertex2D vertices[] = {
			glm::vec2(xpos, ypos + h),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(xpos, ypos),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(xpos + w, ypos),
			glm::vec2(1.0f, 1.0f),

			glm::vec2(xpos, ypos + h),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(xpos + w, ypos),
			glm::vec2(1.0f, 1.0f),

			glm::vec2(xpos + w, ypos + h),
			glm::vec2(1.0f, 0.0f)
		};

		GLuint tempVBO;
		glGenBuffers(1, &tempVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

		x += (ch.Advance >> 6);

		VBOs.push_back(CharInSentence(ch.TextureID, tempVBO));
	}

	bool notSorted = true;
	while (notSorted) {
		notSorted = false;
		for (unsigned int i = 0; i < VBOs.size() - 1; i++) {
			if (VBOs[i].textureID > VBOs[i + 1].textureID) {
				CharInSentence temp(VBOs[i]);
				VBOs[i] = VBOs[i + 1];
				VBOs[i + 1] = temp;
				notSorted = true;
			}
		}
	}

	printf("-----------------------------------\n");
	printf("Text: %s\n", text.c_str());
	for (unsigned int i = 0; i < VBOs.size(); i++) {
		printf("Texture at index %i: %i\n", i, VBOs[i].textureID);
	}

	glFinish();
}

void Sentence::DeleteVBOs()
{
	for (unsigned int i = 0; i < VBOs.size(); i++) {
		glDeleteBuffers(1, &VBOs[i].VBO);
	}
	VBOs.clear();
}

void Sentence::Draw(glm::mat4 proj)
{
	unsigned int pastShader = 0;
	for (unsigned int i = 0; i < VBOs.size(); i++) {
		if (pastShader != shaderID) {
			pastShader = shaderID;
			UseProgramw(pastShader);
			SetUniformMat4fw("P", proj, pastShader);
			SetUniformVec3w("textColor", color, pastShader);
		}
		
		SetUniformMat4fw("M", GetModelTransformMatrix(), pastShader);
		//std::string P = "P";
		//int Pvalue = glGetUniformLocation(pastShader, P.c_str());
		//if (Pvalue == -1)
		//	printf("Invalid Uniform P\n");
		//glUniformMatrix4fv(Pvalue, 1, GL_FALSE, &proj[0][0]);
		//
		//std::string M = "M";
		//int MValue = glGetUniformLocation(pastShader, M.c_str());
		//if (MValue == -1)
		//	printf("Invalid Uniform M\n");
		//glUniformMatrix4fv(MValue, 1, GL_FALSE, &GetModelTransformMatrix()[0][0]);
		//
		//std::string C = "textColor";
		//int CValue = glGetUniformLocation(pastShader, C.c_str());
		//if (MValue == -1)
		//	printf("Invalid Uniform C\n");
		//glUniform3fv(CValue, 1, &color[0]);

		glBindTexture(GL_TEXTURE_2D, VBOs[i].textureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i].VBO);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
