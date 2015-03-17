#pragma once

#include "Quad.h"
#include <iostream>

Quad::Quad() {
	//Shader Sources
	const char* vertexShaderSource =
		"#version 430\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec4 color;"
		//"layout(location = 2) in;"
		"uniform mat4 MVPmatrix;"
		"out vec4 vColor;"
		"void main() {"
		"	vColor = color;"
		"	gl_Position = MVPmatrix * (vec4(position, 1.0));"
		"}";
	const char* fragmentShaderSource =
		"#version 430\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"void main() {"
		"	outColor = vColor;"
		"}";
	//Compile Vertex
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertexShader);
	{
		GLint status;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &status);
		char buffer[512];
		glGetShaderInfoLog(VertexShader, 512, NULL, buffer);
		printf(buffer);
	}
	//Compile Fragment
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	{
		GLint status;
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &status);
		char buffer[512];
		glGetShaderInfoLog(FragmentShader, 512, NULL, buffer);
		printf(buffer);
	}
	//Build Program
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, FragmentShader);
	glAttachShader(ShaderProgram, VertexShader);
	glLinkProgram(ShaderProgram);

	glUseProgram(ShaderProgram);

	GLfloat points[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0,
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0
	};
	//Gen Vertex buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//Gen Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Attribute Pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 7, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 7, (void*)(sizeof(float)* 3));
	//Element buffer
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint elements[] = { 0,1, 2, 3 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	//Build MVP Matrix
	glm::mat4 viewTranslate = glm::translate(glm::mat4(), glm::vec3(400, 400, 0));
	glm::mat4 Model = glm::scale(glm::mat4(), glm::vec3(50,50,1));

	MVP = FrameWork::Ortho * viewTranslate * Model;
	//Unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Quad::~Quad(){
	glDeleteProgram(ShaderProgram);
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
}

void Quad::Draw(){
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint mv_location = glGetUniformLocation(ShaderProgram, "MVPmatrix");
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(MVP));
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}