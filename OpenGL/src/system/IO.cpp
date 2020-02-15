#include "IO.h"
#include "Light.h"
#include "Mesh.h"
#include "Global.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include <future>
#include <chrono>
#include <fstream>

namespace Atlas {

	static std::mutex meshLoaderMutex;

	static void LoadData(std::vector<Object*>& vec, std::string filePath)
	{
		std::ifstream objDataStream(filePath);
		if (!objDataStream.is_open()) {
			System::Err("\"" + filePath + "\"");
		}
		else {
			glm::vec3 translation(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation(0.0f, 0.0f, 0.0f);
			glm::vec3 scale(1.0f, 1.0f, 1.0f);
			glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
			glm::vec3 diffuse = glm::vec3(0.25f, 0.25f, 0.25f);
			glm::vec3 specular = glm::vec3(0.25f, 0.25f, 0.25f);
			float shininess = 32.0f;
			bool hasLighting = true;
			std::string modelFileDirectory = "";
			std::string modelFileName = "";
			std::string textureFileDirectory = "";
			std::string textureFileName = "";
			std::string shaderFileDirectory = "";
			std::string shaderFileName = "";
			std::string strType = "Invalid";
			float mass = 0.0f;
			glm::vec3 linearVelocity(0.0f, 0.0f, 0.0f);
			glm::vec3 angularVelocity(0.0f, 0.0f, 0.0f);
			glm::vec3 torque(0.0f, 0.0f, 0.0f);
			glm::vec3 force(0.0f, 0.0f, 0.0f);
			glm::vec3 gravity(0.0f, 0.0f, 0.0f);
			float momentOfInertia = 1.0f;
			glm::vec3 lightAmbient(1.0f, 1.0f, 1.0f);
			glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);
			glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
			type objectType = type::cubeModel;
			unsigned long long int uid = 0;

			while (!objDataStream.eof()) {
				std::string line;
				std::getline(objDataStream, line);

				if (line.find("#") != std::string::npos) {
				}
				else if (line.find("type: ") != std::string::npos) {
					std::string value = line.substr(6);
					strType = value;
				}
				else if (line.find("modelType: ") != std::string::npos) {
					std::string value = line.substr(11);
					if (value == "cubeModel") {
						objectType = type::cubeModel;
					}
					else if (value == "cubeInvertedLighting") {
						objectType = type::cubeInvertedLighting;
					}
					else if (value == "skyBox") {
						objectType = type::skyBox;
					}
					else if (value == "normalModel") {
						objectType = type::normalModel;
					}
					else {
						System::Warn("Unrecognized string \"" + value + "\" when loading file \"" + filePath + "\"");
						objectType = type::cubeModel;
					}
				}
				else if (line.find("translation.x: ") != std::string::npos) {
					std::string value = line.substr(15);
					translation.x = std::stof(value);
				}
				else if (line.find("translation.y: ") != std::string::npos) {
					std::string value = line.substr(15);
					translation.y = std::stof(value);
				}
				else if (line.find("translation.z: ") != std::string::npos) {
					std::string value = line.substr(15);
					translation.z = std::stof(value);
				}
				else if (line.find("rotation.x: ") != std::string::npos) {
					std::string value = line.substr(12);
					rotation.x = std::stof(value);
				}
				else if (line.find("rotation.y: ") != std::string::npos) {
					std::string value = line.substr(12);
					rotation.y = std::stof(value);
				}
				else if (line.find("rotation.z: ") != std::string::npos) {
					std::string value = line.substr(12);
					rotation.z = std::stof(value);
				}
				else if (line.find("scale.x: ") != std::string::npos) {
					std::string value = line.substr(9);
					scale.x = std::stof(value);
				}
				else if (line.find("scale.y: ") != std::string::npos) {
					std::string value = line.substr(9);
					scale.y = std::stof(value);
				}
				else if (line.find("scale.z: ") != std::string::npos) {
					std::string value = line.substr(9);
					scale.z = std::stof(value);
				}
				else if (line.find("ambient.r: ") != std::string::npos) {
					std::string value = line.substr(11);
					ambient.r = std::stof(value);
				}
				else if (line.find("ambient.g: ") != std::string::npos) {
					std::string value = line.substr(11);
					ambient.g = std::stof(value);
				}
				else if (line.find("ambient.b: ") != std::string::npos) {
					std::string value = line.substr(11);
					ambient.b = std::stof(value);
				}
				else if (line.find("diffuse.r: ") != std::string::npos) {
					std::string value = line.substr(11);
					diffuse.r = std::stof(value);
				}
				else if (line.find("diffuse.g: ") != std::string::npos) {
					std::string value = line.substr(11);
					diffuse.g = std::stof(value);
				}
				else if (line.find("diffuse.b: ") != std::string::npos) {
					std::string value = line.substr(11);
					diffuse.b = std::stof(value);
				}
				else if (line.find("specular.r: ") != std::string::npos) {
					std::string value = line.substr(12);
					specular.r = std::stof(value);
				}
				else if (line.find("specular.g: ") != std::string::npos) {
					std::string value = line.substr(12);
					specular.g = std::stof(value);
				}
				else if (line.find("specular.b: ") != std::string::npos) {
					std::string value = line.substr(12);
					specular.b = std::stof(value);
				}
				else if (line.find("shininess: ") != std::string::npos) {
					std::string value = line.substr(11);
					shininess = std::stof(value);
				}
				else if (line.find("hasLighting: ") != std::string::npos) {
					std::string value = line.substr(13);
					if (value == "true") {
						hasLighting = true;
					}
					else {
						hasLighting = false;
					}
				}
				else if (line.find("modelFileDir: ") != std::string::npos) {
					std::string value = line.substr(14);
					modelFileDirectory = value;
				}
				else if (line.find("modelFileName: ") != std::string::npos) {
					std::string value = line.substr(15);
					modelFileName = value;
				}
				else if (line.find("textureDir: ") != std::string::npos) {
					std::string value = line.substr(12);
					textureFileDirectory = value;
				}
				else if (line.find("textureName: ") != std::string::npos) {
					std::string value = line.substr(13);
					textureFileName = value;
				}
				else if (line.find("shaderDir: ") != std::string::npos) {
					std::string value = line.substr(11);
					shaderFileDirectory = value;
				}
				else if (line.find("shaderName: ") != std::string::npos) {
					std::string value = line.substr(12);
					shaderFileName = value;
				}
				else if (line.find("uid: ") != std::string::npos) {
					std::string value = line.substr(5);
					uid = std::stoull(value);
				}
				else if (line.find("ambientLight.r: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightAmbient.r = std::stof(value);
				}
				else if (line.find("ambientLight.g: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightAmbient.g = std::stof(value);
				}
				else if (line.find("ambientLight.b: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightAmbient.b = std::stof(value);
				}
				else if (line.find("diffuseLight.r: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightDiffuse.r = std::stof(value);
				}
				else if (line.find("diffuseLight.g: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightDiffuse.g = std::stof(value);
				}
				else if (line.find("diffuseLight.b: ") != std::string::npos) {
					std::string value = line.substr(16);
					lightDiffuse.b = std::stof(value);
				}
				else if (line.find("specularLight.r: ") != std::string::npos) {
					std::string value = line.substr(17);
					lightSpecular.r = std::stof(value);
				}
				else if (line.find("specularLight.g: ") != std::string::npos) {
					std::string value = line.substr(17);
					lightSpecular.g = std::stof(value);
				}
				else if (line.find("specularLight.b: ") != std::string::npos) {
					std::string value = line.substr(17);
					lightSpecular.b = std::stof(value);
				}
				else if (line.find("mass: ") != std::string::npos) {
					std::string value = line.substr(6);
					mass = std::stof(value);
				}
				else if (line.find("g.x: ") != std::string::npos) {
					std::string value = line.substr(5);
					gravity.x = std::stof(value);
				}
				else if (line.find("g.y: ") != std::string::npos) {
					std::string value = line.substr(5);
					gravity.y = std::stof(value);
				}
				else if (line.find("g.z: ") != std::string::npos) {
					std::string value = line.substr(5);
					gravity.z = std::stof(value);
				}
				else if (line.find("linVel.x: ") != std::string::npos) {
					std::string value = line.substr(10);
					linearVelocity.x = std::stof(value);
				}
				else if (line.find("linVel.y: ") != std::string::npos) {
					std::string value = line.substr(10);
					linearVelocity.y = std::stof(value);
				}
				else if (line.find("linVel.z: ") != std::string::npos) {
					std::string value = line.substr(10);
					linearVelocity.z = std::stof(value);
				}
				else if (line.find("angVel.x: ") != std::string::npos) {
					std::string value = line.substr(10);
					angularVelocity.x = std::stof(value);
				}
				else if (line.find("angVel.y: ") != std::string::npos) {
					std::string value = line.substr(10);
					angularVelocity.y = std::stof(value);
				}
				else if (line.find("angVel.z: ") != std::string::npos) {
					std::string value = line.substr(10);
					angularVelocity.z = std::stof(value);
				}
				else if (line.find("f.x: ") != std::string::npos) {
					std::string value = line.substr(5);
					force.x = std::stof(value);
				}
				else if (line.find("f.y: ") != std::string::npos) {
					std::string value = line.substr(5);
					force.y = std::stof(value);
				}
				else if (line.find("f.z: ") != std::string::npos) {
					std::string value = line.substr(5);
					force.z = std::stof(value);
				}
				else if (line.find("t.x: ") != std::string::npos) {
					std::string value = line.substr(5);
					torque.x = std::stof(value);
				}
				else if (line.find("t.y: ") != std::string::npos) {
					std::string value = line.substr(5);
					torque.y = std::stof(value);
				}
				else if (line.find("t.z: ") != std::string::npos) {
					std::string value = line.substr(5);
					torque.z = std::stof(value);
				}
				else if (line.find("moi: ") != std::string::npos) {
					std::string value = line.substr(5);
					momentOfInertia = std::stof(value);
				}
			}

			Object* value;

			if (strType == "Light") {
				value = new Light(LightIntensity(lightAmbient, lightDiffuse, lightSpecular), objectType, modelFileDirectory, modelFileName, textureFileDirectory, textureFileName, shaderFileDirectory, shaderFileName, false, hasLighting, System::UpdateLastUID(uid), rotation, translation, scale, Material(ambient, diffuse, specular, shininess));
			}
			else if (strType == "Object") {
				value = new Object(objectType, modelFileDirectory, modelFileName, textureFileDirectory, textureFileName, shaderFileDirectory, shaderFileName, false, hasLighting, System::UpdateLastUID(uid), rotation, translation, scale, Material(ambient, diffuse, specular, shininess));
			}
			else if (strType == "Invalid") {
				value = new Object(objectType, modelFileDirectory, modelFileName, textureFileDirectory, textureFileName, shaderFileDirectory, shaderFileName, false, hasLighting, System::UpdateLastUID(uid), rotation, translation, scale, Material(ambient, diffuse, specular, shininess));
			}

			meshLoaderMutex.lock();
			vec.push_back(value);
			meshLoaderMutex.unlock();
		}
	}

	void IO::LoadFile(std::vector<Object*>& vec, const std::string dir, const std::string fileName)
	{
		//std::vector<std::future<void>> futures;
		std::ifstream f(System::ConvertFilePathToAbsolute(dir + fileName));

		if (!f.is_open()) {
			System::Err("File: \"" + System::ConvertFilePathToAbsolute(dir + fileName) + "\" does not exist or could not be loaded");
		}

		std::vector<std::string> filepaths;

		while (!f.eof())
		{
			std::string line;
			std::getline(f, line);

			if (line.find("Total Size: ") != std::string::npos) {
				std::string value = line.substr(12);
				int size = std::stoi(value);	
			}
			else if (line.find("Obj: ") != std::string::npos) {
				std::string value = line.substr(5);
				filepaths.push_back(value);
			}
		}

		for (unsigned int i = 0; i < filepaths.size(); i++) {
			//futures.push_back(std::async(std::launch::async, LoadData, std::ref(vec), filepaths[i]));
			LoadData(std::ref(vec), System::ConvertFilePathToAbsolute(filepaths[i]));
		}
	}

	static void SaveData(Object* obj, std::string filePath, unsigned int index) {
		std::ofstream objectFile = std::ofstream(filePath);
		if (!objectFile.is_open()) {
			System::Err("Error loading save data file \"" + filePath + "\"");
			return;
		}
		std::string type = obj->GetType();

		glm::vec3 translation = obj->GetTranslation();
		glm::vec3 rotation = obj->GetRotation();
		glm::vec3 scale = obj->GetScale();
		Material mat = obj->GetMaterial();
		glm::vec3 ambient = mat.ambient;
		glm::vec3 diffuse = mat.diffuse;
		glm::vec3 specular = mat.specular;
		float shininess = mat.shininess;
		bool tempHasLighting = obj->GetHasLighting();
		std::string hasLighting = "false";
		if (tempHasLighting) {
			hasLighting = "true";
		}
		else {
			hasLighting = "false";
		}
		std::string modelFileDir = obj->GetModelFileDirectory();
		std::string modelFileName = obj->GetModelFileName();
		std::string texDir = obj->GetTextureDirectory();
		std::string texName = obj->GetTextureName();
		std::string shaderDir = obj->GetShaderDirectory();
		std::string shaderName = obj->GetShaderName();

		std::string modelType = obj->GetModelType();
		std::string uid = std::to_string(obj->GetUID());

		objectFile << "Object: " << index << "\n";
		objectFile << "type: " << type << "\n";
		objectFile << "modelType: " << modelType << "\n";
		objectFile << "translation.x: " << translation.x << "\n";
		objectFile << "translation.y: " << translation.y << "\n";
		objectFile << "translation.z: " << translation.z << "\n";
		objectFile << "rotation.x: " << rotation.x << "\n";
		objectFile << "rotation.y: " << rotation.y << "\n";
		objectFile << "rotation.z: " << rotation.z << "\n";
		objectFile << "scale.x: " << scale.x << "\n";
		objectFile << "scale.y: " << scale.y << "\n";
		objectFile << "scale.z: " << scale.z << "\n";
		objectFile << "ambient.r: " << ambient.r << "\n";
		objectFile << "ambient.g: " << ambient.g << "\n";
		objectFile << "ambient.b: " << ambient.b << "\n";
		objectFile << "diffuse.r: " << diffuse.r << "\n";
		objectFile << "diffuse.g: " << diffuse.g << "\n";
		objectFile << "diffuse.b: " << diffuse.b << "\n";
		objectFile << "specular.r: " << specular.r << "\n";
		objectFile << "specular.g: " << specular.g << "\n";
		objectFile << "specular.b: " << specular.b << "\n";
		objectFile << "shininess: " << shininess << "\n";
		objectFile << "hasLighting: " << hasLighting << "\n";
		objectFile << "modelFileDir: " << modelFileDir << "\n";
		objectFile << "modelFileName: " << modelFileName << "\n";
		objectFile << "textureDir: " << texDir << "\n";
		objectFile << "textureName: " << texName << "\n";
		objectFile << "shaderDir: " << shaderDir << "\n";
		objectFile << "shaderName: " << shaderName << "\n";
		objectFile << "uid: " << uid << "\n";
		if (type == "Light") {
			Light* light = dynamic_cast<Light*>(obj);
			if (light != nullptr) {
				LightIntensity intensity = light->GetLightIntensity();
				glm::vec3 ambient = intensity.ambient;
				glm::vec3 diffuse = intensity.diffuse;
				glm::vec3 specular = intensity.specular;
				objectFile << "ambientLight.r " << ambient.r << "\n";
				objectFile << "ambientLight.g " << ambient.g << "\n";
				objectFile << "ambientLight.b " << ambient.b << "\n";
				objectFile << "diffuseLight.r " << diffuse.r << "\n";
				objectFile << "diffuseLight.g " << diffuse.g << "\n";
				objectFile << "diffuseLight.b " << diffuse.b << "\n";
				objectFile << "specularLight.r " << specular.r << "\n";
				objectFile << "specularLight.g " << specular.g << "\n";
				objectFile << "specularLight.b " << specular.b << "\n";
			}
		}
		else if (type == "PhysicsBody") {
			//PhysicsBody* physicsBody = dynamic_cast<PhysicsBody*>(obj);
			//if (physicsBody != nullptr) {
			//	float mass = physicsBody->GetMass();
			//	glm::vec3 g = physicsBody->GetGravitationalForce();
			//	glm::vec3 linVel = physicsBody->GetLinearVelocity();
			//	glm::vec3 angVel = physicsBody->GetAngularVelocity();
			//	glm::vec3 f = physicsBody->GetForce();
			//	glm::vec3 t = physicsBody->GetTorque();
			//	float moi = physicsBody->GetMomentOfInertia();
			//
			//	objectFile << "mass: " << mass << "\n";
			//	objectFile << "g.x: " << g.x << "\n";
			//	objectFile << "g.y: " << g.y << "\n";
			//	objectFile << "g.z: " << g.z << "\n";
			//	objectFile << "linVel.x: " << linVel.x << "\n";
			//	objectFile << "linVel.y: " << linVel.y << "\n";
			//	objectFile << "linVel.z: " << linVel.z << "\n";
			//	objectFile << "angVel.x: " << angVel.x << "\n";
			//	objectFile << "angVel.y: " << angVel.y << "\n";
			//	objectFile << "angVel.z: " << angVel.z << "\n";
			//	objectFile << "f.x: " << f.x << "\n";
			//	objectFile << "f.y: " << f.y << "\n";
			//	objectFile << "f.z: " << f.z << "\n";
			//	objectFile << "t.x: " << t.x << "\n";
			//	objectFile << "t.y: " << t.y << "\n";
			//	objectFile << "t.z: " << t.z << "\n";
			//	objectFile << "moi: " << moi << "\n";
			//}
		}
		else if (type == "Object") {
			Object* object = dynamic_cast<Object*>(obj);
			if (object != nullptr) {

			}
		}
		objectFile << "\n";
		objectFile.close();
	}

	void IO::SaveToFile(std::vector<Object*>& vec, const std::string dir, const std::string fileName)
	{
		std::vector<std::future<void>> futures;
		std::ofstream outfile(System::ConvertFilePathToAbsolute(dir + fileName));
		if (!outfile.is_open()) {
			System::Err("Error saving objects to level and data files!");
			return;
		}
		outfile << "Total Size: " << vec.size() << "\n\n";
		for (unsigned int i = 0; i < vec.size(); i++) {
			std::string str = System::ConvertFilePathToAbsolute(dir + "data/obj" + std::to_string(i) + ".dat");
			outfile << "Obj: " << str << "\n";
			futures.push_back(std::async(std::launch::async, SaveData, vec[i], str, i));
		}
	}
	//
	//void IO::LoadFile(std::vector<Object2D*>& vec, const std::string dir, const std::string fileName)
	//{
	//	std::ifstream f(dir + fileName);
	//
	//	if (!f.is_open()) {
	//		System::Err("File: \"" + dir + fileName + "\" does not exist or could not be loaded");
	//	}
	//
	//	glm::vec2 translation;
	//	float rotation;
	//	glm::vec2 scale;
	//	glm::vec2 texCoordMin;
	//	glm::vec2 texCoordMax;
	//	GLuint shader = 0;
	//	GLuint texture = 0;
	//
	//	while (!f.eof())
	//	{
	//		std::string line;
	//		std::getline(f, line);
	//
	//		if (line.find("#") != std::string::npos || line.size() == 0) {
	//		}
	//		else if (line.find("Object2D: ") != std::string::npos) {
	//		}
	//		else if (line.find("translation.x: ") != std::string::npos) {
	//			std::string value = line.substr(15);
	//			translation.x = std::stof(value);
	//		}
	//		else if (line.find("translation.y: ") != std::string::npos) {
	//			std::string value = line.substr(15);
	//			translation.y = std::stof(value);
	//		}
	//		else if (line.find("rotation: ") != std::string::npos) {
	//			std::string value = line.substr(10);
	//			rotation = std::stof(value);
	//		}
	//		else if (line.find("scale.x: ") != std::string::npos) {
	//			std::string value = line.substr(9);
	//			scale.x = std::stof(value);
	//		}
	//		else if (line.find("scale.y: ") != std::string::npos) {
	//			std::string value = line.substr(9);
	//			scale.y = std::stof(value);
	//		}
	//		else if (line.find("texture: ") != std::string::npos) {
	//			std::string value = line.substr(9);
	//			texture = std::stoi(value);
	//		}
	//		else if (line.find("textureCoordMin.x: ") != std::string::npos) {
	//			std::string value = line.substr(19);
	//			texCoordMin.x = std::stof(value);
	//		}
	//		else if (line.find("textureCoordMin.y: ") != std::string::npos) {
	//			std::string value = line.substr(19);
	//			texCoordMin.y = std::stof(value);
	//		}
	//		else if (line.find("textureCoordMax.x: ") != std::string::npos) {
	//			std::string value = line.substr(19);
	//			texCoordMax.x = std::stof(value);
	//		}
	//		else if (line.find("textureCoordMax.y: ") != std::string::npos) {
	//			std::string value = line.substr(19);
	//			texCoordMax.y = std::stof(value);
	//		}
	//		else if (line.find("shader: ") != std::string::npos) {
	//			std::string value = line.substr(8);
	//			shader = std::stoi(value);
	//		}
	//		else if (line.find("End Object2D") != std::string::npos) {
	//			vec.push_back(new Object2D(glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, 50.0f), rotation, translation, scale, texture, shader, texCoordMin, texCoordMax));
	//		}
	//	}
	//}
	//
	//void IO::SaveToFile(std::vector<Object2D*>& vec, const std::string dir, const std::string fileName)
	//{
	//	System::Log("Saving to file: \"" + dir + fileName + "\"");
	//	std::ofstream outfile(dir + fileName);
	//	outfile << "Total Size: " << vec.size() << "\n\n";
	//	for (unsigned int i = 0; i < vec.size(); i++) {
	//		glm::vec2 translation = vec[i]->GetTranslation();
	//		float rotation = vec[i]->GetRotation();
	//		glm::vec2 scale = vec[i]->GetScale();
	//		glm::vec2 texCoordMin = vec[i]->GetMinTexCoords();
	//		glm::vec2 texCoordMax = vec[i]->GetMaxTexCoords();
	//		GLuint tex = vec[i]->GetTextureID();
	//		GLuint shader = vec[i]->GetShaderID();
	//		outfile << "Object2D: " << i << "\n";
	//		outfile << "translation.x: " << translation.x << "\n";
	//		outfile << "translation.y: " << translation.y << "\n";
	//		outfile << "rotation: " << rotation << "\n";
	//		outfile << "scale.x: " << scale.x << "\n";
	//		outfile << "scale.y: " << scale.y << "\n";
	//		outfile << "texture: " << tex << "\n";
	//		outfile << "textureCoordMin.x: " << texCoordMin.x << "\n";
	//		outfile << "textureCoordMin.y: " << texCoordMin.y << "\n";
	//		outfile << "textureCoordMax.x: " << texCoordMax.x << "\n";
	//		outfile << "textureCoordMax.y: " << texCoordMax.y << "\n";
	//		outfile << "shader: " << shader << "\n";
	//		outfile << "End Object2D\n";
	//		outfile << "\n";
	//	}
	//	outfile.close();
	//}
}