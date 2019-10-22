#pragma once

enum Mode
{
	scale, translate, rotate, cam, texture, output
};

enum EditorType
{
	text, overlay, scene, light
};

struct Texture
{
	std::string name;
	unsigned int id;
};