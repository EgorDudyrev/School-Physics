#ifndef DBUTTON_H
#define DBUTTON_H

#pragma once
#include <windows.h>
#include "DTexture.h"

enum{	BT_NULL = -1,
		BT_NEW, BT_START_MENU_BTNS = BT_NEW,
		BT_EXIT, BT_END_MENU_BTNS = BT_EXIT,

		BT_SHOWINFO_BALL1, BT_START_EXDESCRIBE_BTNS = BT_SHOWINFO_BALL1,
		BT_SHOWINFO_BALL2,
		BT_CHANGE_M1, BT_START_LVL1CHANGE_BTNS = BT_CHANGE_M1,
		BT_CHANGE_ALPHA1,
		BT_CHANGE_SPEED1,

		BT_CHANGE_M2,
		BT_CHANGE_ALPHA2,
		BT_CHANGE_SPEED2, BT_END_LVL1CHANGE_BTNS = BT_CHANGE_SPEED2, 

		BT_ZOOMIN,
		BT_ZOOMOUT, BT_END_EXDESCRIBE_BTNS = BT_ZOOMOUT,

		BTEX2_CHANGE_D, // ButtonTypeEXersice2_...
		BTEX2_CHANGE_LAMB,
		BTEX2_CHANGE_K,

		BT_SIZE};

const int STD_BTN_WIDTH = 256;
const int STD_SMALL_BTN_WIDTH = 192;
const int STD_BTN_HEIGHT = 32;

class DInterface;

class DButton
{
public:
	DButton();
	DButton(int x, int y, int w, int h, char *text, int type);
	~DButton(void);

	int GetX() {return X;}
	int GetY() {return Y;}
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	int GetType() {return Type;}
	char* GetText() {return Text;}
	bool GetActivateStatus() {return Activate;}
	bool GetVisibleStatus() {return Visible;}
	bool GetEnableStatus() {return Enable;}
	DTexture* GetTexture() {return pTxtr;}

	void SetX(int x) {X = x;}
	void SetY(int y) {Y = y;}
	void SetWidth(int w) {Width = w;}
	void SetHeight(int h) {Height = h;}
	void SetType(int t) {Type = t;}
	void SetText(char *txt) {Text = txt;}
	void SetActivateStatus(bool stat) {Activate = stat;} 	
	void SetVisibleStatus(bool stat) {Visible = stat;} 	
	void SetEnableStatus(bool stat) {Enable = stat;} 	
	void SetTexture(DTexture* txtr) {pTxtr = txtr;}

	float GetU1() {return u1;}
	float GetU2() {return u2;}
	void SetU1(float U1) { u1 = U1;}
	void SetU2(float U2) { u2 = U2;}
protected:
	int X;
	int Y;
	int Width;
	int Height;

	char *Text;
	int Type;

	bool Activate; //Выделена (нажата) кнопка или нет
	bool Enable; //"Включена" ли кнопка
	bool Visible; //Видно ли кнопку

	DTexture *pTxtr;

	float u1, u2;
};

#endif