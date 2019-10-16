#pragma once
#include <vector>
#include "GL/glew.h"

class Search {
public:
	static GLuint LinearSearchVector(std::vector<GLuint> &vec, GLuint value);
};