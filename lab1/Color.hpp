#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define RED_COLOR {1.0f, 0.0f, 0.0f, 1.0f}
#define GREEN_COLOR {0.0f, 1.0f, 0.0f, 1.0f}
#define BLUE_COLOR {0.0f, 0.0f, 1.0f, 1.0f}
#define BLACK_COLOR {0.0f, 0.0f, 0.0f, 1.0f}

struct Color {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;

	std::string toString() {
		return std::to_string(red) + "," +
			   std::to_string(green) + "," +
			   std::to_string(blue) + "," +
			   std::to_string(alpha);
	}
};