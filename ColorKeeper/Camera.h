#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "btBulletDynamicsCommon.h"
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startWorldUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void KeyControl(bool* keys, GLfloat deltaTime, bool* allowedMovement);
	void MouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 GetCameraPosition() const { return position; };
	btVector3 GetBtV3CameraPosition() const { return btVector3(position.x, position.y, position.z); }

	glm::vec3 GetCameraDirection() const { return glm::normalize(front); }
	btVector3 GetBtV3CameraDirection() const { return btVector3(front.x, front.y, front.z).normalize(); };
	btVector3 GetBtV3CameraDirectionWorldUp() const;

	glm::vec3 GetCameraRight() const { return glm::normalize(right); }
	btVector3 GetBtV3CameraRight() const { return btVector3(right.x, right.y, right.z).normalize(); };

	void SetCameraPosition(const glm::vec3& pos) { position = pos; }
	void SetCameraPitch(const float& pitch) { this->pitch = pitch; }
	void SetCameraYaw(const float& yaw) { this->yaw = yaw; }

	glm::mat4 CalculateViewMatrix() const;

	~Camera();

private:
	glm::vec3 position, front, up, right, worldUp;

	GLfloat yaw, pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void Update();
};