#pragma once

#include "math.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// ���ؾ���˷�
	Matrix4 operator*(const Matrix4 &) const;
	// ���ؾ���������ĳ˷�
	Vector4f operator*(const Vector4f &) const;

	float* getMatrixData();
private:
	float data[16];
};