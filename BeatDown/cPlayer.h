/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#pragma once
#include "cSprite.h"

class cPlayer : public cSprite
{
private:
	LPCSTR texturePath = "Images/player.png";
	cTexture texture;
	static cPlayer* instance;
public:
	cPlayer();
	static cPlayer* getInstance();
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	long int score = 0;
	string scoreAdded = "";
	string comboAdded = "";
	int combo = 0;
};