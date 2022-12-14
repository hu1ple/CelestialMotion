#pragma once

#include<vector>
#include<stack>
#include<SOIL2/SOIL2.h>
#include <glm\gtc\matrix_transform.hpp>
#include"deltaTime.h"
#include"Camera.h"

float lastX, lastY;
bool fisrtMouse = true;//������һ֡���
const GLfloat  PI = 3.14159265358979323846f;

//������ݻ��ֳ�50X50������
const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;
std::stack<glm::mat4> mStack;
class Tutorial : public Window {
public:
	Tutorial()
	{
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	~Tutorial()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		//delete pshader;
	}
	inline void RenderScreen() override final
	{
		glfwPollEvents();//����GLFW������еȴ�������¼�����Ϣ����������ϵͳ�ʹ���ϵͳ��Ӧ���������Ϣ��
										//�������Ϣ���ڵȴ��������ȴ�����Щ��Ϣ�ٷ��أ�����ú������������ء�
		glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sunTexture = loadTexture("sun.jpg");
		earthTexture = loadTexture("earth.jpg");
		moonTexture = loadTexture("moon.jpg");

		this->colorShader->UseProgram();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		float timeValue = glfwGetTime();          //ʱ��
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 proj = glm::perspective(glm::radians(pCamera->GetZoom()),
			static_cast<float>(WINDOWWIDTH) / static_cast<float>(WINDOWHEIGHT), 0.1f, 100.0f);
		this->colorShader->SetMatrix4fv("proj", proj);
		glm::mat4 view = pCamera->GetViewMatrix();
		this->colorShader->SetMatrix4fv("view", view);

		mStack.push(glm::mat4(1.0f));
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		mStack.top() *= transform;
		mStack.push(mStack.top());

		mStack.top() *= glm::rotate(glm::mat4(1.0f), (float)timeValue, glm::vec3(0.0f, 1.0f, 0.0f)); // ̫����ת
		mStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));
		drawSphere(sunTexture);
		mStack.pop();//�Ƴ�̫����ת�����ţ�




		//���Ƶ���;
		mStack.push(mStack.top());
		mStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)timeValue) * 1.0f, 0.0f, cos((float)timeValue) * 1.0f)); // ����ת
		mStack.push(mStack.top());
		mStack.top() *= glm::rotate(glm::mat4(1.0f), (float)timeValue, glm::vec3(0.0f, 1.0f, 0.0f)); // ������ת
		mStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)); // ��������

		drawSphere(earthTexture);
		mStack.pop();// �����ջ���Ƴ�������ת������

		//��������
		mStack.push(mStack.top());
		mStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)timeValue) * 0.8f, cos((float)timeValue) * 0.8f)); // ����ת
		mStack.top() *= glm::rotate(glm::mat4(1.0f), (float)timeValue, glm::vec3(0.0f, 0.0f, 1.0f)); // ������ת
		mStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)); // ��������
		drawSphere(moonTexture);


		while (mStack.size())
			mStack.pop();

		glfwSwapBuffers(this->window);
		glfwPollEvents();

	}
	void initUI()
	{
		glfwSetKeyCallback(this->window, KeyCallback);
		glfwSetFramebufferSizeCallback(this->window, FramebufferSizeCallback);
		glfwSetCursorPosCallback(this->window, MouseCallback);
	}
	void CreateObjects()
	{
		//this->CreateTriangle();
		//this->CreateCube();
		CreateSphere();
	}
	void CreateShaders()
	{
		//pshader = new Shader("res/shaders/sphere.vs", "res/shaders/sphere.fs");
		colorShader = new Shader("res/shaders/sphereColor.vs", "res/shaders/sphereColor.fs");

	}

	bool IsWindowClosed()
	{
		return glfwWindowShouldClose(window);
	}

private:
	GLuint VAO;
	GLuint VBO;
	//Shader* pshader;
	Shader* colorShader;
	static bool keys[1024];
	static  std::unique_ptr<Camera> pCamera;
	GLuint sunTexture, earthTexture, moonTexture; // ����
	void CreateSphere()		//������Ķ�������
	{
		std::vector<float> sphereVertices;
		std::vector<int> sphereIndices;


		// ������Ķ���
		for (int y = 0; y <= Y_SEGMENTS; y++)
		{
			for (int x = 0; x <= X_SEGMENTS; x++)
			{
				float xSegment = (float)x / (float)X_SEGMENTS;
				float ySegment = (float)y / (float)Y_SEGMENTS;
				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
				float yPos = std::cos(ySegment * PI);
				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);


				sphereVertices.push_back(xPos);
				sphereVertices.push_back(yPos);
				sphereVertices.push_back(zPos);

				sphereVertices.push_back(ySegment);
				sphereVertices.push_back(xSegment);


			}
		}


		// �������Indices
		for (int i = 0; i < Y_SEGMENTS; i++)
		{
			for (int j = 0; j < X_SEGMENTS; j++)
			{

				sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
				sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
				sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);

				sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
				sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
				sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
			}
		}

		// ��
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		//���ɲ��������VAO��VBO
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// ���������ݰ�����ǰĬ�ϵĻ�����
		glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

		GLuint element_buffer_object; //EBO
		glGenBuffers(1, &element_buffer_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

		// ���ö�������ָ��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// - --------------

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//---------------------------------
		// ���VAO��VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
	void drawSphere(const GLuint& texture)
	{
		glm::mat4 mMat = mStack.top();
		this->colorShader->SetMatrix4fv("transform", mMat);
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_DEPTH_TEST); // ������Ȳ���
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE); // ��������������
		glFrontFace(GL_CCW);
		glDrawElements(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	GLuint loadTexture(const char* textImagePath) {
		GLuint textureID;
		textureID = SOIL_load_OGL_texture(textImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (textureID == 0)
			std::cout << "could not find texture file" << textImagePath << std::endl;
		return textureID;
	}


	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				keys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				keys[key] = false;
			}
		}
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
			pCamera->ProcessKeyboard(FORWARD, deltaTime);
		}
		if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
			pCamera->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
			pCamera->ProcessKeyboard(LEFT, deltaTime);
		}
		if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
			pCamera->ProcessKeyboard(RIGHT, deltaTime);
		}
	}
	static void FramebufferSizeCallback(GLFWwindow
		* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos)
	{
		GLfloat xOffset, yOffset;
		if (fisrtMouse)
		{
			lastX = xPos;
			lastY = yPos;
			fisrtMouse = false;
		}
		xOffset = xPos - lastX;
		yOffset = lastY - yPos;
		lastX = xPos;
		lastY = yPos;
		pCamera->ProcessMouseMove(xOffset, yOffset);
	}

};

std::unique_ptr<Camera> Tutorial::pCamera = std::unique_ptr<Camera>(new
	Camera(glm::vec3(0.0f, .0f, 5.0f)));
bool Tutorial::keys[1024] = { false };




