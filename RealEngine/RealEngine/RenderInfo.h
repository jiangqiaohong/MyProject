#pragma once

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);
public:
	// ��������
	float *verticeArray;
	// ��������Ĵ�С
	size_t arraySize;
};