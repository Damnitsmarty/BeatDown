/*
==========================================================================
cFont.h
==========================================================================
*/

#ifndef _CFONT_H
#define _CFONT_H

// OpenGL Headers
#include "GameConstants.h"

using namespace std;

class cFont
{
private:
	FTFont* theFont;


public:
	cFont();
	cFont(LPCSTR fontFileName, int fontSize);
	~cFont();
	FTFont* getFont();
	void printText(LPCSTR text, FTPoint textPos);

};
#endif