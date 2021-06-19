#pragma once
#include "Shader.h"

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);
public:
	// ��������
	float *verticeArray;
	// ��������Ĵ�С
	size_t arraySize;

	// ���������
	int count;
	// ��״
	int shape;
public:
	Shader* _shader;
	void useGLProgram();
};