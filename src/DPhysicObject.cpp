#include "DPhysicObject.h"



DPhysicObject::DPhysicObject(void)
{
	speed1 = new DVector( 0, 0, 0);
	speed2 = new DVector( 0, 0, 0);
	speed = speed1;
	texture = 0;
	strcpy(name, "Объект");

	attribs = 0;
	numOfAttribs = 0;
	numOfChangeAtribs = 0;
	/*attribs = new DObjectAttrib[6];
	attribs[OBATT_MASS1].SetName("m");
	attribs[OBATT_SPEED1].SetName("v");
	attribs[OBATT_MASS2].SetName("m'");
	attribs[OBATT_SPEED2].SetName("v'");
	attribs[OBATT_ANGLE1].SetName("angle");
	attribs[OBATT_ANGLE2].SetName("angle'");*/
	/*m1 = 0;
	m2 = 0;
	alpha = 0;*/

	x = 0;
	y = 0;
	x0 = 0;
	y0 = 0;

	width = height = 0;
}

DPhysicObject::~DPhysicObject(void)
{
	if(speed1)
		delete speed1;
	if(speed2)
		delete speed2;
}