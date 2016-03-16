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
	DVector operator/ (float& a); //Деление на скаляр
	DVector operator* (float& a); //Умножение на скаляр
	float operator* (DVector& v); //Скалярное произведение векторов
	DVector cross(DVector& v); //Векторное произведение векторов
	float mag(); //Нахождение длины вектора
	void normalize(); //Нормализация вектора
	float distanse(DVector& v); //Нахождение растояния между двумя точками
};
#endif