/*
=================
- cButton.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cButton.h"






/*
=================================================================
 Defualt Constructor
=================================================================
*/
cButton::cButton(glm::vec2 pos, string txt)
{

	buttonText = txt;
	m_InputMgr = cInputMgr::getInstance();

	applyTexture("Images/beat.png");
	setSpritePos(glm::vec2(pos.x, pos.y));
	setSpriteTexCoordData();
	spriteTranslation = glm::vec2(0.0f, 0.0f);
	spriteScaling = glm::vec2(1.0f, 1.0f);
	spriteRotation = 0.0f;
}
void cButton::applyTexture(LPCSTR path) {
	texture.createTexture(path);
	setTextureDimensions(texture.getTWidth(), texture.getTHeight());
	setTexture(texture.getTexture());
	setSpriteCentre();
}
void cButton::render()
{
	setSpriteCentre();

	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(0, 0);
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f(textureWidth, 0);
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f(textureWidth, textureHeight);
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(0, textureHeight);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//Render font
	cFontMgr::getInstance()->getFont("Button")->printTextCentred(buttonText.c_str(), FTPoint(spritePos2D.x + spriteCentre.x, spritePos2D.y + spriteCentre.y),glm::vec4(1,1,1,1));
}

///*
//=================================================================
//Update the sprite position
//=================================================================
//*/
//
void cButton::update(float dt)
{
	if (m_InputMgr->getLeftMouseBtn())
	{
		glm::vec2 areaClicked = m_InputMgr->getMouseXY();
		if (areaClicked.x >= spritePos2D.x && areaClicked.x <= (spritePos2D.x + textureWidth) && areaClicked.y >= spritePos2D.y && areaClicked.y <= (spritePos2D.y + textureHeight))
		{
			buttonClickedRC.x = (int)(areaClicked.x - spritePos2D.x) / textureWidth;
			buttonClickedRC.y = (int)(areaClicked.y - spritePos2D.y) / textureHeight;
			setClicked(true);
			//m_InputMgr->clearBuffers(m_InputMgr->MOUSE_BUFFER);// clear mouse buffer.
		}
		else {
			setClicked(false);
		}
	}
	else setClicked(false);
}

void cButton::setClicked(bool state) {
	clicked = state;
}
bool cButton::getClicked() {
	return clicked;
}

//Add a method to 
void cButton::setSelected(bool state) {
	if (state) applyTexture("Images/beatHighlight.png");
	else applyTexture("Images/beat.png");
	selected = state;
}
bool cButton::getSelected() {
	return selected;
}