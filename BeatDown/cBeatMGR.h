#pragma once
#include "cBkGround.h"

#include "OsuFileParser.h"
#include "cBeat.h"
#include "Mp3.h"



class BeatManager {
public:
	BeatManager();
	static BeatManager* getInstance();
	float time();
	void loadSongByPath(string path);
	float getSpeed(int offset);
	void playSong();
	void scheduleBeat(int offset, int column);
	void update(float elapsedTime);
	vector<cBeat*> beatsVector;
	bool isPlaying = false;

	Mp3 song;
	cBkGround background = NULL;
	cBkGround overlay = cBkGround("Images/OL.png");
private:
	static BeatManager* pInstance;

	
	float startTime = 0;
	cTexture* beatTexture;

	OsuFileData fileData;
	

	//Beat Positioning information:
	glm::vec2 playFieldSize = glm::vec2(820,600); 
	
};