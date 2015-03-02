#pragma once
#include <cmath>
#include "Vector3.h"

class Matrix3 {
public:
	float values[3][3];

	Matrix3();
	Matrix3(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3);

	Vector3 getColumn1();
	Vector3 getColumn2();
	Vector3 getColumn3();
	Vector3 getRow1();
	Vector3 getRow2();
	Vector3 getRow3();

	void Transpose();
	Vector3 MultiplyVector(Vector3 &vector);

	Matrix3 operator * (Matrix3 &other);
	void operator *= (Matrix3 &other);
	void operator = (Matrix3 &other);
	bool operator == (Matrix3 &other);
	friend bool operator==(const Matrix3 &me, const Matrix3 &other);

	static Matrix3 CreateScaleM3(float X, float Y);
	static Matrix3 CreateRotationM3(float radians);
	static Matrix3 CreateTranslationM3(float X, float Y);
};
