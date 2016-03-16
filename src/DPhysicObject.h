#ifndef DPHYSICOBJECT_H
#define DPHYSICOBJECT_H

#include <vector>
using namespace std;
#include "DVector.h"
#include "DTexture.h"
#include "DObjectAttrib.h"

#include <stdio.h>
#pragma once

enum {	OBATT_MASS1, OBATT_ENUM_START = OBATT_MASS1,
		OBATT_ANGLE1,
		OBATT_SPEED1,

		OBATT_MASS2,
		OBATT_ANGLE2,
		OBATT_SPEED2, OBATT_ENUM_END = OBATT_SPEED2
};
class DPhysicObject
{
public:
	DPhysicObject(void);
	~DPhysicObject(void);

	void Set_speed( float x, float y) { speed->x = x; speed->y = y; }
	void Set_speed( DVector * s) { speed = s; }
	DVector * Get_speed() {return speed;}
	void Set_speed1( float x, float y) { speed1->x = x; speed1->y = y; }
	void Set_speed1(float speed) { attribs[OBATT_SPEED1].SetValue(speed);}
	DVector * Get_speed1() {return speed1; }
	void Set_speed2( float x, float y ) { speed2->x = x; speed2->y = y; }
	void Set_speed2(float speed) { attribs[OBATT_SPEED2].SetValue(speed); }
	DVector * Get_speed2() { return speed2; }
	void Set_m1( float mass ) { attribs[OBATT_MASS1].SetValue(mass); }
	float Get_m1() { return attribs[OBATT_MASS1].GetValue(); }
	void Set_m2( float mass ) { attribs[OBATT_MASS2].SetValue(mass); }
	float Get_m2() { return attribs[OBATT_MASS2].GetValue(); }
	void Set_alpha1(float a) { attribs[OBATT_ANGLE1].SetValue(a);}
	float Get_alpha1() {return attribs[OBATT_ANGLE1].GetValue();}
	void Set_alpha2(float a) { attribs[OBATT_ANGLE2].SetValue(a); }
	float Get_alpha2() { return attribs[OBATT_ANGLE2].GetValue(); }

	void CreateAttribs(int numOfAttr) { attribs = new DObjectAttrib[numOfAttr]; numOfAttribs = numOfAttr; }
	DObjectAttrib * GetAttrib(int i) { if (i < numOfAttribs) return &attribs[i]; else return 0; }
	int GetNumOfAttribs() { return numOfAttribs; }
	void SetNumOfAttribs(int n) { numOfAttribs = n; }
	int GetNumOfChangeAttribs() { return numOfChangeAtribs;}
	void SetNumOfChangeAttribs(int n) { numOfChangeAtribs = n; }


	char * GetName() {return &name[0];}
	void SetName(const char * n) { strncpy( name, n, 256);}

	void Set_x(float coor) { x = coor; }
	float Get_x() {return x;}

	void Set_y(float coor) {y = coor; }
	float Get_y() {return y;}

	void Set_x0(float coor) { x0 = coor; }
	float Get_x0() {return x0;}

	void Set_y0(float coor) {y0 = coor; }
	float Get_y0() {return y0;}

	void Set_width(float w) { width = w; }
	float Get_width() {return width;}

	void Set_height(float h) { height = h; }
	float Get_height() {return height;}

	void SetTxtr( DTexture *pTxtr) {texture = pTxtr;}
	DTexture * GetTxtr() {return texture;}

private:
	DVector * speed; //Текущая скорость
	DVector * speed1; //Скорость ДО
	DVector * speed2; //Скорость ПОСЛЕ
	DTexture * texture; //Текстура объекта
	//float alpha; //Угол отклонения
//	int m1; //Масса
	//int m2; //
	DObjectAttrib * attribs;
	int numOfAttribs;
	int numOfChangeAtribs; //характеристики, которые можно изменять
	char name[256];

	float x;
	float y;
	float x0;
	float y0;

	float width;
	float height;
};

#endif DPHYSICOBJECT_H