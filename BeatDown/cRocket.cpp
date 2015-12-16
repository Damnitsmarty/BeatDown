/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"

cRocket* cRocket::instance = NULL;


//constructor
cRocket::cRocket()
{
	texture.createTexture(texturePath);
	setTextureDimensions(160, texture.getTHeight());
	setSpritePos(glm::vec2(1280 / 2 , 650));
	setTexture(texture.getTexture());
}

cRocket* cRocket::getInstance() {
	if (instance == NULL) instance = new cRocket();
	return instance;
}


void cRocket::render()
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

void cRocket::update(float deltaTime)
{
	float x_change = 0;
	if (m_InputMgr->isKeyDown(VK_RIGHT) || m_InputMgr->isKeyDown(int('D')))
	{
		x_change += 10.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT) || m_InputMgr->isKeyDown(int('A')))
	{
		x_change -= 10.0f;
	}
	if (m_InputMgr->isKeyDown(VK_SHIFT) || m_InputMgr->isKeyDown(int('S')))
	{
		x_change *= 2;
	}
	spritePos2D += glm::vec2(x_change, 0);


	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	//for (vector<cBullet*>::iterator index = theRocketBullets.begin(); index != theRocketBullets.end(); ++index)
	//{
	//	for (vector<cBeat*>::iterator iter = beatsVector.begin(); iter != beatsVector.end(); ++iter)
	//	{
	//		if ((*iter)->collidedWith((*iter)->getBoundingRect(), (*index)->getBoundingRect()))
	//		{
	//			// if a collision set the bullet and asteroid to false
	//			(*iter)->setActive(false);
 //				(*index)->setActive(false);
	//		}
	//	}
	//}

//	vector<cBullet*>::iterator index = theRocketBullets.begin();
//	while( index != theRocketBullets.end())
//	{
//		if ((*index)->isActive() == false)
//		{
//			index = theRocketBullets.erase(index);
//		}
//		else
//		{
//			(*index)->update(deltaTime);
//			(*index)->render();
//			++index;
//		}
//	}
}
