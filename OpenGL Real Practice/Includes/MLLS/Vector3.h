#pragma once
#include <cmath>

class Vector3 {
public:
	float x, y, z;

	Vector3();
	Vector3(float fx, float fy, float fz);

	float getMagnitude();
	Vector3 getUnitVector();
	void Normalize();
	float dotProduct(Vector3 &other);
	Vector3 crossProduct(Vector3 &other);
	Vector3 Interpolate(Vector3 &other, float T);

	Vector3 operator * (float &scalar);
	void operator *= (float &scalar);
	Vector3 operator / (float &scalar);
	void operator /= (float &scalar);
	Vector3 operator * (Vector3 &other);
	void operator *= (Vector3 &other);
	Vector3 operator / (Vector3 &other);
	void operator /= (Vector3 &other);
	Vector3 operator + (Vector3 &other);
	void operator += (Vector3 &other);
	Vector3 operator - (Vector3 &other);
	void operator -= (Vector3 &other);
	void operator = (Vector3 &other);
	bool operator == (Vector3 &other);
	friend bool operator==(const Vector3 &me, const Vector3 &other);
};