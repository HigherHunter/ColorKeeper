#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input.h"

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLint GetBufferWidth() const { return bufferWidth; }
	GLint GetBufferHeight() const { return bufferHeight; }

	bool ShouldClose() const { return glfwWindowShouldClose(mainWindow); }
	void CloseWindow() const { glfwSetWindowShouldClose(mainWindow, GL_TRUE); }

	GLFWwindow* GetGlfwWindow() const { return mainWindow; }

	bool* GetKeys() { return keys; }
	bool* GetMouseButtons() { return mouseButtons; }
	GLfloat GetXChange();
	GLfloat GetYChange();
	GLfloat GetMouseXPos() { return xPos; }
	GLfloat GetMouseYPos() { return yPos; }

	void SwapBuffers() const { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];
	bool mouseButtons[2];

	GLfloat xPos, yPos, lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
	static void HandleMouseButton(GLFWwindow* window, int button, int action, int mode);
	Input* inputHandling;
};