#ifndef DINTERFACE_H
#define DINTERFACE_H

#pragma once

#include "DButton.h"
#include "DLevel.h"

enum	{SCR_MAINMENU,
		SCR_EX_SELECT,
		SCR_EX_DESCRIBE};

class DInterface
{
public:
	DInterface(HWND hWnd);
	~DInterface(void);

	void InitInterface();

	void onSlcBtnClick();
	void onBtnNewClick();
	void onBtnOptionsClick();
	void onBtnExitClick();
	void onBtnChangeAttribClick(int clickBtn);
	void onBtnChangeM1Click();
	void onBtnChangeAlpha1Click();
	void onBtnChangeSpeed1Click();
	void onBtnChangeM2Click();
	void onBtnChangeAlpha2Click();
	void onBtnChangeSpeed2Click();
	void onBtnShowInfoBall1Click();
	void onBtnShowInfoBall2Click();
	void onBtnZoomInClick();
	void onBtnZoomOutClick();

	void onBtnChangeD_Ex2Click();
	void onBtnChangeLamb_Ex2Click();
	void onBtnChangeK_Ex2Click();
	/*void onBtnClick(DButton *pBtn);
	void onBtnContinueClick();
	void onBtnNewGameClick(DLevel *pLevel);
	void onBtnOptionsClick();
	void onBtnAboutClick();
	void onBtnExitClick(HWND hWnd);
	void onBtnBackClick();*/

	DButton* GetButton(int ind) { return &pButtons[ind];}
	DButton* GetSlcBtn() {return SlcButton;}
	void SetSlcBtn( int btnInd ) {SlcButton = &pButtons[btnInd];}
	void SetSlcBtn(DButton * Btn) { SlcButton = Btn; }
	void SelectUpperBtn();
	void SelectDownerBtn();

	void SetSlcScreen(int screen) { SlcScreen = screen; }
	int GetSlcScreen() {return SlcScreen;}

	void SetLevels( DLevel * levels) { m_pLevels = levels; }

	void SetSlcLevel(int lvl) {SlcLevel = lvl;}
	int GetSlcLevel() {return SlcLevel;}
protected:
	DButton *pButtons;
	DButton *SlcButton;

	DLevel * m_pLevels;

	int SlcScreen;
	int SlcLevel;

	HWND m_pHWnd;


};

#endif