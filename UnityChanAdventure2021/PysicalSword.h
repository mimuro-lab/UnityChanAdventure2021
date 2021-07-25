#pragma once
#include "Pysical.h"

class PysicalSword :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

public:
	PysicalSword(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalSword() = default;

	//! �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);

};

