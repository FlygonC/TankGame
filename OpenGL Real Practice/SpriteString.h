#pragma once

#include "SpriteAnimated.h"
#include <String.h>

#include "FrameWork.h"

class SpriteString {
public:
	SpriteString();
	~SpriteString();
	void InitializeString(const char* a_input, const char* a_FontPath, float a_x, float a_y, float a_scale);
	void Draw();
	void changeInput(const char* a_input);

	char input[256];
	//const char* FontPath;
	SpriteAnimated output;
	float scale, x, y;
};