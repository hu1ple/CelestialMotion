#pragma once

#include <glfw/glfw3.h>
#include <iostream>
#include "Minicore.h"
// Base abstract class for window creation
class Window {
public:

	virtual void RenderScreen() = 0;
	void InitWindow(const char* title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
#endif // __APPLE__
		window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, title, NULL, NULL);
		if (window == NULL) { ERROR_LOG("Failed to create Window!") }

		glfwMakeContextCurrent(window);//设置参数window中的窗口所关联的OpenGL环境为当前环境。这个环境在当前
		//线程中会一直保持为当前环境，直到另一个环境被设置为当前环境，或者窗口被删除为止。
		if (GLEW_OK != glewInit()) { ERROR_LOG("Failed to init glew") }

	}
protected:
	GLFWwindow* window;
};