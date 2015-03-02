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

#include <iostream>

enum PlayState {
	PLAY,
	STOP,
	ONCE,
	LOOP,
};

struct Frame {
	float x0, x1, y0, y1;
};

struct Animation {
	int startFrame, endFrame = 0;
	PlayState playType;
};

struct UVpoint2 {
	GLfloat U, V;
};

class SpriteAnimated {
public:
	SpriteAnimated();
	~SpriteAnimated();
	void initializeSprite(const char* texturePath, float a_x, float a_y, float a_width, float a_height);
	void Draw();
	void updateUVs();
	void makeBasicStructure(int a_numColumns, int a_numRows);
	void setFrame(int a_frame, float a_x0, float a_y0, float a_x1, float a_y1);
	void playFrame(int a_frame);
	void setAnimation(int a_anim, int a_start, int a_end, PlayState a_playtype);
	void playAnimation(int a_anim);
	void Update();

	float width, height, /*x, y,*/ sheetWidth, sheetHeight, fps, elapsedTime = 0;
	glm::vec2 position;
	int currentFrame = 0;
	PlayState playState = PLAY;
	UVpoint2 UVs[4];
	GLuint VBO, UVBO, EBO, VAO, VertexShader, FragmentShader, ShaderProgram, Texture;
	glm::mat4 MVP;
	Animation currentAnimation;
	Animation animations[16];
	Frame frames[256];
};