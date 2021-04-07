#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startWorldUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startWorldUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime, bool* allowedMovement)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		if (allowedMovement[0])
		{
			front = glm::normalize(glm::cross(worldUp, right));
			position += front * velocity;
		}
	}

	if (keys[GLFW_KEY_S])
	{
		if (allowedMovement[1])
		{
			front = glm::normalize(glm::cross(worldUp, right));
			position -= front * velocity;
		}
	}

	if (keys[GLFW_KEY_A])
	{
		if (allowedMovement[2])
			position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		if (allowedMovement[3])
			position += right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -50.0f)
		pitch = -50.0f;

	Update();
}

glm::mat4 Camera::CalculateViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

btVector3 Camera::GetBtV3CameraDirectionWorldUp() const
{
	const glm::vec3 frontWorldUp = glm::normalize(glm::cross(worldUp, right));
	return btVector3(frontWorldUp.x, frontWorldUp.y, frontWorldUp.z);
}

Camera::~Camera()
{
}