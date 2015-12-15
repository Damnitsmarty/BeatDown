/*
================
cBkGround.h
- Header file for class definition - SPECIFICATION
- Header file for the Background class which is a child of cSprite class
=================
*/
#ifndef _CBKGROUND_H
#define _CBKGROUND_H
#include "cSprite.h"
#include "cTexture.h"

class cBkGround : public cSprite
{
	cTexture texture;
public:
	cBkGround(LPCSTR path);
	void render();		// Default render function
	void update(float deltaTime);		// Update method
};
#endif