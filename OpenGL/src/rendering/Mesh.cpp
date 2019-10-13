#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/ShapeGenerator.h"
#include <iostream>

Mesh::Mesh()
	: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f)
{

}

Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name)
	: directory(directory), fileName(fileName), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(min), maxExtents(max), scale(1.0f, 1.0f, 1.0f)
{
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(minExtents, maxExtents);
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name, minExtents, maxExtents);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
	}
	else if (type == type::skyBox) {
		shape = ShapeGenerator::makeSkybox(minExtents, maxExtents);
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(glm::vec3 min, glm::vec3 max, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
	: directory(directory), fileName(fileName), rotation(rot), translation(trans), minExtents(min), maxExtents(max), scale(s)
{
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(minExtents, maxExtents);
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name, minExtents, maxExtents);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
	}
	else if (type == type::skyBox) {
		shape = ShapeGenerator::makeSkybox(minExtents, maxExtents);
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
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

void Mesh::SetShape(ShapeData newShape)
{
	shape = newShape;
}
