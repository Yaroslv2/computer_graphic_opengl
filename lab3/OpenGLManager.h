#pragma once

#include <string>

class OpenGLManager
{
public:
	static OpenGLManager& getInstanse();

	/// <summary>
	/// Initialize OpenGL libs
	/// </summary>
	/// <returns>true - libs was initialized, false - something went wrong</returns>
	bool init();

	/// <summary>
	/// set callbacks
	/// </summary>
	void setCallbacks();

	/// <summary>
	/// loading shaders
	/// </summary>
	/// <returns></returns>
	std::string loadShader(const char* filename);
private:
	static OpenGLManager instanse;
	OpenGLManager();
};

