#ifndef DCAMERA_H
#define DCAMERA_H

#include <windows.h>
#include "DVector.h"

#pragma once

//#define lerp( x, y, s ) x + s*(y-x)

class DCamera
{
public:
	DCamera(float camX, float camY, float camZ);
	~DCamera(void);

	float GetAngleX() {return angleX;};
	void SetAngleX(float angle) {angleX = angle;};

	float GetAngleY() {return angleY;};
	void SetAngleY(float angle) {angleY = angle;};

	float GetX() {return X;};
	void SetX(float coord) {X = coord;};

	float GetY() {return Y;};
	void SetY(float coord) {Y = coord;};

	float GetZ() {return Z;};
	void SetZ(float coord) {X = coord;};

	void SetPosition( float x, float y, float z );
	void SetRotation( float deg, float x, float y, float z );
	void MoveCameraLoc( float x, float y, float z );
	void MoveCameraGlob( float x, float y, float z );
	void RotateCameraLoc( float deg, float x, float y, float z );
	void RotateCameraGlob( float deg, float x, float y, float z );
	void SetView();

	DVector GetVector() {return camVect;}
protected:
	//углы поворота камеры
	float angleX;
	float angleY;
	//координаты камеры
	float X;
	float Y;
	float Z;
	float T[16]; //матрица преобразований
	DVector camVect; //Вектор направления камеры
};
#endif