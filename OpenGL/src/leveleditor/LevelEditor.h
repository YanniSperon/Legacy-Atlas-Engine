#pragma once

#include <string>

namespace LevelEditor {

	enum Mode
	{
		scale, translate, rotate, cam, texture
	};

	enum EditorType
	{
		scene, light
	};

	struct Texture
	{
		std::string name;
		unsigned int id;
	};
}