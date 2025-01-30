#include "Vase.h"

Vase::Vase(Shader shader) : Drawable((GLuint)GL_TRIANGLES, shader)
{
	loadModelFromFile("./Models/18390_Chinese_Porcelain_Bottle_Vase_v1.obj");
	for (int i = 0; i < vertexes.size(); i++) {
		colors.push_back({ 0.502f, 0.502f, 0.502f });
	}
	setColors(colors.data(), colors.size());
}
