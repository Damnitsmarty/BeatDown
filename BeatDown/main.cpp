#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"
#include "cBeatMGR.h"


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

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	//LPCSTR strTextures[] = { 
	//	"Images\\beat.png",
	//	"Images\\asteroid1.png", 
	//	"Images\\asteroid2.png", 
	//	"Images\\asteroid3.png", 
	//	"Images\\asteroid4.png", 
	//	"Images\\bullet.png" 
	//};
	//for (int tCount = 0; tCount < 5; tCount++)
	//{
	//	theGameTextures.push_back(new cTexture());
	//	theGameTextures[tCount]->createTexture(strTextures[tCount]);
	//}


	static BeatManager* beatMGR = BeatManager::getInstance();
	/*beatMGR->loadSongByPath("Songs/74671 P-Light - TRIGGER-HAPPY/PLight - TRIGGERHAPPY (MineC24) [EXHAUST].osu");
	beatMGR->loadSongByPath("Songs/163078 LiSA - Rising Hope (TV Size)/LiSA - Rising Hope (TV Size) (xChippy) [Hope].osu");
	beatMGR->loadSongByPath("Songs/329657 STEREO DIVE FOUNDATION - Renegade/STEREO DIVE FOUNDATION - Renegade (tutuhaha) [AngelHoney's Insane].osu"); 
	beatMGR->loadSongByPath("Songs/325158 AKINO from bless4 & CHiCO with HoneyWorks - MIIRO vs Ai no Scenario/AKINO from bless4 & CHiCO with HoneyWorks - MIIRO vs. Ai no Scenario (monstrata) [Tatoe].osu");*/
	beatMGR->loadSongByPath("Songs/29864 Baby Alice - Pina Colada Boy (Nightcore Mix)/Baby Alice - Pina Colada Boy (Nightcore Mix) (osuplayer111) [Insane].osu");
	
	
	//cTexture rocketTxt;
	//rocketTxt.createTexture("Images\\rocketSprite.png");
	//cRocket rocketSprite;
	//rocketSprite.attachInputMgr(Input); // Attach the input manager to the sprite
	//rocketSprite.setSpritePos(glm::vec2(512.0f, 380.0f));
	//rocketSprite.setTexture(rocketTxt.getTexture());
	//rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	//rocketSprite.setSpriteCentre();
	//rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

    //This is the mainloop, we render frames until isRunning returns false
	while (WindowManager->isWNDRunning())
    {
		WindowManager->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = WindowManager->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		
		

		beatMGR->update(elapsedTime);
		
		/*rocketSprite.update(elapsedTime);
		rocketSprite.render();*/

		WindowManager->swapBuffers();
		Input->clearBuffers(Input->KEYS_DOWN_BUFFER | Input->KEYS_PRESSED_BUFFER);
    }

	OGL.shutdown(); //Free any resources
	WindowManager->destroyWND(); //Destroy the program window

    return 0; //Return success
}
