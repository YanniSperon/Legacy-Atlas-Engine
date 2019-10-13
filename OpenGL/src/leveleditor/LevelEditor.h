#pragma once

enum Mode
{
	scale, translate, rotate, cam, texture, output
};

struct Texture
{
	std::string name;
	unsigned int id;
};