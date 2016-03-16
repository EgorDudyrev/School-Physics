#include <math.h>
#include "DVector.h"


DVector& DVector::operator =(DVector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

bool DVector::operator ==(DVector &v)
{
	if(fabs(x-v.x) < EPSILON)
		if(fabs(y-v.y) < EPSILON)
			if(fabs(z-v.z) < EPSILON)
				return true;
	return false;
}

DVector DVector::operator+ (DVector& v)
{
	return DVector(x+v.x, y+v.y, z+v.z);
}

DVector DVector::operator- (DVector& v)
{
	return DVector(x-v.x, y-v.y, z-v.z);
}

DVector DVector::operator/ (float& a)
{
	float b = 1.0f/a;
	return DVector(x*b, y*b, z*b);
}
	
DVector DVector::operator* (float& a)
{
	return DVector(x*a, y*a, z*a);
}

float DVector::operator* (DVector& v)
{
	return x*v.x+y*v.y+z*v.z;
}

DVector DVector::cross(DVector& v)
{
	return DVector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

float DVector::mag()
{
	return sqrt(x*x+y*y+z*z);
}

void DVector::normalize()
{
	float magnitude = mag();
	if(magnitude > 0)
	{
		float invertedMag = 1/magnitude;
		x *= invertedMag;
		y *= invertedMag;
		z *= invertedMag;
	}
}

float DVector::distanse(DVector& v)
{
	float dx = x-v.x;
	float dy = y-v.y;
	float dz = z-v.z;
	return sqrt(dx*dx+dy*dy+dz*dz);
}