#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
//GLEW includes must precede anything else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "FrameWork.h"

class Quad {
public:
	Quad();
	~Quad();
	void Draw();

	GLuint VBO, EBO, VAO, VertexShader, FragmentShader, ShaderProgram;
	glm::mat4 MVP;
};