#pragma once
#include "Pysical.h"
class PysicalBullet :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

	// �d�͂�N�R�}�Ɉ��L��
	unsigned char validGravityN = 6;
	unsigned char validGravityCounter = 0;

	// �󒆂̍ŏ����x
	unsigned char minVel_inAir = 5;

	//! �A�N�V������ԂƂ��̕������瑬�x�̌��E�l�𓾂�B
	Dimention getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller) override;

	//! �����x���瑬�x���v�Z����B
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller) override;

	Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	Dimention affectGravity(Dimention affectedAcc, characterAction nowAction) override;

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A����ɒn�ʂƂ̖��C��������B
	Dimention affectFriction(Dimention affectedAcc, Dimention nowVelocity, characterAction nowAction, bool isDireRight);

public:
	PysicalBullet(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalBullet() = default;

	//! �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);



};

