#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
//GLEW includes must precede anything else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <SOIL.h>
#include <iostream>

class FrameWork {
public:
	FrameWork();
	~FrameWork();

	void Orthograghic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);

	static GLFWwindow* window;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint fragmentShaderTextured;
	static GLuint shaderProgram, shaderProgramTextured;
	static int screenWidth, screenHeight;
	static glm::mat4 Ortho;
	static bool getKeyPressed(GLuint a_key);
};

//float deltaTime;

float getDeltaTime();
void resetTime();