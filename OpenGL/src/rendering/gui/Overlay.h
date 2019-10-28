#pragma once
#include <vector>
#include "Renderer.h"
#include "Button.h"

class Overlay {
private:
	std::vector<Object2D*> objects2d;
	std::vector<Sentence*> text2d;
	std::vector<Button*> buttons;
public:
	Overlay();
	Overlay(std::vector<Object2D*> gui, std::vector<Sentence*> text, std::vector<Button*> button);
	~Overlay();

	void AddText(Sentence* sentence);
	void RemoveText(GLuint index, bool shouldDelete);
	void SetText(GLuint index, std::string text);
	void AddObject2D(Object2D* object);
	void RemoveObject2D(GLuint index, bool shouldDelete);
	void AddButton(Button* button);
	void RemoveButton(GLuint index, bool shouldDelete);
	void Submit(Renderer* renderer);
	void CheckTouches(double mouseX, double mouseY, int width, int height, bool isMousePressed);
};