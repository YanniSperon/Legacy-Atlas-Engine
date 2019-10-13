#include "Mesh2D.h"
#include "ShapeGenerator.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

Mesh2D::Mesh2D()
	: rotation(0.0f, 0.0f), translation(0.0f, 0.0f), scale(0.0f, 0.0f), minExtents(0.0f, 0.0f), maxExtents(0.0f, 0.0f)
{

}

Mesh2D::Mesh2D(glm::vec2 min, glm::vec2 max, glm::vec2 rot, glm::vec2 trans, glm::vec2 s, glm::vec2 minTex, glm::vec2 maxTex)
	: rotation(rot), translation(trans), scale(s), minExtents(min), maxExtents(max)
{
	shape = ShapeGenerator::makeSquare(min, max, minTex, maxTex);
}

Mesh2D::~Mesh2D()
{

}

glm::mat4 Mesh2D::GetModelTransformMatrix()
{
	return (glm::translate(glm::mat4(), glm::vec3(translation, 0.0f)) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), 0.0f) * glm::scale(glm::mat4(), glm::vec3(scale, 1.0f)));
}

void Mesh2D::RotateX(float x)
{
	rotation.x = x;
}

void Mesh2D::RotateY(float y)
{
	rotation.y = y;
}

void Mesh2D::Rotate2f(float x, float y)
{
	rotation.x = x;
	rotation.y = y;
}

void Mesh2D::RotateVec2(glm::vec2 rot)
{
	rotation = rot;
}

void Mesh2D::RotateAdd2f(float x, float y)
{
	rotation.x += x;
	rotation.y += y;
}

void Mesh2D::RotateAddVec2(glm::vec2 rot)
{
	rotation += rot;
}

void Mesh2D::TranslateX(float x)
{
	translation.x = x;
}

void Mesh2D::TranslateY(float y)
{
	translation.y = y;
}

void Mesh2D::Translate2f(float x, float y)
{
	translation.x = x;
	translation.y = y;
}

void Mesh2D::TranslateVec2(glm::vec2 trans)
{
	translation = trans;
}

void Mesh2D::TranslateAdd2f(float x, float y)
{
	translation.x += x;
	translation.y += y;
}

void Mesh2D::TranslateAddVec2(glm::vec2 trans)
{
	translation += trans;
}

void Mesh2D::ScaleX(float x)
{
	scale.x = x;
}

void Mesh2D::ScaleY(float y)
{
	scale.y = y;
}

void Mesh2D::Scale2f(float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void Mesh2D::ScaleVec2(glm::vec2 s)
{
	scale = s;
}

void Mesh2D::ScaleAdd2f(float x, float y)
{
	scale.x += x;
	scale.y += y;
}

void Mesh2D::ScaleAddVec2(glm::vec2 s)
{
	scale += s;
}

glm::vec2 Mesh2D::GetTranslation()
{
	return translation;
}

glm::vec2 Mesh2D::GetRotation()
{
	return rotation;
}

glm::vec2 Mesh2D::GetScale()
{
	return scale;
}

ShapeData2D Mesh2D::GetShape()
{
	return shape;
}

void Mesh2D::SetShape(ShapeData2D newShape)
{
	shape = newShape;
}