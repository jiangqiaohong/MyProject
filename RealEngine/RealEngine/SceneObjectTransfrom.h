#pragma once
#include "BaseSceneObject.h"

class SceneObjectTransfrom :public BaseSceneObject
{
public:
	/*
	ͨ����һ��4x4 ����
	*/
	float mat4[16];
};