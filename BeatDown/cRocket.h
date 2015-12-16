/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"

class cRocket : public cSprite
{
private:
	LPCSTR texturePath = "Images/player.png";
	cTexture texture;
	static cRocket* instance;
public:
	cRocket();
	static cRocket* getInstance();
	
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method

};
#endif