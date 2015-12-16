#include "cBeatMGR.h"
#include "cWNDManager.h"

BeatManager* BeatManager::pInstance = NULL;

//Constructor
BeatManager::BeatManager()
{
	beatTexture = new cTexture();
	beatTexture->createTexture("Images\\beat.png");



}
//Singleton get
BeatManager* BeatManager::getInstance()
{
	if (pInstance == NULL) pInstance = new BeatManager();

	return pInstance;
}


float BeatManager::time() {
	float curtime = float(GetTickCount()) / 1000.0f;
	return curtime - startTime;
}

void BeatManager::loadSongByPath(string path) {

	fileData = OsuFileParser::parseFile(path);
	//TODO: return if data is invalid
	for (int i = 0; i < fileData.beats.size(); i++) {
		//Osu's xpos ranges from 0 to 512; calculate our xpos based on that and the playFieldSize 
		int xpos = (float(fileData.beats[i].x) / 512) * (playFieldSize.x - beatTextureSize.x);

		scheduleBeat(fileData.beats[i].offset, xpos);
	}

	song.Load(wstring(fileData.audioPath.begin(), fileData.audioPath.end()).c_str());
	background = cBkGround(fileData.backgroundPath.c_str());
	playSong();
}

float BeatManager::getSpeed(int offset) {
	if (fileData.timingPoints.size() < 1) return NULL;			// break if fileData does not exist or does not have any timing points

	float ret = NULL;											// this is the return variable

	
	for (int i = 0; i < fileData.timingPoints.size(); i++) {	// loop through the sorted timing points
		if (fileData.timingPoints[i].offset <= offset) {		// and find the one nearest to the given offset
			ret = fileData.timingPoints[i].msperbeat;
		}
		else return ret*1.5;										// no need to search through the rest of the items as they are sorted
	}
	return ret*1.5;													// make sure to return the last value if it's reached
}

void BeatManager::playSong() {
	
	
	startTime = time();
	isPlaying = song.Play();
}


void BeatManager::scheduleBeat(int offset, int xpos) {
	float xOffset = (1280 - playFieldSize.x) / 2;	// calculate initial offset
	//xpos += (column - 1)*columnoffset + column*beatTextureSize.x;							// then account for column size & offset
	xOffset += beatTextureSize.x / 2;

	float of = float(offset) / 1000;
	float sp = getSpeed(offset);
	float ypos = playFieldSize.y - of * sp;
	ypos -= sp * fileData.audioLeadIn/1000;

	cBeat* newBeat = new cBeat(beatTexture->getTexture(), offset, getSpeed(offset), xOffset+xpos,ypos);	// create the beat

	beatsVector.push_back(newBeat);															// and add it to the queue
}

void BeatManager::update() {
	background.render();
	overlay.render();
	if (!isPlaying) return;										// break if the song isn't playing
	float offset = float(song.GetCurrentPosition()) / 10000;	// get the time since the start of the song (offset)

	vector<cBeat*>::iterator index = beatsVector.begin();		// iterate over the beats queue
	while (index != beatsVector.end()) {

		if ((*index)->isActive() == false) {					// if the beat is not activated (yet)
			
		}
		else {													// if the beat is activated
			(*index)->update(offset);						//  update its position
			(*index)->render();
		}
		++index;
	}
}



