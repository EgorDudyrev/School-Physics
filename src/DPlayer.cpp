#include "DPlayer.h"

DPlayer::DPlayer()
{
	//pCamera = new DCamera(X*LVLCELLSIZE+LVLCELLSIZE/2, LVLCELLSIZE/2, Z*LVLCELLSIZE+LVLCELLSIZE/2);

	Status = 0;
}

DPlayer::~DPlayer(void)
{
	if(pCamera)
		delete pCamera;
}

void DPlayer::CheckStatus()
{
	//switch (Status)
	{
	
	}
}