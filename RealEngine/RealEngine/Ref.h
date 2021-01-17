#pragma once

class Ref
{
public:
	void retain();
	void release();

	// �Զ��ͷţ������Զ��ͷų��У�
	Ref* autorelease();

	unsigned int getReferenceCount() const;
private:
	unsigned int _referenceCount;

	friend class AutoreleasePool;
};