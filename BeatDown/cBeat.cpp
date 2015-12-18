/*
=================
cBeat.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBeat.h"

cBeat::cBeat(GLuint texture, int _offset, int _speed, int xpos, int ypos)
{
	offset = _offset;
	speed = _speed;
	setSpritePos( glm::vec2(xpos,ypos) );
	setSpriteTranslation(glm::vec2(0, speed));
	//Create the texture
	setTexture(texture);
	setTextureDimensions(beatTextureSize.x, beatTextureSize.y);
	setActive(true);
}	

void cBeat::render()
{
	if (getSpritePos().y < 0 || getSpritePos().y>800) return;
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
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

void cBeat::update(float currentOffset)
{

	float mult = float(offset) / 1000 - float(currentOffset) / 1000;

	float y = playFieldSize.y - float(speed)*mult;
	setSpritePos(glm::vec2(spritePos2D.x, y));
	setBoundingRect(&boundingRect);
	
	cPlayer* player = cPlayer::getInstance();
	int pLeft = player->getSpritePos().x - ((player->getBoundingRect().right - player->getBoundingRect().left) / 2);
	int pRight = player->getSpritePos().x + ((player->getBoundingRect().right - player->getBoundingRect().left) / 2);
	int nLeft = getSpritePos().x - ((getBoundingRect().right - getBoundingRect().left) / 2);
	int nRight = getSpritePos().x + ((getBoundingRect().right - getBoundingRect().left) / 2);


	if (y >= 650 && !passedPlayer) {
		if (nLeft >= pLeft && nRight <= pRight) { 
			//if the player's rectangle surrounds the beat completely, it's a full hit
			//Play the hitsound
			HitsoundManager::getInstance()->playSound(1);
			passedPlayer = true;
			//update score
			cPlayer::getInstance()->combo += 1;
			cPlayer::getInstance()->score += 300 * cPlayer::getInstance()->combo;
			cPlayer::getInstance()->comboAdded = "300!!";
			cPlayer::getInstance()->scoreAdded = "+" + to_string(300 * cPlayer::getInstance()->combo);
			setActive(false);
		}
		else if ((nLeft < pLeft && nRight > pLeft) || nRight > pRight && nLeft < pRight) { 
			//the player's rectangle only touches the beat. it's a partial hit. add 100*combo
			//Play the hitsound
			HitsoundManager::getInstance()->playSound(1);
			passedPlayer = true;

			cPlayer::getInstance()->combo += 1;
			cPlayer::getInstance()->score += 100 * cPlayer::getInstance()->combo;
			cPlayer::getInstance()->comboAdded = "100";
			cPlayer::getInstance()->scoreAdded = "+" + to_string(100 * cPlayer::getInstance()->combo);
			setActive(false);
		}
		else {

			cPlayer::getInstance()->combo = 0;
			cPlayer::getInstance()->comboAdded = "MISS!";
			cPlayer::getInstance()->scoreAdded = "";
			passedPlayer = true;
		}
	}

	
}