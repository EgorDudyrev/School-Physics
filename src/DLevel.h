#pragma once
#include "DPhysicObject.h"
class DTexture;

const float TIMESCALE = 0.2f;

enum {	TS_PAUSE,
		TS_STOP,

		TS_FASTBACKRUN,
		TS_BACKRUN,
		TS_RUN,
		TS_FASTRUN,		
		};

class DLevel
{
public:
	DLevel();
	~DLevel(void);

	void LoadLevel();

	int GetLvlNumber() {return lvlNumber;}
	int GetNumOfLevels() {return numOfLevels;}
	void SetNumOfLevels(int n) { numOfLevels = n; }

	DTexture * GetFTextr() {return FTxtr;}
	void SetFTextr( DTexture *pTxtr) { FTxtr = pTxtr; }

	char * GetExSelectText() { return &ExSelectText[0]; }

	void ToEnable() {enableStatus = true;}
	void ToDisable() {enableStatus = false;}
	bool GetEnable() { return enableStatus; }

	void CreatePhysObjects(int numOfObj) { physObjects = new DPhysicObject[numOfObj]; numOfObjects = numOfObj; }
	DPhysicObject* GetPhysObject(int i) {return &physObjects[i];};
	int GetNumOfObjects() { return numOfObjects; }

	void CreateLvlChars(int i) { levelChars = new DObjectAttrib[i]; }
	DObjectAttrib* GetLvlChar(int i) { return &levelChars[i]; }

	int GetTime() {return time;}
	void SetTime(int t) {time = t;}

	void TimeManipulate();
	void Run() { timeStatus = TS_RUN; }
	void Pause() { timeStatus = TS_PAUSE; }
	void TimeIncrease() { time++; timer++; }
	void TimeIncrease(int delta) { time += delta; timer += delta; }
	void TimeDecrease() { if(time > 0) time--; if(timer > 0) timer--; }
	void TimeDecrease(int delta) { if(time >= delta) time -= delta; if(timer >= delta) timer -= delta; }
	int GetTimeStatus() { return timeStatus; }
	void SetTimeStatus(int stat) { timeStatus = stat; }

	void Update();
	void UpdateMechLvl();
	void UpdateDifrLvl();

	float GetCoordSysX() {return coordSysX;}
	float GetCoordSysY() {return coordSysY;}

	void CalculateSpeed2();
	void CalculateDifrAngle();
	void CalculateDifrAngle(int k);//Для дифр. уровня
	int CalculateKmax();
	void SetStartPosition();

	bool CheckCollision(DPhysicObject * pObj1, DPhysicObject * pObj2);
	bool CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2);

	void SetScale(float s) { scale = s; }
	float GetScale() { return scale; }
	void ZoomIn() { scale += 0.1f; }
	void ZoomOut() { if(scale > 0.1f) scale -= 0.1f; }

	bool isOutOfBorder(DPhysicObject * pObj);
protected:
	int lvlNumber;
	static int numOfLevels;
	bool enableStatus;

	DTexture * FTxtr; //Текстура, показывающая уровень на экране выбора уровней
	char ExSelectText[256];

	DPhysicObject * physObjects;
	int numOfObjects;
	DObjectAttrib * levelChars;

	int time;
	int timer;
	int timeStatus;

	float coordSysX;
	float coordSysY;

	float scale; //Масштаб изображения (зум)
};
