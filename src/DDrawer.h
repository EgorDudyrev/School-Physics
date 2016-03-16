#ifndef DDRAWER_H
#define DDRAWER_H


#include <vector>
using namespace std;
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>
class DTexture;
class DModel;
class DInterface;
class DButton;
class DLevel;
class DObjectAttrib;
#pragma once



const float C_COLOR_BLACK[4]	= { 0.0, 0.0, 0.0, 1.0 };
const float C_COLOR_GRAY[4]		= { 0.5, 0.5, 0.5, 1.0 };
const float C_COLOR_WHITE[4]	= { 1.0, 1.0, 1.0, 1.0 };

const float C_COLOR_RED[4]		= { 1.0, 0.0, 0.0, 1.0 };
const float C_COLOR_GREEN[4]	= { 0.0, 1.0, 0.0, 1.0 };
const float C_COLOR_BLUE[4]		= { 0.0, 0.0, 1.0, 1.0 };

const float C_COLOR_YELLOW[4]	= { 1.0, 1.0, 0.0, 1.0 };
const float C_COLOR_CIAN[4]		= { 0.0, 1.0, 1.0, 1.0 };
const float C_COLOR_PURPURE[4]	= { 1.0, 0.0, 1.0, 1.0 };

const float C_COLOR_ORANGE[4]	= { 1.0, 0.5, 0.0, 1.0 };
const float C_COLOR_PINK[4]		= { 1.0, 0.0, 0.5, 1.0 };
const float C_COLOR_MAROON[4]	= { 1.0, 0.5, 0.5, 1.0 };

const float C_COLOR_LIGHT_GREEN[4]	= { 0.5, 1.0, 0.0, 1.0 };
const float C_COLOR_SPRING_GREEN[4] = { 0.0, 1.0, 0.5, 1.0 };
const float C_COLOR_GREEN_MINT[4]	= { 0.5, 1.0, 0.5, 1.0 };

const float C_COLOR_VIOLET[4]	= { 0.5, 0.0, 1.0, 1.0 };
const float C_COLOR_AZURE[4]	= { 0.0, 0.5, 1.0, 1.0 };
const float C_COLOR_KING_BLUE[4]= { 0.5, 0.5, 1.0, 1.0 };

const float C_COLOR_LIGHT_BLUE[4] = { 0.26, 0.67, 1.0, 1.0 };

const float C_COLOR_TRANSPARENT[4] = { 0.0, 0.0, 0.0, 0.0 };

class DDrawer
{
public:
	DDrawer(HWND, DInterface *, DLevel *);
	~DDrawer(void);

	void DrawText( int x, int y, const char *str, float size = 16, float* color = 0, int rect_width = -1 );
	int index_first_char_in_string(const char* str, const char chr);

	void DrawScene(  ); 
	void InitGraphic();

	void DrawMainMenu();
	void DrawExSelectMenu();
	void DrawExDescribeMenu();

	void DrawMechLevel(); //Уровень с шарами
	void DrawDifrLevel(); //Уровень с дифракционной решёткой

	void DrawAttrib(DObjectAttrib * pAttrib, float x, float y, float w, float h, float * textClr);

	void FindLightWaveColor(double lamb, float ** color);

	void DrawButton( DButton *pBtn );
	void DrawButton(DButton *pBtn, DTexture * pTxtr, float bright);

	bool GetTxtrEnable() { return glTxtrEnable; }
	void SetTxtrEnable(bool TxtrEnable) { glTxtrEnable = TxtrEnable; }
	void ChangeTxtrEnable() { glTxtrEnable = !glTxtrEnable; }

	void DrawColorRect(float x1, float x2, float y1, float y2, float *color);
	void DrawColorRect(float x1, float x2, float y1, float y2, float z1, float z2, float *color);
	void DrawColorQuadr(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *color);
	void DrawTextureRect(float x1, float x2, float y1, float y2, float u1, float v1, float u2, float v2, DTexture *txtr, float bright = 1.0f);

	void	MakeTexture( const char *filename, const char* name, DTexture *&texture, unsigned int filter ); //Обобщающая функция создания текстуры
	DTexture* CreateTexture( const char *name, unsigned int filter );
	int		LoadTexture( const char *filename, DTexture** ptex );
	int		GraphicsLoadTexture( DTexture** ptex );
	void	BindTexture( DTexture* );

	void DrawObject(DModel *pModel,float x,float y,float z);
	void DrawModel( DModel * pModel );
	// Загружает модель формата *.smd
	int	LoadModel( const char* filename, const char* name, DModel** newModel);
	int LoadModelAnimation( const char* filename, const char* anim_name, DModel ** );
	int	DeleteModel( DModel** pModel );
private:
	HWND myhWnd;
	HGLRC hRC;	// Постоянный контекст рендеринга
	HDC hDC;	// Приватный контекст устройства GDI
	
	bool glTxtrEnable;

	DTexture *pFontTxtr;
	DTexture *pBtnTxtr;
	DTexture *pMenuBackTxtr;
	DTexture *pAdMenuTxtr;
	DTexture *pBallTxtr;
	DTexture *pNewGameBtnTxtr;
	DTexture *pExitBtnTxtr;
	DTexture *pLockTxtr;
	DTexture *pChangeBtnTxtr;
	DTexture *pBallInfo1BtnTxtr;
	DTexture *pBallInfo2BtnTxtr;
	DTexture *pZoomInBtnTxtr;
	DTexture *pZoomOutBtnTxtr;

	DInterface	*m_pInterface;
	DLevel		*m_pLevels;
};

#endif