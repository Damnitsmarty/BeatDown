/*
================
cBkGround.h
- Header file for class definition - SPECIFICATION
- Header file for the Background class which is a child of cSprite class
=================
*/
#pragma once
#include "cSprite.h"
#include "cTexture.h"
#include "cFontMgr.h"
#include <functional>

static const glm::vec2 buttonSize = glm::vec2(240, 80);

class cButton : public cSprite
{

	string buttonText;
	bool clicked;
	bool selected;
	glm::vec2 buttonClickedRC;
	cTexture texture;
public:
	cButton(glm::vec2 pos, string txt);
	void applyTexture(LPCSTR path);
	void render();		// Default render function
	void update(float deltaTime);		// Update method
	void setClicked(bool state);
	bool getClicked();
	void setSelected(bool state);
	bool getSelected();
};