#pragma once

#include "math.h"
class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	void IdentityMatrix();

	// ���ؾ���˷�
	Matrix4 operator*(Matrix4 &) const;

	float* getMatrixData();
private:
	float data[16];
};