#pragma once
#include <cmath>

class Vector2 {
public:
	float x, y;

	Vector2();
	Vector2(float fx, float fy);

	float getMagnitude();
	Vector2 getUnitVector();
	void Normalize();
	float dotProduct(Vector2 &other);
	float angle(Vector2 &other);
	Vector2 Interpolate(Vector2 &other, float T);

	Vector2 operator * (float &scalar);
	void operator *= (float &scalar);
	Vector2 operator / (float &scalar);
	void operator /= (float &scalar);
	Vector2 operator * (Vector2 &other);
	void operator *= (Vector2 &other);
	Vector2 operator / (Vector2 &other);
	void operator /= (Vector2 &other);
	Vector2 operator + (Vector2 &other);
	void operator += (Vector2 &other);
	Vector2 operator - (Vector2 &other);
	void operator -= (Vector2 &other);
	void operator = (Vector2 &other);
	bool operator == (Vector2 &other);
	friend bool operator==(const Vector2 &me, const Vector2 &other);
};