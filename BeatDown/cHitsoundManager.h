#pragma once
#include "GameConstants.h"
#include "Mp3.h"

class HitsoundManager {
public:
	HitsoundManager() ;
	static HitsoundManager* getInstance();
	void HitsoundManager::playSound(int sound);
private:
	static HitsoundManager* pInstance;
	vector<Mp3*> emitters;
	int currentSound = 0;
};