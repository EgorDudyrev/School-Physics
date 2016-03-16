#include "DButton.h"


DButton::DButton()
{
	DButton(0, 0, STD_BTN_WIDTH, STD_BTN_HEIGHT, 0, BT_NULL);
}

DButton::DButton(int x, int y, int w, int h, char *text, int type)
{
	X = x;
	Y = y;
	Width = w;
	Height = h;

	Activate = false;
	Enable = false;
	Visible = false;

	Text = text;

	Type = type;

	pTxtr = 0;

	u1 = 0.0f;
	u2 = 1.0f;
}

DButton::~DButton(void)
{
}