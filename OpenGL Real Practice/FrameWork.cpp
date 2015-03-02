#pragma once

#include "FrameWork.h"

GLFWwindow* FrameWork::window;
GLuint FrameWork::shaderProgram;
GLuint FrameWork::shaderProgramTextured;
int FrameWork::screenHeight = 400;
int FrameWork::screenWidth = 800;
glm::mat4 FrameWork::Ortho;

FrameWork::FrameWork() {
	//Start GLFW #########
	glfwInit();
	//Set GLFW Window settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//Create Window
	window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	glfwMakeContextCurrent(window);
	//Start GLEW ##########
	glewExperimental = GL_TRUE;
	glewInit();
	//Other GL things #########
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Shaders #########
	//Shader Copilation #########
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexSource =
		"#version 430\n"
		"layout(location = 0) in vec2 position;"
		"layout(location = 1) in vec4 colorIn;"
		"layout(location = 2) in vec2 UVIn;"
		"out vec4 colorOut;"
		"out vec2 UVOut;"
		"void main(){"
		"	colorOut = colorIn;"
		"	UVOut = UVIn;"
		"	gl_Position = vec4(position, 0.0, 1.0);"
		"}";
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	{
		GLint status;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		printf(buffer);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSource =
		"#version 430\n"
		"in vec4 colorOut;"
		"in vec2 UVOut;"
		"out vec4 outColor;"
		"uniform sampler2D tex;"
		"void main(){"
		//"	outColor = texture(tex, UVOut) * vec4(colorOut);"
		"	outColor = vec4(colorOut);"
		"}";
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	{
		GLint status;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		printf(buffer);
	}
	fragmentShaderTextured = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSourceTextured =
		"#version 430\n"
		"in vec2 UVOut;"
		"out vec4 outColor;"
		"uniform sampler2D tex;"
		"void main(){"
		"	outColor = texture(tex, UVOut);"
		"}";
	glShaderSource(fragmentShaderTextured, 1, &fragmentSourceTextured, NULL);
	glCompileShader(fragmentShaderTextured);
	{
		GLint status;
		glGetShaderiv(fragmentShaderTextured, GL_COMPILE_STATUS, &status);
		char buffer[512];
		glGetShaderInfoLog(fragmentShaderTextured, 512, NULL, buffer);
		printf(buffer);
	}
	//Build Program 1
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//Build Program 2
	shaderProgramTextured = glCreateProgram();
	glAttachShader(shaderProgramTextured, vertexShader);
	glAttachShader(shaderProgramTextured, fragmentShaderTextured);
	glLinkProgram(shaderProgramTextured);
	//Texture Settings
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Orthograghic(0, screenWidth, screenHeight, 0, -1, 1, Ortho);
}
FrameWork::~FrameWork() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glfwTerminate();
}


void FrameWork::Orthograghic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat) {
	float deltaX = a_fRight - a_fLeft;
	float deltaY = a_fTop - a_fBottom;
	float deltaZ = a_fNear - a_fFar;

	mat[0].x = 2.f / deltaX;
	mat[0].y = 0.f;
	mat[0].z = 0.f;
	mat[0].w = 0.f;

	mat[1].x = 0.f;
	mat[1].y = 2.f / deltaY;
	mat[1].z = 0.f;
	mat[1].w = 0.f;

	mat[2].x = 0.f;
	mat[2].y = 0.f;
	mat[2].z = 2.f / deltaZ;
	mat[2].w = 0.f;

	mat[3].x = ((a_fLeft + a_fRight) / (a_fLeft - a_fRight));
	mat[3].y = ((a_fBottom + a_fTop) / (a_fBottom - a_fTop));
	mat[3].z = (-(a_fNear + a_fFar) / (a_fFar - a_fNear));
	mat[3].w = 1.f;
}

bool FrameWork::getKeyPressed(GLuint a_key) {
	return glfwGetKey(window, a_key) == GLFW_PRESS;
}

float deltaTime = 0;

float getDeltaTime() {
	return deltaTime;
}

void resetTime() {
	deltaTime = glfwGetTime();
	glfwSetTime(0);
}