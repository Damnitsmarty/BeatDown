#pragma once
#include "cSprite.h"

static glm::vec2 beatTextureSize = glm::vec2(120,40);

class cBeat : public cSprite
{
public:
		// texture size is public because BeatMGR uses it

	int offset = 0;
	float speed = 0;
	cBeat(GLuint texture, int _offset, int _speed, int xpos, int ypos);
	void render();											// GL render function
	void update(float currentOffset);							// Beat update method
private:
	bool soundPlayed = false;
};