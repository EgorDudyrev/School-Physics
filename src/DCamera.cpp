#include "DCamera.h"
#include <gl/gl.h>

DCamera::DCamera(float camX, float camY, float camZ)
{
	//углы поворота камеры
	angleX = 0;
	angleY = 0;
	//координаты камеры
	X = camX;
	Y = camY;
	Z = camZ;
	//матрица преобразований
	for(int i = 0; i<16; i++)
		T[i] = 0;
	T[0] = 1.0f;
	T[5] = 1.0f;
	T[10] = -1.0f;
	T[15] = 1.0f;
	T[12] = X;
	T[13] = Y;
	T[14] = Z;

	camVect.x = 0;
	camVect.y = 0;
	camVect.z = -1;

	//поворот камеры в нужную сторону(не работает)
//	RotateCameraGlob(angleY, 0.0f, 1.0f, 0.0f);
}

DCamera::~DCamera(void)
{
}

void DCamera::MoveCameraLoc( float x, float y, float z )
{
	float dx = x * T[0] + y * T[4] + z * T[8];
	float dy = x * T[1] + y * T[5] + z * T[9];
	float dz = x * T[2] + y * T[6] + z * T[10];
	T[12] += dx;
	T[13] += dy;
	T[14] += dz;
	X += dx;
	Y += dy;
	Z += dz;
}

void DCamera::MoveCameraGlob( float x, float y, float z )
{
	T[12] += x * 1;
	T[13] += y * 1;
	T[14] += z * 1;

	X += x;
	Y += y;
	Z += z;
}

void DCamera::RotateCameraLoc( float deg, float x, float y, float z )
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(T);
	glRotatef( deg, x, y, z );
	glGetFloatv(GL_MODELVIEW_MATRIX, T);
	glPopMatrix();

	angleX += deg*x;
	angleY += deg*y;
}

void DCamera::RotateCameraGlob( float deg, float x, float y, float z )
{
	float dx = x * T[0] + y * T[1] + z * T[2];
	float dy = x * T[4] + y * T[5] + z * T[6];
	float dz = x * T[8] + y * T[9] + z * T[10];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(T);
	glRotatef(deg, dx, dy, dz);
	glGetFloatv(GL_MODELVIEW_MATRIX, T );
	glPopMatrix();

	angleX += deg*x;
	angleY += deg*y;
	
	DVector oldVect = camVect;

	camVect.x = oldVect.x*T[0] + oldVect.y*T[1] + oldVect.z*T[2];
	camVect.y = oldVect.x*T[4] + oldVect.y*T[5] + oldVect.z*T[6];
	camVect.z = oldVect.x*T[8] + oldVect.y*T[9] + oldVect.z*T[10];

	/*camVect.x = camVect.x*T[0] + camVect.x*T[4] + camVect.x*T[8] + camVect.z*T[12];
	camVect.y = camVect.y*T[1] + camVect.y*T[5] + camVect.y*T[9] + camVect.z*T[13];
	camVect.z = camVect.z*T[2] + camVect.z*T[6] + camVect.z*T[10] + camVect.z*T[14];*/
}

void DCamera::SetView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float viewmatrix[16] = {
							T[0], T[4], -T[8], 0,
							T[1], T[5], -T[9], 0,
							T[2], T[6], -T[10], 0,	
							-(T[0]*T[12] +T[1]*T[13] +T[2]*T[14]),
							-(T[4]*T[12] +T[5]*T[13] +T[6]*T[14]),
							(T[8]*T[12] +T[9]*T[13] +T[10]*T[14]), 1};
	
	glLoadMatrixf(viewmatrix);
}

void DCamera::SetPosition(float x, float y, float z)
{
	T[12] = x * 1;
	T[13] = y * 1;
	T[14] = z * 1;

	X = x;
	Y = y;
	Z = z;
}

void DCamera::SetRotation(float deg, float x, float y, float z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(T);
	glRotatef(deg, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, T );
	glPopMatrix();

	angleX += deg*x;
	angleY += deg*y;
}
