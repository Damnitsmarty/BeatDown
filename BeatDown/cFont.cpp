/*
==========================================================================
cFont.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cFont.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/
cFont::cFont()
{
	theFont = NULL;
}
/*
==========================================================================
Overloaded constructor
==========================================================================
*/
cFont::cFont(LPCSTR fontFileName, int fontSize)
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}

/*
==========================================================================
Destructor
==========================================================================
*/
cFont::~cFont()
{
	delete theFont;
}
/*
==========================================================================
get the pointer to the font
==========================================================================
*/
FTFont* cFont::getFont()
{
	return theFont;
}

/*
==========================================================================
Render the text using the desired font
==========================================================================
*/
void cFont::printText(LPCSTR text, FTPoint textPos, glm::vec4 colour)
{
	glPushMatrix();
	FTBBox b = theFont->BBox(text);

	float x_offset = (b.Lower().X());
	float y_offset = (b.Upper().Y());

	
	glTranslatef(textPos.X() - x_offset, textPos.Y() + y_offset , 0);
	glScalef(1, -1, 1);
	glColor4d(colour.r, colour.g, colour.b, colour.a);
	theFont->Render(text);

	glPopMatrix();
}
void cFont::printTextCentred(LPCSTR text, FTPoint centrePos, glm::vec4 colour) {
	glPushMatrix();
	FTBBox b = theFont->BBox(text);

	float x_offset = (b.Lower().X());
	float y_offset = (b.Upper().Y());

	float x_offset_centre = (b.Upper().X() - b.Lower().X()) / 2;
	float y_offset_centre = (b.Upper().Y() - b.Lower().Y()) / 2;

	glTranslatef(centrePos.X() - x_offset - x_offset_centre, centrePos.Y() + y_offset - y_offset_centre, 0);
	glScalef(1, -1, 1);
	glColor4d(colour.r, colour.g, colour.b, colour.a);
	theFont->Render(text);

	glPopMatrix();
}