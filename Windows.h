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

		glfwMakeContextCurrent(window);//���ò���window�еĴ�����������OpenGL����Ϊ��ǰ��������������ڵ�ǰ
		//�߳��л�һֱ����Ϊ��ǰ������ֱ����һ������������Ϊ��ǰ���������ߴ��ڱ�ɾ��Ϊֹ��
		if (GLEW_OK != glewInit()) { ERROR_LOG("Failed to init glew") }

	}
protected:
	GLFWwindow* window;
};