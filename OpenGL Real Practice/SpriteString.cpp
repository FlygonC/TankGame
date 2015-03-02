#pragma once

#include "SpriteString.h"

SpriteString::SpriteString() {}

SpriteString::~SpriteString() {}

void SpriteString::InitializeString(const char* a_input, const char* a_FontPath, float a_x, float a_y, float a_scale) {
	for (int i = 0; i < strlen(a_input) +1 ; i++) {
		input[i] = a_input[i];
	}
	//FontPath = a_FontPath;
	x = a_x;
	y = a_y;
	scale = a_scale;

	output.initializeSprite(a_FontPath, x, y, scale, scale);
	output.makeBasicStructure(16, 16);
}

void SpriteString::Draw() {
	//int testLength = strlen(input);
	int i = 0;
	while (input[i] != '\0') {
		output.position = glm::vec2(x + i*(scale), y);
		//output.x = x+i*(scale);
		//output.y = y;

		output.playFrame(input[i]);
		output.Draw();
		i++;
	}
}

void SpriteString::changeInput(const char* a_input) {
	for (int i = 0; i < strlen(a_input) + 1; i++) {
		input[i] = a_input[i];
	}
}