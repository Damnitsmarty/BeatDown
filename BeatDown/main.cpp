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


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1280;
    const int windowHeight = 800;
    const int windowBPP = 16;




    //This is our window
	static cWNDManager* WindowManager = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* Input = cInputMgr::getInstance();

	// Load Font manager and fonts
	static cFontMgr* FontManager = cFontMgr::getInstance();
	FontManager->addFont("Regular", LPCSTR("Fonts/Aller_Rg.ttf"), 96);
	FontManager->addFont("Light", LPCSTR("Fonts/Aller_Lt.ttf"), 48);
		

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

	static BeatManager* beatMGR = BeatManager::getInstance();
	beatMGR->loadSongByPath("Songs/74671 P-Light - TRIGGER-HAPPY/PLight - TRIGGERHAPPY (MineC24) [EXHAUST].osu");
	//beatMGR->loadSongByPath("Songs/163078 LiSA - Rising Hope (TV Size)/LiSA - Rising Hope (TV Size) (xChippy) [Hope].osu");
	//beatMGR->loadSongByPath("Songs/329657 STEREO DIVE FOUNDATION - Renegade/STEREO DIVE FOUNDATION - Renegade (tutuhaha) [AngelHoney's Insane].osu"); 
	//beatMGR->loadSongByPath("Songs/325158 AKINO from bless4 & CHiCO with HoneyWorks - MIIRO vs Ai no Scenario/AKINO from bless4 & CHiCO with HoneyWorks - MIIRO vs. Ai no Scenario (monstrata) [Tatoe].osu");
	//beatMGR->loadSongByPath("Songs/29864 Baby Alice - Pina Colada Boy (Nightcore Mix)/Baby Alice - Pina Colada Boy (Nightcore Mix) (osuplayer111) [Insane].osu");
	
	

	cPlayer* thePlayer = cPlayer::getInstance();

	//This is the mainloop, we render frames until isRunning returns false
	while (WindowManager->isWNDRunning())
    {
		WindowManager->processWNDEvents(); //Process any window events
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		beatMGR->update();
		
		string combostr = to_string(thePlayer->combo).append("x");
		string scorestr = to_string(thePlayer->score);
		FontManager->getFont("Regular")->printText(combostr.c_str(), FTPoint(10, 700));
		FontManager->getFont("Regular")->printText(scorestr.c_str(), FTPoint(10, 10));
		FontManager->getFont("Light")->printText(thePlayer->scoreAdded.c_str(), FTPoint(10, 140));
		FontManager->getFont("Light")->printText(thePlayer->comboAdded.c_str(), FTPoint(10, 700-140));

		thePlayer->update(1);
		thePlayer->render();

		WindowManager->swapBuffers();
		//Input->clearBuffers(Input->KEYS_DOWN_BUFFER | Input->KEYS_PRESSED_BUFFER);
    }

	OGL.shutdown(); //Free any resources
	WindowManager->destroyWND(); //Destroy the program window

    return 0; //Return success
}

void printScores() {
	
}
