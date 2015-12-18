#pragma once
#include "cBkGround.h"

#include "OsuFileParser.h"
#include "cBeat.h"
#include "Mp3.h"



class BeatManager {
public:
	BeatManager();
	static BeatManager* getInstance();

	void loadSongByPath(string path);
	float getSpeed(int offset);
	void playSong();
	void scheduleBeat(int offset, int column);
	void update();


	vector<cBeat*> beatsVector;
	bool isPlaying = false;
	
	Mp3 song;
	cBkGround background = NULL;
	cBkGround overlay = cBkGround("Images/OL.png");

private:
	static BeatManager* pInstance;


	cTexture* beatTexture;
	OsuFileData fileData;
	

	
	
};