#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
//GLEW includes must precede anything else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <SOIL.h>

#include "FrameWork.h"

struct UVpoint {
	GLfloat U, V;
};

class Sprite {
public:
	Sprite();
	~Sprite();
	void initializeSprite(const char* texturePath, float a_x, float a_y, float a_width, float a_height);
	void Draw();
	void updateUVs();

	bool initialized = false;
	float width, height, x, y, sheetWidth, sheetHeight;
	UVpoint UVs[4];
	GLuint VBO, UVBO, EBO, VAO, VertexShader, FragmentShader, ShaderProgram, Texture;
	glm::mat4 MVP;
};