#include "Loader.h"
#include "System.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image/stb_image.h"

namespace Atlas {

	GLuint Loader::LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter)
	{
		GLuint texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		stbi_set_flip_vertically_on_load(1);

		int width, height, nrChannels;
		std::string texDirAndNameAbsolute = System::ConvertFilePathToAbsolute(texDirAndName);
		unsigned char* data = stbi_load(texDirAndNameAbsolute.c_str(), &width, &height, &nrChannels, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMaxFilter);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			System::Log("Failed to load texture \"" + texDirAndName + "\"!");
		}
		return texID;
	}
	GLuint Loader::LoadTexture(const std::string& texDir, const std::string& texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter)
	{
		GLuint texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		stbi_set_flip_vertically_on_load(1);

		int width, height, nrChannels;
		std::string str = System::ConvertFilePathToAbsolute(texDir + texName);
		unsigned char* data = stbi_load(str.c_str(), &width, &height, &nrChannels, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMaxFilter);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			System::Log("Failed to load texture \"" + texDir + texName + "\"!");
		}
		return texID;
	}
	
	TexCoords Loader::GetTextureCoordinates(GLuint minX, GLuint minY, GLuint maxX, GLuint maxY, GLuint width, GLuint height)
	{
		TexCoords tex;
		tex.min = glm::vec2(((float)minX / (float)width), ((float)minY / (float)height));
		tex.max = glm::vec2(((float)maxX / (float)width), ((float)maxY / (float)height));
		return tex;
	}
}