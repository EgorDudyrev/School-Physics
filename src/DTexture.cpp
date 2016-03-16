#include "DTexture.h"

DTexture::DTexture()
{
	bpp = 0;
	Data = 0;
	Filter = 0;
	glTexture = 0;
	Height = 0;
	Width = 0;
	Name[0] = 0;
	FileName[0] = 0;
}

DTexture::~DTexture()
{
	if( Data )
		delete [] Data;
}