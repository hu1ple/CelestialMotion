// This code is to draw a triangle within the window. The code is using opengl programmable
// pipeline with Shader class. 
// Copyright by Rui @njupt.
// 2022.9

#include <iostream>
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Minicore.h"
#include "Windows.h"
#include "Tutorial.h"


int main()
{
	Tutorial tutorial;
	tutorial.InitWindow("Tutorial4");
	tutorial.initUI();
	tutorial.CreateObjects();
	tutorial.CreateShaders();
	float currentTime = 0.0f;
	float lastTime = 0.0f;
	//extern float deltaTime;
	while (!tutorial.IsWindowClosed())
	{
		tutorial.RenderScreen();
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		tutorial.RenderScreen();
	}

	return 0;
}