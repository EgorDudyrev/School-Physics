#ifndef DVECTOR_H
#define DVECTOR_H

#pragma once

const float EPSILON = 0.001f;

class DVector
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};

	DVector(void) : x(0), y(0), z(0) {}
	DVector(DVector& v) : x(v.x), y(v.y), z(v.z) {}
	DVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	~DVector(void) {}

	bool operator== (DVector& v);
	DVector& operator= (DVector& v);
	DVector operator+ (DVector& v);
	DVector operator- (DVector& v);
	DVector operator/ (float& a); //������� �� ������
	DVector operator* (float& a); //��������� �� ������
	float operator* (DVector& v); //��������� ������������ ��������
	DVector cross(DVector& v); //��������� ������������ ��������
	float mag(); //���������� ����� �������
	void normalize(); //������������ �������
	float distanse(DVector& v); //���������� ��������� ����� ����� �������
};
#endif