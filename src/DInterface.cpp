#include "DInterface.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>
DInterface::DInterface(HWND hWnd)
{
	m_pHWnd = hWnd;

	pButtons = new DButton[BT_SIZE];
	SlcButton = &pButtons[BT_START_MENU_BTNS];
	SlcButton->SetType(BT_START_MENU_BTNS);
	
	SlcScreen = SCR_MAINMENU;
	SlcLevel = 0;

	InitInterface();

	m_pLevels = 0;
}

DInterface::~DInterface(void)
{
	if( pButtons )
		delete[] pButtons;
	pButtons = 0;
	SlcButton = 0;
}

void DInterface::InitInterface()
{
	DButton *pBtn;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Настройка кнопок для Главного меню 
	int btnWidth = screenWidth/3;
	int btnHeight = screenHeight/ (BT_END_MENU_BTNS+1-BT_START_MENU_BTNS + 2);
	int firstBtnX = (screenWidth-btnWidth)/2;
	int firstBtnY = btnHeight;
	for(int i = BT_START_MENU_BTNS; i <= BT_END_MENU_BTNS; i++)
	{
		pBtn = &pButtons[i];
		pBtn->SetType(i);
		pBtn->SetWidth(btnWidth);
		pBtn->SetHeight(btnHeight);
		pBtn->SetX(firstBtnX);
		pBtn->SetY(firstBtnY + (i-BT_START_MENU_BTNS)*btnHeight);
		
		switch(pBtn->GetType()) {
			case BT_NEW:
				pBtn->SetVisibleStatus(true);
				pBtn->SetEnableStatus(true);
				break;			
			case BT_EXIT:
				pBtn->SetVisibleStatus(true);
				pBtn->SetEnableStatus(true);
				break;
		}
	}
	for(int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
	{
		pBtn = &pButtons[i];
		pBtn->SetType(i);
		pBtn->SetWidth(32);
		pBtn->SetHeight(32);
		pBtn->SetX(screenWidth/3 - 30 - pBtn->GetWidth());
		pBtn->SetY( 160 + 50* (i - BT_START_LVL1CHANGE_BTNS) + 9 );

		pBtn->SetVisibleStatus(true);
		pBtn->SetEnableStatus(true);
		pBtn->SetActivateStatus(false);
	}
	//Кнопки для свёртывания информации
	pBtn = &pButtons[BT_SHOWINFO_BALL1];
	pBtn->SetType(BT_SHOWINFO_BALL1);
	pBtn->SetWidth(128);
	pBtn->SetHeight(32);
	pBtn->SetX(30);
	pBtn->SetY(160);
	pBtn->SetVisibleStatus(true);
	pBtn->SetEnableStatus(true);
	pBtn->SetActivateStatus(false);

	pBtn = &pButtons[BT_SHOWINFO_BALL2];
	pBtn->SetType(BT_SHOWINFO_BALL2);
	pBtn->SetWidth(128);
	pBtn->SetHeight(32);
	pBtn->SetX(30);
	pBtn->SetY(190);
	pBtn->SetActivateStatus(false);
	pBtn->SetVisibleStatus(true);
	pBtn->SetEnableStatus(true);

	//Кнопки зума (приближение, отдаление)
	pBtn = &pButtons[BT_ZOOMIN];
	pBtn->SetType(BT_ZOOMIN);
	pBtn->SetWidth(32);
	pBtn->SetHeight(32);
	pBtn->SetX(screenWidth - 32*4);
	pBtn->SetY(screenHeight - 16*5);
	pBtn->SetActivateStatus(false);
	pBtn->SetVisibleStatus(true);
	pBtn->SetEnableStatus(true);

	pBtn = &pButtons[BT_ZOOMOUT];
	pBtn->SetType(BT_ZOOMOUT);
	pBtn->SetWidth(32);
	pBtn->SetHeight(32);
	pBtn->SetX(screenWidth - 32*3);
	pBtn->SetY(screenHeight - 16*5);
	pBtn->SetActivateStatus(false);
	pBtn->SetVisibleStatus(true);
	pBtn->SetEnableStatus(true);
}

void DInterface::onBtnNewClick()
{
	SlcScreen = SCR_EX_SELECT;
}

void DInterface::onBtnOptionsClick()
{
	return;
}

void DInterface::onBtnExitClick()
{
	DestroyWindow(m_pHWnd);
}

void DInterface::onSlcBtnClick()
{
	switch(SlcButton->GetType())
	{
		case BT_NEW:
			onBtnNewClick();
			break;
		case BT_EXIT:
			onBtnExitClick();
			break; 
		case BT_CHANGE_M1:
			onBtnChangeAttribClick(BT_CHANGE_M1);
			break;
		case BT_CHANGE_ALPHA1:
			onBtnChangeAttribClick(BT_CHANGE_ALPHA1);
			break;
		case BT_CHANGE_SPEED1:
			onBtnChangeAttribClick(BT_CHANGE_SPEED1);
			break;
		case BT_CHANGE_M2:
			onBtnChangeAttribClick(BT_CHANGE_M2);
			break;
		case BT_CHANGE_ALPHA2:
			onBtnChangeAttribClick(BT_CHANGE_ALPHA2);
			break;
		case BT_CHANGE_SPEED2:
			onBtnChangeAttribClick(BT_CHANGE_SPEED2);
			break;
		case BTEX2_CHANGE_D:
			onBtnChangeD_Ex2Click();
			break;
		case BTEX2_CHANGE_LAMB:
			onBtnChangeLamb_Ex2Click();
			break;
		case BTEX2_CHANGE_K:
			onBtnChangeK_Ex2Click();
			break;
		case BT_SHOWINFO_BALL1:
			onBtnShowInfoBall1Click();
			break;
		case BT_SHOWINFO_BALL2:
			onBtnShowInfoBall2Click();
			break;
		case BT_ZOOMIN:
			onBtnZoomInClick();
			break;
		case BT_ZOOMOUT:
			onBtnZoomOutClick();
			break;
	}
		
}

void DInterface::SelectUpperBtn()
{
	for(int i = SlcButton->GetType()-1; i != BT_START_MENU_BTNS-2; i--)
	{
		if(i == -1)
		{
			for(int k = BT_END_MENU_BTNS; k >= BT_START_MENU_BTNS; k--)
			{
				if(pButtons[k].GetEnableStatus() && pButtons[k].GetVisibleStatus())
				{
					SlcButton = &pButtons[k];
					break;
				}
			}
			break;
		}
		if(pButtons[i].GetEnableStatus() && pButtons[i].GetVisibleStatus())
		{
			SlcButton = &pButtons[i];
			break;
		}
		
	}
}

void DInterface::SelectDownerBtn()
{
	for(int i = SlcButton->GetType()+1; i != BT_END_MENU_BTNS+2; i++)
	{
		if(i == BT_END_MENU_BTNS+1)
		{
			for(int k = BT_START_MENU_BTNS; k <= BT_END_MENU_BTNS; k++)
			{
				if(pButtons[k].GetEnableStatus() && pButtons[k].GetVisibleStatus())
				{
					SlcButton = &pButtons[k];
					break;
				}
			}
			break;
		}
		if(pButtons[i].GetEnableStatus() && pButtons[i].GetVisibleStatus() && i <= BT_END_MENU_BTNS)
		{
			SlcButton = &pButtons[i];
			break;
		}
		
	}
}

void DInterface::onBtnChangeM1Click()
{
	pButtons[BT_CHANGE_M1].SetActivateStatus(!pButtons[BT_CHANGE_M1].GetActivateStatus());

	if (pButtons[BT_CHANGE_M1].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(0)->Set_m1(0);
		
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_M1)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeAlpha1Click()
{
	pButtons[BT_CHANGE_ALPHA1].SetActivateStatus(!pButtons[BT_CHANGE_ALPHA1].GetActivateStatus());

	if (pButtons[BT_CHANGE_ALPHA1].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(0)->Set_alpha1(0);

		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_ALPHA1)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeSpeed1Click()
{
	pButtons[BT_CHANGE_SPEED1].SetActivateStatus(!pButtons[BT_CHANGE_SPEED1].GetActivateStatus());

	if (pButtons[BT_CHANGE_SPEED1].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(0)->Set_speed1(0);

		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_SPEED1)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);

		m_pLevels[SlcLevel].SetStartPosition();
		m_pLevels[SlcLevel].CalculateSpeed2();
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeM2Click()
{
	pButtons[BT_CHANGE_M2].SetActivateStatus(!pButtons[BT_CHANGE_M2].GetActivateStatus());

	if (pButtons[BT_CHANGE_M2].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(1)->Set_m1(0);

		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_M2)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeAlpha2Click()
{
	pButtons[BT_CHANGE_ALPHA2].SetActivateStatus(!pButtons[BT_CHANGE_ALPHA2].GetActivateStatus());

	if (pButtons[BT_CHANGE_ALPHA2].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(1)->Set_alpha1(0);

		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_ALPHA2)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeSpeed2Click()
{
	pButtons[BT_CHANGE_SPEED2].SetActivateStatus(!pButtons[BT_CHANGE_SPEED2].GetActivateStatus());

	if (pButtons[BT_CHANGE_SPEED2].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(1)->Set_speed1(0);

		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != BT_CHANGE_SPEED2)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeAttribClick(int clickBtn)
{
	pButtons[clickBtn].SetActivateStatus(!pButtons[clickBtn].GetActivateStatus());

	int objNum = (clickBtn - BT_START_LVL1CHANGE_BTNS) / 3;
	if (pButtons[clickBtn].GetActivateStatus())
	{
		m_pLevels[SlcLevel].GetPhysObject(objNum)->GetAttrib((clickBtn - BT_START_LVL1CHANGE_BTNS)%3 + OBATT_ENUM_START)->SetValue(0);


		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			if (i != clickBtn)
				pButtons[i].SetEnableStatus(false);
	}
	else
	{
		for (int i = BT_START_LVL1CHANGE_BTNS; i <= BT_END_LVL1CHANGE_BTNS; i++)
			pButtons[i].SetEnableStatus(true);

		m_pLevels[SlcLevel].SetStartPosition();
		m_pLevels[SlcLevel].CalculateSpeed2();
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeD_Ex2Click()
{
	DButton * pBtn = m_pLevels[1].GetPhysObject(0)->GetAttrib(0)->GetButton();

	pBtn->SetActivateStatus(!pBtn->GetActivateStatus());

	if (pBtn->GetActivateStatus())
	{
		m_pLevels[1].GetPhysObject(0)->GetAttrib(0)->SetNewValue(0);

		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
				if (m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->GetType() != BTEX2_CHANGE_D)
					m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(false);
	}
	else
	{
		m_pLevels[1].GetPhysObject(0)->GetAttrib(0)->AsignValue();
		m_pLevels[1].CalculateDifrAngle();


		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
					m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(true);
	}
	//Продолжение в DWindow.cpp WndProc()
}

void DInterface::onBtnChangeLamb_Ex2Click()
{
	DButton * pBtn = m_pLevels[1].GetPhysObject(1)->GetAttrib(0)->GetButton();

	pBtn->SetActivateStatus(!pBtn->GetActivateStatus());

	//pBtn->SetEnableStatus(false);
	if (pBtn->GetActivateStatus())
	{
		m_pLevels[1].GetPhysObject(1)->GetAttrib(0)->SetNewValue(0);

		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
				if (m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->GetType() != BTEX2_CHANGE_LAMB)
					m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(false);
	}
	else
	{
		m_pLevels[1].GetPhysObject(1)->GetAttrib(0)->AsignValue();
		m_pLevels[1].CalculateDifrAngle();


		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
				m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(true);
	}
}

void DInterface::onBtnChangeK_Ex2Click()
{
	DButton * pBtn = m_pLevels[1].GetPhysObject(1)->GetAttrib(1)->GetButton();

	pBtn->SetActivateStatus(!pBtn->GetActivateStatus());

	if (pBtn->GetActivateStatus())
	{
		m_pLevels[1].GetPhysObject(1)->GetAttrib(1)->SetNewValue(0);

		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
				if (m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->GetType() != BTEX2_CHANGE_K)
					m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(false);
	}
	else
	{
		m_pLevels[1].GetPhysObject(1)->GetAttrib(1)->AsignValue();
		m_pLevels[1].CalculateDifrAngle();

		for (int i = 0; i < m_pLevels[1].GetNumOfObjects(); i++)
			for (int j = 0; j < m_pLevels[1].GetPhysObject(i)->GetNumOfChangeAttribs(); j++)
				m_pLevels[1].GetPhysObject(i)->GetAttrib(j)->GetButton()->SetEnableStatus(true);
	}
}

void DInterface::onBtnShowInfoBall1Click()
{
	pButtons[BT_SHOWINFO_BALL1].SetActivateStatus(!pButtons[BT_SHOWINFO_BALL1].GetActivateStatus());
}

void DInterface::onBtnShowInfoBall2Click()
{
	pButtons[BT_SHOWINFO_BALL2].SetActivateStatus(!pButtons[BT_SHOWINFO_BALL2].GetActivateStatus());
}

void DInterface::onBtnZoomInClick()
{
	m_pLevels[SlcLevel].ZoomIn();
}

void DInterface::onBtnZoomOutClick()
{
	m_pLevels[SlcLevel].ZoomOut();
}
