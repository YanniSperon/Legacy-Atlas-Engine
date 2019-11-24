#pragma once

namespace LevelEditor {

	enum Mode
	{
		scale, translate, rotate, cam, texture
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
}