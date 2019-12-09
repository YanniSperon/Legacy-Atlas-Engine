#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/ShapeGenerator.h"
#include "Global.h"
#include "System.h"
#include "Convert.h"
#include "PhysicsEngine.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>


namespace Atlas {

	Mesh::Mesh()
		: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), objectType(type::cubeModel), physicsObject(NULL), mass(0.0f)
	{

	}

	Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name, bool enablePhysics)
		: directory(dir), fileName(name), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(min), maxExtents(max), scale(1.0f, 1.0f, 1.0f), objectType(type), physicsObject(NULL), mass(0.0f)
	{
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
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = System::ConvertFilePathToLocal(file);
					Filepath pathtemp = System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					Global::Variables.loadedMeshCache[meshName] = physicalLocation;

					Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadShape(meshDirectory + meshName, minExtents, maxExtents);
					shape = Global::Variables.meshCache[meshDirectory + meshName];
				}
			}
			catch (const std::exception & e) {
				try {
					if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
						shape = Global::Variables.meshCache[dir + fileName];
					}
					else {
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = System::ConvertFilePathToLocal(file);
						Filepath pathtemp = System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						Global::Variables.loadedMeshCache[meshName] = physicalLocation;

						Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
						shape = Global::Variables.meshCache[meshDirectory + meshName];
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

		if (enablePhysics) {
			btCollisionShape* physicsShape = new btBoxShape(Convert::Vector3(glm::vec3(0.5f, 0.5f, 0.5f)));
			btTransform shapeTransformation;
			translation = glm::vec3(5.0f, 5.0f, 5.0f);
			shapeTransformation.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
			printf("\nTest: \n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", GetModelTransformMatrix()[0][0], GetModelTransformMatrix()[0][1], GetModelTransformMatrix()[0][2], GetModelTransformMatrix()[0][3], GetModelTransformMatrix()[1][0], GetModelTransformMatrix()[1][1], GetModelTransformMatrix()[1][2], GetModelTransformMatrix()[1][3], GetModelTransformMatrix()[2][0], GetModelTransformMatrix()[2][1], GetModelTransformMatrix()[2][2], GetModelTransformMatrix()[2][3], GetModelTransformMatrix()[3][0], GetModelTransformMatrix()[3][1], GetModelTransformMatrix()[3][2], GetModelTransformMatrix()[3][3]);
			physicsObject = PhysicsEngine::AddPhysicsBody(physicsShape, shapeTransformation, 0.0f);
		}
	}

	Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name, bool enablePhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float objectMass)
		: directory(dir), fileName(name), rotation(rot), translation(trans), minExtents(min), maxExtents(max), scale(s), objectType(type), physicsObject(NULL), mass(objectMass)
	{
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
					std::string file = dir + name;
					std::replace(file.begin(), file.end(), '\\', '/');
					std::string physicalLocation = "";

					file = System::ConvertFilePathToLocal(file);
					Filepath pathtemp = System::SeperateFilepath(file);
					std::string meshDirectory = pathtemp.directory;
					std::string meshName = pathtemp.filename;
					physicalLocation = pathtemp.directory + pathtemp.filename;

					Global::Variables.loadedMeshCache[meshName] = physicalLocation;

					Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadShape(meshDirectory + meshName, minExtents, maxExtents);
					shape = Global::Variables.meshCache[meshDirectory + meshName];
				}
			}
			catch (const std::exception & e) {
				try {
					if (Global::Variables.meshCache.find(dir + fileName) != Global::Variables.meshCache.end()) {
						shape = Global::Variables.meshCache[dir + fileName];
					}
					else {
						std::string file = dir + name;
						std::replace(file.begin(), file.end(), '\\', '/');
						std::string physicalLocation = "";

						file = System::ConvertFilePathToLocal(file);
						Filepath pathtemp = System::SeperateFilepath(file);
						std::string meshDirectory = pathtemp.directory;
						std::string meshName = pathtemp.filename;
						physicalLocation = pathtemp.directory + pathtemp.filename;

						Global::Variables.loadedMeshCache[meshName] = physicalLocation;

						Global::Variables.meshCache[meshDirectory + meshName] = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
						shape = Global::Variables.meshCache[meshDirectory + meshName];
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
		
		if (enablePhysics) {
			btCollisionShape* physicsShape = new btBoxShape(Convert::Vector3(maxExtents));
			physicsShape->setLocalScaling(Convert::Vector3(s));
			btTransform shapeTransformation;
			shapeTransformation.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
			printf("\nTest: \n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", GetModelTransformMatrix()[0][0], GetModelTransformMatrix()[0][1], GetModelTransformMatrix()[0][2], GetModelTransformMatrix()[0][3], GetModelTransformMatrix()[1][0], GetModelTransformMatrix()[1][1], GetModelTransformMatrix()[1][2], GetModelTransformMatrix()[1][3], GetModelTransformMatrix()[2][0], GetModelTransformMatrix()[2][1], GetModelTransformMatrix()[2][2], GetModelTransformMatrix()[2][3], GetModelTransformMatrix()[3][0], GetModelTransformMatrix()[3][1], GetModelTransformMatrix()[3][2], GetModelTransformMatrix()[3][3]);
			physicsObject = PhysicsEngine::AddPhysicsBody(physicsShape, shapeTransformation, mass);
		}
	}

	Mesh::~Mesh()
	{
		
	}

	glm::mat4 Mesh::GetModelTransformMatrix()
	{
		glm::mat4 returnMat4;
		if (physicsObject != NULL) {
			physicsObject->getWorldTransform().getOpenGLMatrix(&returnMat4[0][0]);
		}
		else {
			returnMat4 = (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)) * glm::scale(glm::mat4(), scale));
		}
		return returnMat4 * glm::scale(glm::mat4(), scale);
	}

	glm::mat4 Mesh::GetModelTransRotMatrix()
	{
		return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
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
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
		}
	}

	void Mesh::ScaleY(float y)
	{
		scale.y = y;
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
		}
	}

	void Mesh::ScaleZ(float z)
	{
		scale.z = z;
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
		}
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
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
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
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
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
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
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
		if (physicsObject != NULL) {
			physicsObject->getCollisionShape()->setLocalScaling(Convert::Vector3(scale));
			PhysicsEngine::Recalculate(physicsObject);
		}
	}

	void Mesh::Update()
	{
		if (physicsObject != NULL) {
			translation = Convert::Vector3(physicsObject->getWorldTransform().getOrigin());
			physicsObject->getWorldTransform().getRotation().getEulerZYX(rotation.z, rotation.y, rotation.x);
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

	float Mesh::GetMass()
	{
		return mass;
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

	void Mesh::Cleanup()
	{
		if (physicsObject != NULL) {
			PhysicsEngine::RemovePhysicsBody(physicsObject);
		}
	}

	void Mesh::FlushCache()
	{
		for (auto it : Global::Variables.meshCache) {
			it.second.cleanUp();
		}
		Global::Variables.meshCache.erase(Global::Variables.meshCache.begin(), Global::Variables.meshCache.end());
	}
	void Mesh::test()
	{
		if (btRigidBody* body = btRigidBody::upcast(physicsObject))
		{
			body->activate(true);
			body->applyCentralForce(btVector3(0.0f, 5.0f, 0.0f));
		}
	}
}