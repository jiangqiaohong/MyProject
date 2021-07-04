#pragma once

#include "math.h"
class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// ��λ����
	void IdentityMatrix();

	// ƽ�ƾ���
	void MoveMatrix(Vector3f vec3);
	// ���ž���
	void ScaleMatrix(Vector3f vec3);

	// ���ؾ���˷�
	Matrix4 operator*(Matrix4 &) const;

	float* getMatrixData();
private:
	float data[16];
};