#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cFontMgr.h"
#include "cBeatMGR.h"
#include "cHitsoundMGR.h"
#include "cButton.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1280;
	const int windowHeight = 800;
	const int windowBPP = 16;

	enum GameState { MENU, PLAYING, SCORE };
	GameState gstate = GameState::MENU;



	//This is our window
	static cWNDManager* WindowManager = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* Input = cInputMgr::getInstance();

	// Load Font manager and fonts
	static cFontMgr* FontManager = cFontMgr::getInstance();
	FontManager->addFont("Regular", LPCSTR("Fonts/Aller_Rg.ttf"), 96);
	FontManager->addFont("Light", LPCSTR("Fonts/Aller_Lt.ttf"), 48);
	FontManager->addFont("Button", LPCSTR("Fonts/Aller_Lt.ttf"), 20);

	//The example OpenGL code
	windowOGL OGL;

	//Attach OGL & Managers
	WindowManager->attachOGLWnd(&OGL);
	WindowManager->attachInputMgr(Input);

	//Attempt to create the window
	if (!WindowManager->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		WindowManager->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!OGL.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		WindowManager->destroyWND(); //Reset the display and exit
		return 1;
	}

	//Clear key buffers
	Input->clearBuffers(Input->KEYS_DOWN_BUFFER | Input->KEYS_PRESSED_BUFFER);



	//initialize the Hitsound manager
	//it is only used by cBeat.cpp, so it is not needed as a variable
	HitsoundManager::getInstance();

	cPlayer* thePlayer = cPlayer::getInstance();
	static BeatManager* beatMGR = BeatManager::getInstance();
	


	cBkGround menuOverlay = cBkGround("Images/mainMenu.png");
	cBkGround menuBkg = NULL;
	string diffList[4] = { "easy.osu","normal.osu","hard.osu", "insane.osu" };
	string songlist[5][2] = {
		{ "Baracuda - La Di Da", "Songs/Baracuda - La Di Da (Nightcore Mix)/" } ,
		{ "Kitsune^2-Rainbow Tylenol", "Songs/Kitsune^2 - Rainbow Tylenol/" } ,
		{ "P-Light - TRIGGER-HAPPY", "Songs/P-Light - TRIGGER-HAPPY/" } ,
		{ "Noisestorm - Solar", "Songs/Noisestorm - Solar/" } ,
		{ "LeaF - Calamity Fortune", "Songs/LeaF - Calamity Fortune/" } };
	int selectedSong = 0;
	int selectedDiff = 0;

	vector<cButton*> songBtns;
	for (int i = 0; i < 5;i++) 	songBtns.push_back(new cButton(glm::vec2(10, 115 + (i)*(buttonSize.y + 10)), songlist[i][0]));

	vector<cButton*> diffBtns;
	diffBtns.push_back(new cButton(glm::vec2(1280 - (buttonSize.x + 20), 115+ diffBtns.size()*(buttonSize.y + 10)), "Easy"));
	diffBtns.push_back(new cButton(glm::vec2(1280 - (buttonSize.x + 20), 115+ diffBtns.size()*(buttonSize.y + 10)), "Normal"));
	diffBtns.push_back(new cButton(glm::vec2(1280 - (buttonSize.x + 20), 115+ diffBtns.size()*(buttonSize.y + 10)), "Hard"));
	diffBtns.push_back(new cButton(glm::vec2(1280 - (buttonSize.x + 20), 115 + diffBtns.size()*(buttonSize.y + 10)), "Insane"));
	
	cButton* startBtn = new cButton(glm::vec2(1280 - (buttonSize.x + 20), 800 - (buttonSize.y + 20)), "Play!");
	cButton* replayBtn = new cButton(glm::vec2(1280 - (buttonSize.x + 20), 800 - 2* (buttonSize.y + 20)), "Replay");
	cButton* backBtn = new cButton(glm::vec2(1280 - (buttonSize.x + 20), 800 - (buttonSize.y + 20)), "Main Menu");


	//select the first song and load its background
	songBtns[0]->setSelected(true);
	diffBtns[0]->setSelected(true);
	OsuFileData fd = OsuFileParser::parseFile(songlist[selectedSong][1] + "easy.osu");
	menuBkg = cBkGround(fd.backgroundPath.c_str());

	//This is the mainloop, we render frames until isRunning returns false
	while (WindowManager->isWNDRunning())
    {
		WindowManager->processWNDEvents(); //Process any window events
			
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (gstate == GameState::MENU) {
			
			

			//render the menu and overlay
			menuBkg.render();
			menuOverlay.render();

			//render the song buttons
			for (int i = 0; i < songBtns.size(); i++) {
				songBtns[i]->update(1);

				//if a button other than the selectedSong button is pressed
				if (i != selectedSong && songBtns[i]->getClicked()) {
					//update the button states
					songBtns[selectedSong]->setSelected(false);
					songBtns[i]->setSelected(true);
					selectedSong = i;

					//also, load the background for the selected song
					//parse the easy difficulty of the song to get the path to the new background
					OsuFileData fd = OsuFileParser::parseFile(songlist[selectedSong][1] + "easy.osu");
					menuBkg = cBkGround(fd.backgroundPath.c_str());
				}
				songBtns[i]->render();
			}
			//render the difficulty buttons
			for (int i = 0; i < diffBtns.size(); i++) {
				diffBtns[i]->update(1);

				//if a button other than the selectedSong button is pressed
				if (i != selectedDiff && diffBtns[i]->getClicked()) {
					//update the button states
					diffBtns[selectedDiff]->setSelected(false);
					diffBtns[i]->setSelected(true);
					selectedDiff = i;
				}
				diffBtns[i]->render();
			}


			//render the start button
			startBtn->update(1);
			startBtn->render();
			//and start the song if it is clicked
			if (startBtn->getClicked()) {
				string songPath = songlist[selectedSong][1] + diffList[selectedDiff];
				gstate = GameState::PLAYING;
				beatMGR->loadSongByPath(songPath);
				Input->clearBuffers(Input->MOUSE_BUFFER);
			}
			



		}
		else if (gstate == GameState::PLAYING) {
			beatMGR->update();
			


			//Render all text
			string combostr = string("x").append(to_string(thePlayer->combo));
			string scorestr = to_string(thePlayer->score);
			FontManager->getFont("Regular")->printText(combostr.c_str(), FTPoint(10, 700), glm::vec4(1, 1, 1, 0.5));
			FontManager->getFont("Regular")->printText(scorestr.c_str(), FTPoint(10, 10), glm::vec4(1, 1, 1, 0.5));
			FontManager->getFont("Light")->printText(thePlayer->scoreAdded.c_str(), FTPoint(10, 140), glm::vec4(1, 1, 1, 0.3));
			FontManager->getFont("Light")->printText(thePlayer->comboAdded.c_str(), FTPoint(10, 700 - 140), glm::vec4(1, 1, 1, 0.5));
			
			//update and render the player
			//TODO: figure out why the cPlayer class doesn't let me remove the deltaTime parameter from the update function
			thePlayer->update(1);
			thePlayer->render();

			//500ms after the last note has played, go to the score screen
			if (beatMGR->song.GetCurrentPosition() >= (beatMGR->beatsVector[beatMGR->beatsVector.size() - 1]->offset + 500) * 10000) {
				gstate = GameState::SCORE;
			}
			
		}
		else if (gstate == GameState::SCORE){
			menuBkg.render();
			//Render the scores

			string combostr = string("x").append(to_string(thePlayer->combo));
			string scorestr = to_string(thePlayer->score);
			FontManager->getFont("Regular")->printText(combostr.c_str(), FTPoint(10, 700), glm::vec4(1, 1, 1, 0.5));
			FontManager->getFont("Regular")->printText(scorestr.c_str(), FTPoint(10, 10), glm::vec4(1, 1, 1, 0.5));


			replayBtn->update(1);
			
			if (replayBtn->getClicked()) {
				string songPath = songlist[selectedSong][1] + diffList[selectedDiff];
				gstate = GameState::PLAYING;
				beatMGR->loadSongByPath(songPath);
			}
			replayBtn->render();
			backBtn->update(1);
			if (backBtn->getClicked()) {
				gstate = GameState::MENU;
				//clear the mouse click, so the Play button 
				//(which is at the same location) doesn't get clicked
				Input->clearBuffers(Input->MOUSE_BUFFER);
			}
				
			backBtn->render();

		}
		WindowManager->swapBuffers();
    }

	OGL.shutdown(); //Free any resources
	WindowManager->destroyWND(); //Destroy the program window

    return 0; //Return success
}