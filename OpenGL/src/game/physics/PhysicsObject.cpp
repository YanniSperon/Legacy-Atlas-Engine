#include "PhysicsObject.h"
#include "Global.h"
#include <algorithm>
#include "Convert.h"
#include "System.h"
#include "Loader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
//#include "glm/gtx/quaternion.hpp"

namespace Atlas {

	PhysicsObject::PhysicsObject()
		: uid(), vertexBufferID(0), indexBufferID(0), texID(0), shaderID(0), numIndices(0), material(), glInitialized(false), textureDirectory(""), textureName(""), shaderDirectory(""), shaderName(""), hasLighting(false), physicsObject(NULL)
	{
	}

	PhysicsObject::PhysicsObject(Object* obj, float mass)
		: Mesh(obj->GetTypeEnum(), obj->GetModelFileDirectory(), obj->GetModelFileName(), obj->GetRotation(), obj->GetTranslation(), obj->GetScale()), glInitialized(false), uid()
	{
		textureDirectory = obj->GetTextureDirectory();
		textureName = obj->GetTextureName();
		shaderDirectory = obj->GetShaderDirectory();
		shaderName = obj->GetShaderName();
		hasLighting = obj->GetHasLighting();
		material = obj->GetMaterial();

		//if (Global::Variables.textureCache.find(obj->GetTextureDirectory() + obj->GetTextureName()) != Global::Variables.textureCache.end()) {
		//	texID = Global::Variables.textureCache[obj->GetTextureDirectory() + obj->GetTextureName()];
		//}
		//else {
		//	std::string file = obj->GetTextureDirectory() + obj->GetTextureName();
		//	std::replace(file.begin(), file.end(), '\\', '/');
		//	std::string physicalLocation = "";
		//
		//	file = System::ConvertFilePathToLocal(file);
		//	Filepath pathtemp = System::SeperateFilepath(file);
		//	std::string textureDir = pathtemp.directory;
		//	std::string texName = pathtemp.filename;
		//	physicalLocation = pathtemp.directory + pathtemp.filename;
		//
		//	Global::Variables.loadedTextureCache[texName] = physicalLocation;
		//
		//	Global::Variables.textureCache[textureDir + texName] = Loader::LoadTexture(textureDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		//	texID = Global::Variables.textureCache[textureDir + texName];
		//}
		//
		//if (Global::Variables.shaderCache.find(obj->GetShaderDirectory() + obj->GetShaderName()) != Global::Variables.shaderCache.end()) {
		//	shaderID = Global::Variables.shaderCache[obj->GetShaderDirectory() + obj->GetShaderName()]->GetShaderID();
		//}
		//else {
		//	std::string file = obj->GetShaderDirectory() + obj->GetShaderName();
		//	std::replace(file.begin(), file.end(), '\\', '/');
		//	std::string physicalLocation = "";
		//
		//	file = System::ConvertFilePathToLocal(file);
		//	Filepath pathtemp = System::SeperateFilepath(file);
		//	std::string shadrDirectory = pathtemp.directory;
		//	std::string shadrName = pathtemp.filename;
		//	physicalLocation = pathtemp.directory + pathtemp.filename;
		//
		//	Global::Variables.loadedShaderCache[shadrName] = physicalLocation;
		//
		//	Global::Variables.shaderCache[shadrDirectory + shadrName] = new Shader(shadrDirectory + shadrName);
		//	shaderID = Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		//}
		//numIndices = (GLsizei)GetShape().numIndices;

		vertexBufferID = obj->GetVBO();
		indexBufferID = obj->GetIBO();
		texID = obj->GetTextureID();
		shaderID = obj->GetShaderID();
		numIndices = obj->GetNumIndices();
		
		btCollisionShape* physicsShape = new btBoxShape(Convert::Vector3(GetShape().max));
		physicsShape->setLocalScaling(Convert::Vector3(obj->GetScale()));
		btTransform shapeTransformation;
		shapeTransformation.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
		physicsObject = PhysicsEngine::AddPhysicsBody(physicsShape, shapeTransformation, mass, this);

		if (obj->GetGLInitialized()) {
			GLInit();
		}
	}

	PhysicsObject::~PhysicsObject()
	{

	}

	void PhysicsObject::Update()
	{
		if (physicsObject != NULL) {
			TranslateVec3(Convert::Vector3(physicsObject->getWorldTransform().getOrigin()));
			glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			physicsObject->getWorldTransform().getRotation().getEulerZYX(rotation.z, rotation.y, rotation.x);
			RotateVec3(rotation);
		}
	}

	void PhysicsObject::InverseUpdate()
	{
		if (physicsObject != NULL) {
			btTransform transform;
			transform.setIdentity();
			transform.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
			physicsObject->setWorldTransform(transform);
		}
	}

	glm::mat4 PhysicsObject::GetModelTransformMatrix()
	{
		glm::mat4 returnMat4;
		if (physicsObject != NULL) {
			physicsObject->getWorldTransform().getOpenGLMatrix(&returnMat4[0][0]);
		}
		else {
			returnMat4 = (glm::translate(glm::mat4(), GetTranslation()) * glm::yawPitchRoll(glm::radians(GetRotation().x), glm::radians(GetRotation().y), glm::radians(GetRotation().z)) * glm::scale(glm::mat4(), GetScale()));
		}
		return returnMat4 * glm::scale(glm::mat4(), GetScale());

	}

	bool PhysicsObject::GetGLInitialized()
	{
		return glInitialized;
	}

	Material PhysicsObject::GetMaterial()
	{
		return material;
	}

	bool PhysicsObject::GetHasLighting()
	{
		return hasLighting;
	}

	GLuint PhysicsObject::GetShaderID()
	{
		return shaderID;
	}

	GLuint PhysicsObject::GetTextureID()
	{
		return texID;
	}

	GLuint PhysicsObject::GetVBO()
	{
		return vertexBufferID;
	}

	btCollisionObject* PhysicsObject::GetPhysicsObject()
	{
		return physicsObject;
	}

	const UUID& PhysicsObject::GetUID() const
	{
		return uid;
	}

	void PhysicsObject::SetHasLighting(bool newValue)
	{
		hasLighting = newValue;
	}

	void PhysicsObject::Launch(glm::vec3 viewDirection)
	{
		btRigidBody* body = btRigidBody::upcast(physicsObject);
		if (body != NULL) {
			body->setLinearVelocity(Convert::Vector3(50.0f * viewDirection));
			glm::normalize(viewDirection);
		}
	}

	void PhysicsObject::Draw()
	{
		Bind();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void PhysicsObject::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void PhysicsObject::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void PhysicsObject::PrepareForDeletion()
	{
		BulletPhysicsObject* userPtr = (BulletPhysicsObject*)physicsObject->getUserPointer();
		delete userPtr;
		physicsObject->setUserPointer(NULL);
		PhysicsEngine::RemovePhysicsBody(physicsObject);
	}

	void PhysicsObject::GLInit()
	{
		glInitialized = true;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));



		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);



		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glFinish();
	}

	std::string to_string(void* userPointer) {
		if (userPointer) {
			BulletPhysicsObject* userPtr = static_cast<BulletPhysicsObject*>(userPointer);
			if (userPtr) {
				return std::string("BulletPhysicsObject: {") + "\"UID\": \"" + std::to_string(userPtr->uid) + "\"}";
			}
			else {
				return "invalid cast";
			}
		}
		else {
			return "nullptr";
		}
	}

	std::string to_string(btCollisionObject* obj) {
		if (obj) {
			return std::string("btCollisionObject: {") + "\"User Object:\": \"" + to_string(obj->getUserPointer()) + "\"}";
		}
		else {
			return "nullptr";
		}
	}

	std::string PhysicsObject::ToString() {
		if (physicsObject) {
			if (physicsObject->getUserPointer()) {
				return std::string("PhysicsObject: {") + "\"UID\": \"" + std::to_string(uid) + "\" " + "\"CollisionUID\": \"" + std::to_string(static_cast<BulletPhysicsObject*>(physicsObject->getUserPointer())->uid) + "\" " + Mesh::ToString() + "}";
			}
		}

		return std::string("PhysicsObject: {") + "\"UID\": \"" + std::to_string(uid) + "\" " + "\"CollisionUID\": \"nullptr\" " + Mesh::ToString() + "}";

	}

	std::string PhysicsObject::ToStringVerbose() {
		return std::string("PhysicsObject: {") + "\"UID\": \"" + std::to_string(uid) + "\" " + "\"BTCollisionObject\": \"" + to_string(physicsObject) + "\" " + Mesh::ToString() + "}";
	}
}