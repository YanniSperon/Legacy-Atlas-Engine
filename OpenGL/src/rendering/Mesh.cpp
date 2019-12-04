#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/ShapeGenerator.h"
#include "Global.h"
#include "System.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

namespace Atlas {

	Mesh::Mesh()
		: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), objectType(type::cubeModel)
	{

	}

	Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name)
		: directory(dir), fileName(name), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(min), maxExtents(max), scale(1.0f, 1.0f, 1.0f), objectType(type)
	{
		System::Log("Creating mesh \"" + dir + name + "\"");
		if (type == type::cubeModel) {
			if (Global::Variables.meshCache.find("default::type::cube") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::cube"];
			}
			else {
				Global::Variables.meshCache["default::type::cube"] = ShapeGenerator::makeCube(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::cube"];
			}
		}
		else if (type == type::normalModel) {
			try {
				if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
					shape = Global::Variables.meshCache[dir + fileName];
				}
				else {
					System::Err("Attempting to load normal shape with location \"" + dir + fileName + "\"");
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = System::ConvertFilePathToLocal(file);
					System::Warn("    Local filepath \"" + file + "\"");
					Filepath pathtemp = System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					Global::Variables.loadedMeshCache[meshName] = physicalLocation;

					Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadShape(meshDirectory + meshName, minExtents, maxExtents);
					shape = Global::Variables.meshCache[meshDirectory + meshName];
					System::Warn("    Mesh dir and name (key): \"" + meshDirectory + meshName + "\"");
					System::Warn("    Original mesh dir and name (value): \"" + dir + name + "\"");
				}
			}
			catch (const std::exception & e) {
				try {
					if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
						shape = Global::Variables.meshCache[dir + fileName];
					}
					else {
						System::Err("Attempting to load textured shape with location \"" + dir + fileName + "\"");
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = System::ConvertFilePathToLocal(file);
						System::Warn("    Local filepath \"" + file + "\"");
						Filepath pathtemp = System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						Global::Variables.loadedMeshCache[meshName] = physicalLocation;

						Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
						shape = Global::Variables.meshCache[meshDirectory + meshName];
						System::Warn("    Mesh dir and name (key): \"" + meshDirectory + meshName + "\"");
						System::Warn("    Original mesh dir and name (value): \"" + dir + name + "\"");
					}
				}
				catch (const std::exception & e) {
					System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
				}
			}
		}
		else if (type == type::skyBox) {
			if (Global::Variables.meshCache.find("default::type::skyBox") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::skyBox"];
			}
			else {
				Global::Variables.meshCache["default::type::skyBox"] = ShapeGenerator::makeSkybox(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::skyBox"];
			}
		}
		else if (type == type::cubeInvertedLighting) {
			if (Global::Variables.meshCache.find("default::type::cubeInvertedLighting") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
			else {
				Global::Variables.meshCache["default::type::cubeInvertedLighting"] = ShapeGenerator::makeInvertedLightingCube(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
		}
		else {
			if (Global::Variables.meshCache.find("default::type::triangle") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::triangle"];
			}
			else {
				Global::Variables.meshCache["default::type::triangle"] = ShapeGenerator::makeTriangle(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::triangle"];
			}
		}
	}

	Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: directory(dir), fileName(name), rotation(rot), translation(trans), minExtents(min), maxExtents(max), scale(s), objectType(type)
	{
		System::Log("Creating mesh \"" + dir + name + "\"");
		if (type == type::cubeModel) {
			if (Global::Variables.meshCache.find("default::type::cube") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::cube"];
			}
			else {
				Global::Variables.meshCache["default::type::cube"] = ShapeGenerator::makeCube(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::cube"];
			}
		}
		else if (type == type::normalModel) {
			try {
				if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
					shape = Global::Variables.meshCache[dir + fileName];
				}
				else {
					System::Err("Attempting to load normal shape with location \"" + dir + fileName + "\"");
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = System::ConvertFilePathToLocal(file);
					System::Warn("    Local filepath \"" + file + "\"");
					Filepath pathtemp = System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					Global::Variables.loadedMeshCache[meshName] = physicalLocation;

					Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadShape(meshDirectory + meshName, minExtents, maxExtents);
					shape = Global::Variables.meshCache[meshDirectory + meshName];
					System::Warn("    Mesh dir and name (key): \"" + meshDirectory + meshName + "\"");
					System::Warn("    Original mesh dir and name (value): \"" + dir + name + "\"");
				}
			}
			catch (const std::exception & e) {
				try {
					if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
						shape = Global::Variables.meshCache[dir + fileName];
					}
					else {
						System::Err("Attempting to load textured shape with location \"" + dir + fileName + "\"");
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = System::ConvertFilePathToLocal(file);
						System::Warn("    Local filepath \"" + file + "\"");
						Filepath pathtemp = System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						Global::Variables.loadedMeshCache[meshName] = physicalLocation;

						Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
						shape = Global::Variables.meshCache[meshDirectory + meshName];
						System::Warn("    Mesh dir and name (key): \"" + meshDirectory + meshName + "\"");
						System::Warn("    Original mesh dir and name (value): \"" + dir + name + "\"");
					}
				}
				catch (const std::exception & e) {
					System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
				}
			}
		}
		else if (type == type::skyBox) {
			if (Global::Variables.meshCache.find("default::type::skyBox") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::skyBox"];
			}
			else {
				Global::Variables.meshCache["default::type::skyBox"] = ShapeGenerator::makeSkybox(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::skyBox"];
			}
		}
		else if (type == type::cubeInvertedLighting) {
			if (Global::Variables.meshCache.find("default::type::cubeInvertedLighting") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
			else {
				Global::Variables.meshCache["default::type::cubeInvertedLighting"] = ShapeGenerator::makeInvertedLightingCube(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::cubeInvertedLighting"];
			}
		}
		else {
			if (Global::Variables.meshCache.find("default::type::triangle") != Global::Variables.meshCache.end()) {
				shape = Global::Variables.meshCache["default::type::triangle"];
			}
			else {
				Global::Variables.meshCache["default::type::triangle"] = ShapeGenerator::makeTriangle(minExtents, maxExtents);
				shape = Global::Variables.meshCache["default::type::triangle"];
			}
		}
	}

	Mesh::~Mesh()
	{

	}

	glm::mat4 Mesh::GetModelTransformMatrix()
	{
		return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)) * glm::scale(glm::mat4(), scale));
	}

	void Mesh::RotateX(float x)
	{
		rotation.x = x;
	}

	void Mesh::RotateY(float y)
	{
		rotation.y = y;
	}

	void Mesh::RotateZ(float z)
	{
		rotation.z = z;
	}

	void Mesh::Rotate3f(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}

	void Mesh::RotateVec3(glm::vec3 rot) {
		rotation = rot;
	}

	void Mesh::RotateAdd3f(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
	}

	void Mesh::RotateAddVec3(glm::vec3 rot)
	{
		rotation += rot;
	}

	void Mesh::TranslateX(float x)
	{
		translation.x = x;
	}

	void Mesh::TranslateY(float y)
	{
		translation.y = y;
	}

	void Mesh::TranslateZ(float z)
	{
		translation.z = z;
	}

	void Mesh::Translate3f(float x, float y, float z)
	{
		translation.x = x;
		translation.y = y;
		translation.z = z;
	}

	void Mesh::TranslateVec3(glm::vec3 trans) {
		translation = trans;
	}

	void Mesh::TranslateAdd3f(float x, float y, float z)
	{
		translation.x += x;
		translation.y += y;
		translation.z += z;
	}

	void Mesh::TranslateAddVec3(glm::vec3 trans)
	{
		translation += trans;
	}

	void Mesh::ScaleX(float x)
	{
		scale.x = x;
	}

	void Mesh::ScaleY(float y)
	{
		scale.y = y;
	}

	void Mesh::ScaleZ(float z)
	{
		scale.z = z;
	}

	void Mesh::Scale3f(float x, float y, float z)
	{
		if (scale.x > 0) {
			scale.x = x;
		}
		if (scale.y > 0) {
			scale.y = y;
		}
		if (scale.z > 0) {
			scale.z = z;
		}
	}

	void Mesh::ScaleVec3(glm::vec3 s)
	{
		if (s.x > 0) {
			scale.x = s.x;
		}
		if (s.y > 0) {
			scale.y = s.y;
		}
		if (s.z > 0) {
			scale.z = s.z;
		}
	}

	void Mesh::ScaleAdd3f(float x, float y, float z)
	{
		if (scale.x + x > 0) {
			scale.x += x;
		}
		if (scale.y + y > 0) {
			scale.y += y;
		}
		if (scale.z + z > 0) {
			scale.z += z;
		}
	}

	void Mesh::ScaleAddVec3(glm::vec3 s)
	{
		if (scale.x + s.x > 0) {
			scale.x += s.x;
		}
		if (scale.y + s.y > 0) {
			scale.y += s.y;
		}
		if (scale.z + s.z > 0) {
			scale.z += s.z;
		}
	}

	glm::vec3 Mesh::GetTranslation()
	{
		return translation;
	}

	glm::vec3 Mesh::GetRotation()
	{
		return rotation;
	}

	glm::vec3 Mesh::GetScale()
	{
		return scale;
	}

	ShapeData Mesh::GetShape()
	{
		return shape;
	}

	std::string Mesh::GetModelFileName()
	{
		return fileName;
	}

	std::string Mesh::GetModelFileDirectory()
	{
		return directory;
	}

	void Mesh::SetShape(ShapeData newShape)
	{
		shape = newShape;
	}

	std::string Mesh::GetModelType()
	{
		if (objectType == type::cubeModel) {
			return "cubeModel";
		}
		else if (objectType == type::cubeInvertedLighting) {
			return "cubeInvertedLighting";
		}
		else if (objectType == type::skyBox) {
			return "skyBox";
		}
		else if (objectType == type::normalModel) {
			return "normalModel";
		}
	}

	std::string Mesh::GetType()
	{
		return "Mesh";
	}

	void Mesh::FlushCache()
	{
		for (auto it : Global::Variables.meshCache) {
			it.second.cleanUp();
		}
		Global::Variables.meshCache.erase(Global::Variables.meshCache.begin(), Global::Variables.meshCache.end());
	}
}