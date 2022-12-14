#pragma once
#include<GLEW/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat ZOOM = 45.0f;
const GLfloat SPEED = 10.f;
const GLfloat SENSITIVITY = 0.05f;
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) :front(glm::vec3(0.0f, 0.0f
		, -1.0f)), zoom(ZOOM), speed(SPEED),sensitivity(SENSITIVITY)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
	}
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, position + front, up);

	}

	GLfloat GetZoom()
	{
		return this->zoom;
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = this->speed * deltaTime;
		if (direction == FORWARD) {
			this -> position += this -> front * velocity;
		}
		if (direction == BACKWARD) {
			this->position -= this->front * velocity;
		}
		if (direction ==RIGHT) {
			this->position += this->right * velocity;
		}
		if (direction ==LEFT) {
			this->position -= this->right * velocity;
		}
	}
	void ProcessMouseMove(GLfloat xOffset, GLfloat yOffset)
	{
		xOffset *= sensitivity;
		yOffset *= sensitivity;
		this->yaw += xOffset;
		this->pitch += yOffset;
		this->updataCameraVectors();
	}
private:
	glm::vec3 position, front, up, right;
	glm::vec3 worldUp;
	GLfloat yaw, pitch;
	GLfloat zoom;
	GLfloat speed, sensitivity;
	void updataCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
		front.y = sin(glm::radians(this->pitch));
		front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));


		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};