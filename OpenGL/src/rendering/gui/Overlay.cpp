#include "Overlay.h"
#include "Console.h"

Overlay::Overlay()
{
	
}

Overlay::Overlay(std::vector<Object2D*> gui, std::vector<Sentence*> text, std::vector<Button*> button)
	: objects2d(gui), text2d(text), buttons(button)
{

}

Overlay::~Overlay()
{
	for (unsigned int i = 0; i < objects2d.size(); i++) {
		delete objects2d[i];
	}
	objects2d.clear();
	for (unsigned int i = 0; i < text2d.size(); i++) {
		delete text2d[i];
	}
	text2d.clear();
	for (unsigned int i = 0; i < buttons.size(); i++) {
		delete buttons[i];
	}
	buttons.clear();
}

void Overlay::AddText(Sentence* sentence)
{
	text2d.push_back(sentence);
}

void Overlay::RemoveText(GLuint index, bool shouldDelete)
{
	if (index >= 0) {
		if (index < text2d.size()) {
			if (shouldDelete) {
				delete text2d[index];
			}
			text2d.erase(text2d.begin() + index);
		}
		else {
			Console::Err("Cannot remove text at index " + std::to_string(index) + ". It is out of bounds!");
		}
	}
	else {
		Console::Err("Cannot remove text at index " + std::to_string(index) + ". It is negative!");
	}
}

void Overlay::SetText(GLuint index, std::string text)
{
	text2d[index]->SetText(text);
}

void Overlay::AddObject2D(Object2D* object)
{
	objects2d.push_back(object);
}

void Overlay::RemoveObject2D(GLuint index, bool shouldDelete)
{
	if (index >= 0) {
		if (index < objects2d.size()) {
			if (shouldDelete) {
				delete objects2d[index];
			}
			objects2d.erase(objects2d.begin() + index);
		}
		else {
			Console::Err("Cannot remove object at index " + std::to_string(index) + ". It is out of bounds!");
		}
	}
	else {
		Console::Err("Cannot remove object at index " + std::to_string(index) + ". It is negative!");
	}
}

void Overlay::AddButton(Button* button)
{
	buttons.push_back(button);
}

void Overlay::RemoveButton(GLuint index, bool shouldDelete)
{
	if (index >= 0) {
		if (index < buttons.size()) {
			if (shouldDelete) {
				delete buttons[index];
			}
			buttons.erase(buttons.begin() + index);
		}
		else {
			Console::Err("Cannot remove button at index " + std::to_string(index) + ". It is out of bounds!");
		}
	}
	else {
		Console::Err("Cannot remove button at index " + std::to_string(index) + ". It is negative!");
	}
}

void Overlay::Submit(Renderer* renderer)
{
	for (unsigned int i = 0; i < buttons.size(); i++) {
		renderer->Submit2D(buttons[i]);
	}
	for (unsigned int i = 0; i < objects2d.size(); i++) {
		renderer->Submit2D(objects2d[i]);
	}
	for (unsigned int i = 0; i < text2d.size(); i++) {
		renderer->SubmitText(text2d[i]);
	}
}

void Overlay::CheckTouches(double mouseX, double mouseY, int width, int height, bool isMousePressed)
{
	if (isMousePressed) {
		for (unsigned int i = 0; i < buttons.size(); i++) {
			buttons[i]->CheckPress(mouseX, mouseY, width, height);
		}
	}
}
