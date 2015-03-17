#pragma once

#include "Sprite.h"

Sprite::Sprite() {
	//Shader Sources
	const char* vertexShaderSource =
		"#version 430\n"
		"layout(location = 0) in vec3 position;"
		//"layout(location = 1) in vec4 color;"
		"layout(location = 1) in vec2 texCoords;"
		"uniform mat4 MVPmatrix;"
		//"out vec4 vColor;"
		"out vec2 UVs;"
		"void main() {"
		//"	vColor = color;"
		"	UVs = texCoords;"
		"	gl_Position = MVPmatrix * (vec4(position, 1.0));"
		"}";
	const char* fragmentShaderSource =
		"#version 430\n"
		//"in vec4 vColor;"
		"in vec2 UVs;"
		"out vec4 outColor;"
		"uniform sampler2D tex;"
		"void main() {"
		"	outColor = texture(tex, UVs) * (vec4(1.0, 1.0, 1.0, 1.0));"
		//"	outColor = vec4(1.0,1.0,1.0,1.0);"
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
	//Vertex Data
	GLfloat points[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	//UV Data
	UVs[0].U = 0;
	UVs[0].V = 1;//
	UVs[1].U = 1;
	UVs[1].V = 1;//
	UVs[2].U = 0;
	UVs[2].V = 0;//
	UVs[3].U = 1;
	UVs[3].V = 0;//
//	//Gen Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);//Open Vertex Array
//	//Gen Vertex buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//Bind VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//	//Attribute Pointers: Verticies
	GLuint posAttrib = glGetAttribLocation(ShaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 3, 0);
//	//Gen UV buffer
	glGenBuffers(1, &UVBO);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);//Bind UVBO, VBO unbound
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
//	//Attribute Pointers: UVs
	GLuint UVAttrib = glGetAttribLocation(ShaderProgram, "texCoords");
	glEnableVertexAttribArray(UVAttrib);
	glVertexAttribPointer(UVAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 2, 0);
//	//Element buffer
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint elements[] = { 0, 1, 2, 3 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//	//Build MVP Matrix
	glm::mat4 viewTranslate = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	glm::mat4 Model = glm::scale(glm::mat4(), glm::vec3(0, 0, 1));

	MVP = FrameWork::Ortho * viewTranslate * Model;
//	//Unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//Unbind elements
	glBindBuffer(GL_ARRAY_BUFFER, 0);//Unbind all buffers, VBO and UVBO
	glBindVertexArray(0);//Close Vertex Array
}

Sprite::~Sprite() {
	glDeleteProgram(ShaderProgram);
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
}

void Sprite::initializeSprite(const char* texturePath, float a_x, float a_y, float a_width, float a_height) {
	x = a_x;
	y = a_y;
	width = a_width;
	height = a_height;

	//glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image(texturePath, &texWidth, &texHeight, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	sheetWidth = texWidth; sheetHeight = texHeight;
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	initialized = true;
}

void Sprite::Draw() {
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// hardcode active texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//GLint uniTexture = glGetUniformLocation(ShaderProgram, "tex");
	//glUniform1f(uniTexture, 0);

	glm::mat4 viewTranslate = glm::translate(glm::mat4(), glm::vec3(x, y, 0));
	glm::mat4 Model = glm::scale(glm::mat4(), glm::vec3(width, height, 1));
	//    ________________
	MVP = FrameWork::Ortho * viewTranslate * Model;

	GLuint mv_location = glGetUniformLocation(ShaderProgram, "MVPmatrix");
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(MVP));

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::updateUVs() {
	glBindVertexArray(VAO);//Open Vertex Array

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);//Bind UVBO, VBO unbound
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}