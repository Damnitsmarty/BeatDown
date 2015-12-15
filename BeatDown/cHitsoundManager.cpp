#include "cHitsoundManager.h"

//Singleton get
HitsoundManager* HitsoundManager::pInstance = NULL;




HitsoundManager* HitsoundManager::getInstance() {
		if (pInstance == NULL) pInstance = new HitsoundManager();
		return pInstance;
	};


//Constructor
HitsoundManager::HitsoundManager(){
	//currentSound = 0;

	string path = "Audio/hitnormal.wav";
	//Add 5 sounds to the vector
	for (int i = 0; i < 5; i++) {
		//Create the sound and load it
		Mp3* temp = new Mp3();
		temp->Load(wstring(path.begin(), path.end()).c_str());

		//The first time a sound is played there is a small freeze
		//Play every sound when created, so it does not freeze the game during gameplay
		temp->Play();
		//add the sound to the vector
		emitters.push_back(temp);
	}
}



void HitsoundManager::playSound(int sound){
		//ensure currentSound is always within the vector size limits
		currentSound = currentSound % emitters.size();

		//Preload the next hitsound by setting its position to 0
		Mp3* nextSound;
		if (currentSound == emitters.size() - 1) nextSound = emitters[0];
		else nextSound = emitters[currentSound + 1];

		long long pos = 0, dur = nextSound->GetDuration();
		nextSound->SetPositions(&pos, &dur, true);

		//Play the current sound
		emitters[currentSound]->Play();

		currentSound++; //increment the counter
	}


