/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBkGround.h"

cBkGround::cBkGround(LPCSTR path)
{
	texture.createTexture(path);
	
	float ratio = float(texture.getTWidth()) / float(texture.getTHeight());
	if (800 * ratio >= 1280) {
		float actualHeight = 800;
		float actualWidth = actualHeight * ratio;
		
		setTextureDimensions(actualWidth, actualHeight);
		setSpritePos(glm::vec2(640 - int(actualWidth / 2), 400 - int(actualHeight / 2)));
	}
	else {
		float actualWidth = 1280;
		float actualHeight = actualWidth / ratio;

		setTextureDimensions(actualWidth, actualHeight);
		setSpritePos(glm::vec2(640 - int(actualWidth / 2), 400 - int(actualHeight / 2)));
	}

	
	setTexture(texture.getTexture());
	//setTextureDimensions(1280, 800);
	//setTextureDimensions(texture.getTWidth(), texture.getTHeight());
	
}

void cBkGround::render()
{
	cSprite::render();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBkGround::update(float deltaTime)
{
}
