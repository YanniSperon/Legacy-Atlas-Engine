#include "IO.h"
#include <iostream>
#include <fstream>

void IO::LoadFile(std::vector<Object>& vec, const std::string dir, const std::string fileName)
{
	std::ifstream f(dir + fileName);

	if (!f.is_open()) {
		printf("File: \"%s%s\" does not exist or could not be loaded.\n", dir.c_str(), fileName.c_str());
	}

	unsigned int currentObject = 0;

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.find("#") != std::string::npos || line.size() == 0) {

		}
		else if (line.find("Total Size: ") != std::string::npos) {
			std::string value = line.substr(12);
			int size = std::stoi(value);
			for (unsigned int i = 0; i < size; i++) {
				vec.push_back(Object(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", 0, 0));
			}
		}
		else if (line.find("Object: ") != std::string::npos) {
			std::string value = line.substr(8);
			currentObject = std::stoi(value);
		}
		else if (line.find("translation.x: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateX(std::stof(value));
		}
		else if (line.find("translation.y: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateY(std::stof(value));
		}
		else if (line.find("translation.z: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateZ(std::stof(value));
		}
		else if (line.find("rotation.x: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateX(std::stof(value));
		}
		else if (line.find("rotation.y: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateY(std::stof(value));
		}
		else if (line.find("rotation.z: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateZ(std::stof(value));
		}
		else if (line.find("scale.x: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleX(std::stof(value));
		}
		else if (line.find("scale.y: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleY(std::stof(value));
		}
		else if (line.find("scale.z: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleZ(std::stof(value));
		}
		else if (line.find("texture: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].SetTexture(std::stoi(value));
		}
		else if (line.find("shader: ") != std::string::npos) {
			std::string value = line.substr(8);
			vec[currentObject].SetShader(std::stoi(value));
		}
	}
}

void IO::SaveToFile(std::vector<Object>& vec, const std::string dir, const std::string fileName)
{
	printf("Saving to file: %s%s", dir.c_str(), fileName.c_str());
	std::ofstream outfile(dir + fileName);
	outfile << "Total Size: " << vec.size() << "\n\n";
	for (unsigned int i = 0; i < vec.size(); i++) {
		glm::vec3 translation = vec[i].GetTranslation();
		glm::vec3 rotation = vec[i].GetRotation();
		glm::vec3 scale = vec[i].GetScale();
		GLuint tex = vec[i].GetTextureID();
		GLuint shader = vec[i].GetShaderID();
		outfile << "Object: " << i << "\n";
		outfile << "translation.x: " << translation.x << "\n";
		outfile << "translation.y: " << translation.y << "\n";
		outfile << "translation.z: " << translation.z << "\n";
		outfile << "rotation.x: " << rotation.x << "\n";
		outfile << "rotation.y: " << rotation.y << "\n";
		outfile << "rotation.z: " << rotation.z << "\n";
		outfile << "scale.x: " << scale.x << "\n";
		outfile << "scale.y: " << scale.y << "\n";
		outfile << "scale.z: " << scale.z << "\n";
		outfile << "texture: " << tex << "\n";
		outfile << "shader: " << shader << "\n";
		outfile << "\n";
	}
	outfile.close();
}

void IO::LoadFile(std::vector<Object2D>& vec, const std::string dir, const std::string fileName)
{
	std::ifstream f(dir + fileName);

	if (!f.is_open()) {
		printf("File: \"%s%s\" does not exist or could not be loaded.\n", dir.c_str(), fileName.c_str());
	}

	glm::vec2 translation;
	glm::vec2 rotation;
	glm::vec2 scale;
	glm::vec2 texCoordMin;
	glm::vec2 texCoordMax;
	GLuint shader = 0;
	GLuint texture = 0;

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.find("#") != std::string::npos || line.size() == 0) {
		}
		else if (line.find("Object2D: ") != std::string::npos) {
		}
		else if (line.find("translation.x: ") != std::string::npos) {
			std::string value = line.substr(15);
			translation.x = std::stof(value);
		}
		else if (line.find("translation.y: ") != std::string::npos) {
			std::string value = line.substr(15);
			translation.y = std::stof(value);
		}
		else if (line.find("rotation.x: ") != std::string::npos) {
			std::string value = line.substr(12);
			rotation.x = std::stof(value);
		}
		else if (line.find("rotation.y: ") != std::string::npos) {
			std::string value = line.substr(12);
			rotation.y = std::stof(value);
		}
		else if (line.find("scale.x: ") != std::string::npos) {
			std::string value = line.substr(9);
			scale.x = std::stof(value);
		}
		else if (line.find("scale.y: ") != std::string::npos) {
			std::string value = line.substr(9);
			scale.y = std::stof(value);
		}
		else if (line.find("texture: ") != std::string::npos) {
			std::string value = line.substr(9);
			texture = std::stoi(value);
		}
		else if (line.find("textureCoordMin.x: ") != std::string::npos) {
			std::string value = line.substr(19);
			texCoordMin.x = std::stof(value);
		}
		else if (line.find("textureCoordMin.y: ") != std::string::npos) {
			std::string value = line.substr(19);
			texCoordMin.y = std::stof(value);
		}
		else if (line.find("textureCoordMax.x: ") != std::string::npos) {
			std::string value = line.substr(19);
			texCoordMax.x = std::stof(value);
		}
		else if (line.find("textureCoordMax.y: ") != std::string::npos) {
			std::string value = line.substr(19);
			texCoordMax.y = std::stof(value);
		}
		else if (line.find("shader: ") != std::string::npos) {
			std::string value = line.substr(8);
			shader = std::stoi(value);
		}
		else if (line.find("End Object2D") != std::string::npos) {
			printf("Creation object2D with:\ntranslation: (%f, %f)\nrotation: (%f, %f)\nscale: (%f, %f)\ntexture: %i\nshader: %i\ntexCoordMin: (%f, %f)\ntexCoordMax: (%f, %f)\n", translation.x, translation.y, rotation.x, rotation.y, scale.x, scale.y, texture, shader, texCoordMin.x, texCoordMin.y, texCoordMax.x, texCoordMax.y);
			vec.push_back(Object2D(glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), rotation, translation, scale, texture, shader, texCoordMin, texCoordMax));
		}
	}
}

void IO::SaveToFile(std::vector<Object2D>& vec, const std::string dir, const std::string fileName)
{
	printf("Saving to file: %s%s", dir.c_str(), fileName.c_str());
	std::ofstream outfile(dir + fileName);
	outfile << "Total Size: " << vec.size() << "\n\n";
	for (unsigned int i = 0; i < vec.size(); i++) {
		glm::vec2 translation = vec[i].GetTranslation();
		glm::vec2 rotation = vec[i].GetRotation();
		glm::vec2 scale = vec[i].GetScale();
		glm::vec2 texCoordMin = vec[i].GetMinTexCoords();
		glm::vec2 texCoordMax = vec[i].GetMaxTexCoords();
		GLuint tex = vec[i].GetTextureID();
		GLuint shader = vec[i].GetShaderID();
		outfile << "Object2D: " << i << "\n";
		outfile << "translation.x: " << translation.x << "\n";
		outfile << "translation.y: " << translation.y << "\n";
		outfile << "rotation.x: " << rotation.x << "\n";
		outfile << "rotation.y: " << rotation.y << "\n";
		outfile << "scale.x: " << scale.x << "\n";
		outfile << "scale.y: " << scale.y << "\n";
		outfile << "texture: " << tex << "\n";
		outfile << "textureCoordMin.x: " << texCoordMin.x << "\n";
		outfile << "textureCoordMin.y: " << texCoordMin.y << "\n";
		outfile << "textureCoordMax.x: " << texCoordMax.x << "\n";
		outfile << "textureCoordMax.y: " << texCoordMax.y << "\n";
		outfile << "shader: " << shader << "\n";
		outfile << "End Object2D\n";
		outfile << "\n";
	}
	outfile.close();
}

/*void IO::LoadFile(std::vector<Sentence>& vec, const std::string dir, const std::string fileName)
{
	std::ifstream f(dir + fileName);

	if (!f.is_open()) {
		printf("File: \"%s%s\" does not exist or could not be loaded.\n", dir.c_str(), fileName.c_str());
	}

	unsigned int currentObject = 0;

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.find("#") != std::string::npos || line.size() == 0) {

		}
		else if (line.find("Total Size: ") != std::string::npos) {
			std::string value = line.substr(12);
			int size = std::stoi(value);
			for (unsigned int i = 0; i < size; i++) {
				vec.push_back(Object(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", 0, 0));
			}
		}
		else if (line.find("Object: ") != std::string::npos) {
			std::string value = line.substr(8);
			currentObject = std::stoi(value);
		}
		else if (line.find("translation.x: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateX(std::stof(value));
		}
		else if (line.find("translation.y: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateY(std::stof(value));
		}
		else if (line.find("translation.z: ") != std::string::npos) {
			std::string value = line.substr(15);
			vec[currentObject].TranslateZ(std::stof(value));
		}
		else if (line.find("rotation.x: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateX(std::stof(value));
		}
		else if (line.find("rotation.y: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateY(std::stof(value));
		}
		else if (line.find("rotation.z: ") != std::string::npos) {
			std::string value = line.substr(12);
			vec[currentObject].RotateZ(std::stof(value));
		}
		else if (line.find("scale.x: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleX(std::stof(value));
		}
		else if (line.find("scale.y: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleY(std::stof(value));
		}
		else if (line.find("scale.z: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].ScaleZ(std::stof(value));
		}
		else if (line.find("texture: ") != std::string::npos) {
			std::string value = line.substr(9);
			vec[currentObject].SetTexture(std::stoi(value));
		}
		else if (line.find("shader: ") != std::string::npos) {
			std::string value = line.substr(8);
			vec[currentObject].SetShader(std::stoi(value));
		}
	}
}

void IO::SaveToFile(std::vector<Sentence>& vec, const std::string dir, const std::string fileName)
{
	printf("Saving to file: %s%s", dir.c_str(), fileName.c_str());
	std::ofstream outfile(dir + fileName);
	outfile << "Total Size: " << vec.size() << "\n\n";
	for (unsigned int i = 0; i < vec.size(); i++) {
		glm::vec3 translation = vec[i].GetTranslation();
		glm::vec3 rotation = vec[i].GetRotation();
		glm::vec3 scale = vec[i].GetScale();
		GLuint tex = vec[i].GetTextureID();
		GLuint shader = vec[i].GetShaderID();
		outfile << "Object: " << i << "\n";
		outfile << "translation.x: " << translation.x << "\n";
		outfile << "translation.y: " << translation.y << "\n";
		outfile << "translation.z: " << translation.z << "\n";
		outfile << "rotation.x: " << rotation.x << "\n";
		outfile << "rotation.y: " << rotation.y << "\n";
		outfile << "rotation.z: " << rotation.z << "\n";
		outfile << "scale.x: " << scale.x << "\n";
		outfile << "scale.y: " << scale.y << "\n";
		outfile << "scale.z: " << scale.z << "\n";
		outfile << "texture: " << tex << "\n";
		outfile << "shader: " << shader << "\n";
		outfile << "\n";
	}
	outfile.close();
}*/