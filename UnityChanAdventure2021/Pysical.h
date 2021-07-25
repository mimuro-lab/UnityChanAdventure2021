
/*!
@file Pysical.h
@brief PredictPoint�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/05/04/19:09
@author mimuro
*/

#pragma once
#include "Define.h"
#include "CollisionDetect.h"
#include "VirtualController.h"

/*!
@class Pysical
@brief �������Z�ɒu���đ��x�̉��Z��S���N���X�B
@date 2020/05/04/19:12
@author mimuro
*/
using namespace Define;

class Pysical {

protected:
	//! ���݂̑��x���Ǘ�����ϐ��B
	Dimention now_vel;

	//! ���݂̉����x���Ǘ�����ϐ��B
	Dimention now_acc;

	//! Action���̎��ԁAAction���؂�ւ��ƂO�Ƀ��Z�b�g�����B
	unsigned short int timeInAction = 0;

	//! �I�u�W�F�N�g����������Ă���̐�Ύ���
	unsigned short int timeFromBorn = 0;

	// moveN�R�}�Ɉ������x��������B
	unsigned char addAccN = 2;
	unsigned char addAccCounter = 0;

	//! �d�͂̒l
	unsigned char acc_gravity = Accel_gravity;

	//! ���C�͂̒l
	unsigned char acc_friction = 1;

	//! �u���b�N�Ƃ̔����W��(���鐔�A�傫���Ƒ��x�͏������Ȃ�)
	double coef_block = 0.3;

	// Action���Ƃ̉����x�̑傫���Ƒ��x�̌��E�l
	unsigned char acc_brake = 1;

	unsigned char acc_walk = 1;
	unsigned char limVel_walk = 3;

	unsigned char acc_run = 1;
	unsigned char limVel_run = 7;

	unsigned char initVel_jumpUp = 10;
	unsigned char initVel_jumpMidAir = 0;

	unsigned char acc_inAir = 2;
	char limVel_inAir_jumpUp = 0;
	unsigned char limVel_inAir_afterJump = limVel_walk;
	char limVel_inAir = 0;

	bool preJumpingDireRight = false;
	bool nowJumpingDireRight = false;

	characterAction preAction;

	//! �����x���i�[����ϐ��B
	std::vector<Dimention> _isInitVelocity;

	//! ���̃A�N�V������Ԃ̎��ɏd�͂�L���ɂ��邩�ǂ������Ǘ�����ϐ��B
	std::vector<bool> _validGravityAction;

	//! ���̃A�N�V������Ԃ̎��ɖ��C�͂�L���ɂ��邩�ǂ������Ǘ�����ϐ��B
	std::vector<bool> _validFrictionAction;

	//! �Ώۂ̑��x�ɑ΂��A�����x������ɗ^����֐��B
	virtual Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, VirtualController controller);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	virtual Dimention affectGravity(Dimention affectedAcc, characterAction nowAction);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A����ɒn�ʂƂ̖��C��������B
	virtual Dimention affectFriction(Dimention affectedAcc, characterAction nowAction, bool isDireRight);

	//! �A�N�V������ԂƂ��̕�����������x�𓾂�B
	Dimention getForceFromAction(characterAction nowAction, bool isDireRight, VirtualController controller);

	//! �A�N�V������ԂƂ��̕������瑬�x�̌��E�l�𓾂�B
	virtual Dimention getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller);
	
	//! �����x���瑬�x���v�Z����B
	virtual Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller);

	//! �����Ă�������Ƒ��x�������Ⴄ�Ƃ��͑��x��0�ɂ���B�i���������̂݁j
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, characterAction nowAction, bool isDireRight);

	//! ���x�𓖂��蔻��ɂ�胊�Z�b�g����B
	Dimention resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
		
	characterAction preIsAction = characterAction::Idle;

	//! Action���؂�ւ�����u�Ԃ��擾����֐�
	bool isSwitching(Define::characterAction nowAction) {
		bool ret = false;
		if (nowAction != preIsAction)	ret = true;
		else							ret = false;
		preIsAction = nowAction;
		return ret;
	}

public:

	Pysical()
	{
		now_vel.x = 0;
		now_vel.y = 0;
		now_acc.x = now_acc.y = 0;

		Dimention initVel;
		initVel.x = initVel.y = 0;
		_isInitVelocity = std::vector<Dimention>(static_cast<int>(Define::characterAction::_end), initVel);
		_isInitVelocity[static_cast<int>(Define::characterAction::Jump_Up)].y = - initVel_jumpUp;
		_isInitVelocity[static_cast<int>(Define::characterAction::Jump_MidAir)].y = -initVel_jumpMidAir;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::characterAction::_end), false);
		_validGravityAction[static_cast<int>(Define::characterAction::Fall)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Jump_MidAir)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Brake)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Crouch)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Damage)]

			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_horizonal)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_end)]

			= _validGravityAction[static_cast<int>(Define::characterAction::Soard1_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard2_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard3_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard1_end)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Death)]
			= true;

		_validFrictionAction = std::vector<bool>(static_cast<int>(Define::characterAction::_end), false);
		_validFrictionAction[static_cast<int>(Define::characterAction::Idle)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Brake)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Crouch)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Landing)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Damage)]
			
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Up)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_MidAir)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Fall)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Fall)]

			= _validFrictionAction[static_cast<int>(Define::characterAction::Hundgun_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Hundgun_horizonal)]
		
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard1_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard2_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard3_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard1_end)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Death)]
			
			= true;
	};
	~Pysical() = default;

	//! �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(characterAction nowAction, bool isDireRight, VirtualController controller, std::shared_ptr<CollisionDetect> _collision);

	//! ���W���Z�b�g������A�K�؂ɑ��x�����Z�b�g����B
	Dimention resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);

	const Dimention getAcc() { return now_acc; }
};