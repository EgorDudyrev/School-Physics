#include "DLevel.h"
#include "DDrawer.h"
#define _USE_MATH_DEFINES
//#include <cmath>
#include <math.h>

int DLevel::numOfLevels = 0;

DLevel::DLevel()
{
	lvlNumber = 0; 

	FTxtr = 0;
	sprintf(ExSelectText, "");
	enableStatus = false;


	physObjects = 0;
	numOfObjects = 0;
	/*CreatePhysObjects(2);
	//physObjects = new DPhysicObject[2];
	char name[256];
	sprintf(name, "Шар 1");
	physObjects[0].SetName( name );
	sprintf(name, "Шар 2");
	physObjects[1].SetName( name );
	*/
	levelChars = 0;

	time = 0;
	timer = 0;
	timeStatus = TS_STOP;

	scale = 1.0f;

	//coordSysX = GetSystemMetrics(SM_CXSCREEN) / 2;
	coordSysX = GetSystemMetrics(SM_CXSCREEN) / 3 * 2;
	coordSysY = GetSystemMetrics(SM_CYSCREEN) / 2;
}

DLevel::~DLevel(void)
{
	if(physObjects)
		delete[] physObjects;
	if (levelChars)
		delete[] levelChars;
}

void DLevel::LoadLevel()
{
	
}

void DLevel::TimeManipulate()
{
	switch(timeStatus)
	{
		case TS_PAUSE:
			break;
		case TS_RUN:
			TimeIncrease();
			break;
		case TS_FASTRUN:
			TimeIncrease(5);
			break;
		case TS_BACKRUN:
			TimeDecrease();
			break;
		case TS_FASTBACKRUN:
			TimeDecrease(5);
			break;
		case TS_STOP:
			SetTime(0);
			timeStatus = TS_PAUSE;
			break;
	}
}

void DLevel::Update()
{	
	if (!physObjects) return;

	switch (lvlNumber)
	{
	case 0: 
		UpdateMechLvl();
		break;
	case 1:
		UpdateDifrLvl();
	}
}

void DLevel::CalculateSpeed2()
{
	int m1 = physObjects[0].Get_m1();
	int m2 = physObjects[1].Get_m1();
	float alpha1_rad = physObjects[0].Get_alpha1() * 3.14f / 180.0f;
	float alpha1_grad = physObjects[0].Get_alpha1();
	float alpha2_rad = physObjects[1].Get_alpha1() * 3.14f / 180.0f;
	float alpha2_grad = physObjects[1].Get_alpha1();

	physObjects[0].Set_speed1(physObjects[0].GetAttrib(OBATT_SPEED1)->GetValue(), 0);
	physObjects[1].Set_speed2(physObjects[1].GetAttrib(OBATT_SPEED1)->GetValue(), 0);

	DVector * p1v1;
	DVector * p1v2;
	DVector * p1v;
	DVector * p2v1;
	DVector * p2v2;
	DVector * p2v;

	p1v = physObjects[0].Get_speed();
	p1v1 = physObjects[0].Get_speed1();
	p1v2 = physObjects[0].Get_speed2();
	p2v = physObjects[1].Get_speed();
	p2v1 = physObjects[1].Get_speed1();
	p2v2 = physObjects[1].Get_speed2();
	float tanA, tanB;

	tanA = tan(alpha1_rad);
	tanB = tan(alpha2_rad);

	if (alpha1_grad + alpha2_grad > 180)
	{
		physObjects[0].GetAttrib(OBATT_SPEED2)->SetValue(-1);
		physObjects[1].GetAttrib(OBATT_SPEED2)->SetValue(-1);

		return;
	}
	else if (alpha1_grad + alpha2_grad == 180)
	{
		if (m1*p1v1->x == -m2*p2v1->x)
		{
			float v1 = sqrt( (m1*p1v1->mag()*p1v1->mag() + m2*p2v1->mag()*p2v1->mag()) *m2 / m1 / (m1 + m2));
			float v2 = m1*v1 / m2;

			p1v2->x = v1*cos(alpha1_rad);
			p1v2->y = v1*sin(alpha1_rad);


			p2v2->x = v2*cos(alpha2_rad);
			p2v2->y = v2*sin(alpha2_rad) * (-1);
		}
		else
		{
			physObjects[0].GetAttrib(OBATT_SPEED2)->SetValue(-2);
			physObjects[1].GetAttrib(OBATT_SPEED2)->SetValue(-2);

			return;
		}
	}
	else if (alpha1_grad == 90)
	{
	p1v2->y = tan(alpha2_rad)*(m1*p1v1->x + m2*p2v1->x) / m1;
	//	p1v2->y = -tanB*(m1*p1v1->x + m2*p2v1->x) / m1;
		p2v2->y = -p1v2->y;

		p1v2->x = 0;
		p2v2->x = (m1*p1v1->x + m2*p2v1->x) / m2;
	}
	else if (alpha2_grad == 90)
	{
		p1v2->y = tan(alpha1_rad) * (m1*p1v1->x + m2*p2v1->x) / m1;
		//p1v2->y = -tanA * (m1*p1v1->x + m2*p2v1->x) / m1;
		p2v2->y = -p1v2->y;

		p1v2->x = (m1*p1v1->x + m2*p2v1->x) / m1;
		p2v2->x = 0;
	}
	else
	{
		p2v2->x = tan(alpha1_rad)*(m1*p1v1->x + m2*p2v1->x) / m2 / (tan(alpha1_rad) + tan(alpha2_rad));
		p1v2->x = tan(alpha2_rad)*(m1*p1v1->x + m2*p2v1->x) / m1 / (tan(alpha1_rad) + tan(alpha2_rad));

		p2v2->y = tan(alpha2_rad) * p2v2->x;
		p1v2->y = tan(alpha1_rad) * p1v2->x;

		p2v2->y = -p2v2->y;
	}

		
	
	physObjects[0].GetAttrib(OBATT_SPEED2)->SetValue(p1v2->mag());
	physObjects[1].GetAttrib(OBATT_SPEED2)->SetValue(p2v2->mag());
}

void DLevel::SetStartPosition()
{
	physObjects[0].Set_x0(0);
	physObjects[0].Set_y0(0);
	physObjects[0].Set_x( physObjects[0].Get_x0() );
	physObjects[0].Set_y( physObjects[0].Get_y0() );
	physObjects[0].Set_speed(physObjects[0].GetAttrib(OBATT_SPEED1)->GetValue(), 0);
	//physObjects[0].Set_speed( physObjects[0].Get_speed1() );

	physObjects[1].Set_x0(300);
	//physObjects[1].Set_y0(-32);
	physObjects[1].Set_y0(-48);
	//physObjects[1].Set_y0(-64);
	physObjects[1].Set_x( physObjects[1].Get_x0() );
	physObjects[1].Set_y( physObjects[1].Get_y0() );
	//physObjects[1].Set_speed( physObjects[1].Get_speed1() );
	physObjects[1].Set_speed(physObjects[1].GetAttrib(OBATT_SPEED1)->GetValue(), 0);

}

void DLevel::UpdateMechLvl()
{
	float w = GetSystemMetrics(SM_CXSCREEN) * 2 / 3 / scale; //ширина игрового поля в игровых координатах
	float leftBorder = -w / 2;
	float h = GetSystemMetrics(SM_CYSCREEN) / scale; //высота игрового поля в игровых координатах

	for (int i = 0; i < 2; i++)
	{
		if (isOutOfBorder(&physObjects[i]))
			SetTimeStatus(TS_PAUSE);
	}

	for (int i = 0; i < 2; i++)
	{
		physObjects[i].Set_x((physObjects[i].Get_x0() + physObjects[i].Get_speed()->x * time * TIMESCALE));// * scale);
		physObjects[i].Set_y((physObjects[i].Get_y0() + physObjects[i].Get_speed()->y * time * TIMESCALE));// * scale);
	}



	if (CheckCollision(& physObjects[0], & physObjects[1]))
	{
		if (timeStatus >= TS_RUN && timeStatus <= TS_FASTRUN)
		{
			physObjects[0].Set_speed(physObjects[0].Get_speed2());
			physObjects[1].Set_speed(physObjects[1].Get_speed2());

			physObjects[0].Set_x0(physObjects[0].Get_x());
			physObjects[1].Set_x0(physObjects[1].Get_x());
			time = 0;
			//time = 10;
		}
		if (timeStatus >= TS_FASTBACKRUN && timeStatus <= TS_BACKRUN)
		{
			physObjects[0].Set_speed(physObjects[0].Get_speed1());
			physObjects[1].Set_speed(physObjects[1].Get_speed1());

			physObjects[0].Set_x0(0);
			physObjects[1].Set_x0(300);
			time = timer;
		}

	}
}

void DLevel::UpdateDifrLvl()
{
}

bool DLevel::isOutOfBorder(DPhysicObject * pObj)
{
	float w = GetSystemMetrics(SM_CXSCREEN) * 2 / 3 / scale; //ширина игрового поля в игровых координатах
	float leftBorder = -w / 2;
	float h = GetSystemMetrics(SM_CYSCREEN) / scale; //высота игрового поля в игровых координатах
	bool MovingRight;
	bool MovingLeft;
	bool MovingUp;
	bool MovingDown;
	
	MovingRight = (pObj->Get_speed()->x >= 0 && timeStatus >= TS_RUN && timeStatus <= TS_FASTRUN) || (pObj->Get_speed()->x <= 0 && timeStatus >= TS_FASTBACKRUN && timeStatus <= TS_BACKRUN);
	MovingLeft = (pObj->Get_speed()->x <= 0 && timeStatus >= TS_RUN && timeStatus <= TS_FASTRUN) || (pObj->Get_speed()->x >= 0 && timeStatus >= TS_FASTBACKRUN && timeStatus <= TS_BACKRUN);
	MovingUp = (pObj->Get_speed()->y >= 0 && timeStatus >= TS_RUN && timeStatus <= TS_FASTRUN) || (pObj->Get_speed()->y <= 0 && timeStatus >= TS_FASTBACKRUN && timeStatus <= TS_BACKRUN);
	MovingDown = (pObj->Get_speed()->y <= 0 && timeStatus >= TS_RUN && timeStatus <= TS_FASTRUN) || (pObj->Get_speed()->y >= 0 && timeStatus >= TS_FASTBACKRUN && timeStatus <= TS_BACKRUN);

	if ((MovingLeft && (pObj->Get_x() + pObj->Get_speed()->x <= -w / 2))
		|| (MovingRight && (pObj->Get_x() + pObj->Get_width() + pObj->Get_speed()->x >= w / 2))
		|| (MovingUp && (pObj->Get_y() + pObj->Get_speed()->y >= h / 2))
		|| (MovingDown && (pObj->Get_y() - pObj->Get_height() + pObj->Get_speed()->y <= -h / 2))
		)
		{
			//SetTimeStatus(TS_PAUSE);
			return true;
		}
	return false;
}

bool DLevel::CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float c1X = x1 + r1;
	float c1Y = y1 + r1;
	float c2X = x2 + r2;
	float c2Y = y2 + r2;

	return (r1 + r2)*(r1 + r2) >= (x1 - c2X)*(c1X - c2X) + (c1Y - c2Y)*(c1Y - c2Y);
}

bool DLevel::CheckCollision(DPhysicObject * pObj1, DPhysicObject * pObj2)
{
	return CheckCollision(pObj1->Get_x(), pObj1->Get_y(), pObj1->Get_width() / 2, pObj2->Get_x(), pObj2->Get_y(), pObj2->Get_width() / 2);
}

void DLevel::CalculateDifrAngle(int k)
{
	float d = physObjects[0].GetAttrib(0)->GetValue();
	float lamb = physObjects[1].GetAttrib(0)->GetValue();
	int kmax = CalculateKmax();
	if (k > kmax || k < -kmax)
		physObjects[1].GetAttrib(2)->SetValue(0);
	else
	{
		float sin = k*lamb / d / 1000;
		physObjects[1].GetAttrib(2)->SetValue(asin(sin));
	}
}

void DLevel::CalculateDifrAngle()
{
	CalculateDifrAngle(physObjects[1].GetAttrib(1)->GetValue());
}

int DLevel::CalculateKmax()
{
	float d = physObjects[0].GetAttrib(0)->GetValue();
	float lamb = physObjects[1].GetAttrib(0)->GetValue();
	return int(d / lamb*1000);
}