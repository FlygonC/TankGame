#pragma once

#include "SpriteAnimated.h"

SpriteAnimated::SpriteAnimated() {
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

SpriteAnimated::~SpriteAnimated() {
	glDeleteProgram(ShaderProgram);
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
}

void SpriteAnimated::initializeSprite(const char* texturePath, float a_x, float a_y, float a_width, float a_height) {
	position = glm::vec2(a_x, a_y);
	//x = a_x;
	//y = a_y;
	width = a_width;
	height = a_height;

	/*for (int i = 0; i < 128; i++) {
		frames[i].x0 = 0;
		frames[i].x1 = 0;
		frames[i].y0 = 0;
		frames[i].y1 = 0;
	}*/
	currentFrame = 0;
	currentAnimation = animations[0];
	fps = 10;

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
}

void SpriteAnimated::Draw() {
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// hardcode active texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	GLint uniTexture = glGetUniformLocation(ShaderProgram, "tex");
	glUniform1f(uniTexture, 0);

	glm::mat4 viewTranslate = glm::translate(glm::mat4(), glm::vec3(position.x, position.y, 0));
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

void SpriteAnimated::updateUVs() {
	glBindVertexArray(VAO);//Open Vertex Array

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);//Bind UVBO, VBO unbound
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteAnimated::makeBasicStructure(int a_numColumns, int a_numRows) {
	for (int i = 0; i < a_numRows; i++) {
		for (int j = 0; j < a_numColumns; j++) {
			/*frames[(i*a_numColumns) + j].x0 = (sheetWidth / a_numColumns)*j;
			frames[(i*a_numColumns) + j].x1 = (sheetWidth / a_numColumns)*j + (sheetWidth / a_numColumns);

			frames[(i*a_numColumns) + j].y0 = (sheetHeight / a_numRows)*i;
			frames[(i*a_numColumns) + j].y1 = (sheetHeight / a_numRows)*i + (sheetHeight / a_numRows);*/
			setFrame((i*a_numColumns) + j, 
				(sheetWidth / a_numColumns)*j,  
				(sheetHeight / a_numRows)*i, 
				(sheetWidth / a_numColumns)*j + (sheetWidth / a_numColumns),
				(sheetHeight / a_numRows)*i + (sheetHeight / a_numRows));
		}
	}
}

void SpriteAnimated::setFrame(int a_frame, float a_x0, float a_y0, float a_x1, float a_y1) {
	frames[a_frame].x0 = a_x0;
	frames[a_frame].x1 = a_x1;
	frames[a_frame].y0 = a_y0;
	frames[a_frame].y1 = a_y1;
}

void SpriteAnimated::playFrame(int a_frame) {
	UVs[0].U = frames[a_frame].x0 / sheetWidth;
	UVs[0].V = frames[a_frame].y1 / sheetHeight;//up left
	UVs[1].U = frames[a_frame].x1 / sheetWidth;
	UVs[1].V = frames[a_frame].y1 / sheetHeight;//up right
	UVs[2].U = frames[a_frame].x0 / sheetWidth;
	UVs[2].V = frames[a_frame].y0 / sheetHeight;//down left
	UVs[3].U = frames[a_frame].x1 / sheetWidth;
	UVs[3].V = frames[a_frame].y0 / sheetHeight;//down right
	updateUVs();
}

void SpriteAnimated::setAnimation(int a_anim, int a_start, int a_end, PlayState a_playtype) {
	animations[a_anim].startFrame = a_start;
	animations[a_anim].endFrame = a_end;
	animations[a_anim].playType = a_playtype;
}

void SpriteAnimated::playAnimation(int a_anim) {
	currentAnimation = animations[a_anim];
	currentFrame = currentAnimation.startFrame;
}

void SpriteAnimated::Update() {
	/*switch (playState) {
	case PLAY:
	}*/
	if (playState == PLAY && currentAnimation.playType != STOP) {
		elapsedTime += getDeltaTime();
	}

	while (elapsedTime >= 1 / fps) {
		currentFrame++;
		elapsedTime -= 1 / fps;
		if (currentFrame > currentAnimation.endFrame) {
			switch (currentAnimation.playType) {
			case ONCE:
				currentFrame = currentAnimation.endFrame;
				break;
			case LOOP:
			//default:
				currentFrame -= (currentAnimation.endFrame + 1) - currentAnimation.startFrame;
				break;
			}
		}
		playFrame(currentFrame);
	}
}