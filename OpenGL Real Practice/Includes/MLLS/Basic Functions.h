const double Pi = 3.14159265359;

template<typename A>
A static Sum(A a, A b) {
	return a + b;
}

template<typename A>
A static Difference(A a, A b) {
	return a - b;
}

template<typename A>
A static Product(A a, A b) {
	return a * b;
}

template<typename A>
A static Quotient(A a, A b) {
	return a / b;
}

//Radians and Degrees -----------------------------
float static radianToDegree(float radian) {
	return (radian * 180) / Pi;
}
float static degreeToRadian(float degree) {
	return (degree * Pi) / 180;
}

// Interpolate
float static InterpolateScalar(float A, float B, float T) {
	return A + T * (B - A);
}

float static testPower2(float number) {
	if (1 >= number) {
		return 1;
	}
	int i = 1;
	while (true) {
		i = i * 2;
		if (i >= number) {
			return i;
		}
	}
}