#ifndef DPLAYER_H
#define DPLAYER_H

#include "DCamera.h"
#include "DLevel.h"

#pragma once


class DPlayer
{
public:
	DPlayer();
	~DPlayer(void);
	
	DCamera* GetCamera() {return pCamera;};

	int GetStatus() { return Status; }
	void SetStatus(int status) { Status = status; }
	void CheckStatus();
	
protected:
	int X;
	int Z;

	int Status;

	DCamera *pCamera;
};

#endif