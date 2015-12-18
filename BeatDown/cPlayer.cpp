/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayer.h"

cPlayer* cPlayer::instance = NULL;


//constructor
cPlayer::cPlayer()
{
	//Create the texture and update the sprite's position, dimensions and bounding rect
	texture.createTexture(texturePath);
	setTextureDimensions(180, texture.getTHeight());
	setSpritePos(glm::vec2(1280 / 2 , 650+texture.getTHeight()/2));
	setTexture(texture.getTexture());
	setBoundingRect(&boundingRect);
}

cPlayer* cPlayer::getInstance() {
	if (instance == NULL) instance = new cPlayer();
	return instance;
}


void cPlayer::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayer::update(float deltaTime)
{
	float x_change = 0;
	if (m_InputMgr->isKeyDown(VK_RIGHT) || m_InputMgr->isKeyDown(int('D')))
	{
		x_change += 15.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT) || m_InputMgr->isKeyDown(int('A')))
	{
		x_change -= 15.0f;
	}
	if (m_InputMgr->isKeyDown(VK_SHIFT) || m_InputMgr->isKeyDown(VK_SPACE) || m_InputMgr->isKeyDown(int('S')))
	{
		x_change *= 2;
	}
	setSpritePos(glm::vec2(getSpritePos().x + x_change, getSpritePos().y));
	setBoundingRect(&boundingRect);

}
