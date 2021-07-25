#include "PysicalBullet.h"


/*!
@brief Action��Ԃ���A���̎��̑��x�̌��E�l�𓾂�B�������l�����Ă���A�����̂͑��x���O��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnVelocity;

	returnVelocity.x = returnVelocity.y = 128;

	// �����E����̎��͏�ɋ󒆂̑��x�̏��������������B
	if (nowAction == characterAction::Run || nowAction == characterAction::Walk) {
		if (isDireRight) {
			limVel_inAir_jumpUp = std::abs(now_vel.x);
			if (std::abs(now_vel.x) < limVel_walk)
				limVel_inAir_jumpUp = std::abs(limVel_walk);
		}
		else {
			limVel_inAir_jumpUp = -std::abs(now_vel.x);
			if (std::abs(now_vel.x) < limVel_walk)
				limVel_inAir_jumpUp = -std::abs(limVel_walk);
		}
		if (now_vel.x == 0) {
			if (isDireRight)
				limVel_inAir_jumpUp = limVel_walk;
			else
				limVel_inAir_jumpUp = -limVel_walk;
		}
	}
	if (nowAction == characterAction::Idle) {
		if (isDireRight)
			limVel_inAir_jumpUp = limVel_walk;
		else
			limVel_inAir_jumpUp = -limVel_walk;
	}

	if (preAction == characterAction::Walk || preAction == characterAction::Run)
		limVel_inAir = limVel_inAir_jumpUp;

	// �󒆂ŕ����]���������ǂ����B
	//if (nowAction == characterAction::Jump_Up || nowAction == characterAction::Jump_MidAir ||
	//	nowAction == characterAction::Jump_Fall || nowAction == characterAction::Fall) {
	//	preJumpingDireRight = isDireRight;

		//if (preJumpingDireRight != nowJumpingDireRight) 
		{
			if (isDireRight) {
				limVel_inAir = 128;
			}
			if (!isDireRight) {
				limVel_inAir = -128;
			}
		}

	//	nowJumpingDireRight = preJumpingDireRight;
	//}

	nowJumpingDireRight = preJumpingDireRight = isDireRight;

	switch (nowAction) {
	case characterAction::Walk:
		if (isDireRight)
			returnVelocity.x = limVel_walk;
		else
			returnVelocity.x = -limVel_walk;
		break;
	case characterAction::Run:
		if (isDireRight)
			returnVelocity.x = limVel_run;
		else
			returnVelocity.x = -limVel_run;
		break;

	case characterAction::Jump_Up:
		returnVelocity.x = limVel_inAir;
		break;
	case characterAction::Jump_MidAir:
		returnVelocity.x = limVel_inAir;
		break;
	case characterAction::Fall:
		returnVelocity.x = limVel_inAir;
		break;

	}

	//DrawFormatString(100, 20, GetColor(255, 255, 255), "vel_lim x:%d, y:%d", returnVelocity.x, returnVelocity.y);

	preAction = nowAction;

	return returnVelocity;
}

/*!
@brief ���C�͂�L���ɂ���֐��B�����͉̂����x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention PysicalBullet::affectFriction(Dimention affectedAcc, Dimention nowVelocity, characterAction nowAction, bool isDireRight)
{
	Dimention returnAcc = affectedAcc;

	if (nowAction == characterAction::Jump_Up ||
		nowAction == characterAction::Jump_MidAir ||
		nowAction == characterAction::Jump_Fall ||
		nowAction == characterAction::Fall) {
		if (now_vel.x == 0)
			return returnAcc;
	}

	if (_validFrictionAction[static_cast<int>(nowAction)] && nowAction != characterAction::Fall) {
		if (isDireRight) {
			returnAcc.x -= acc_friction;
		}
		if (!isDireRight) {
			returnAcc.x += acc_friction;
		}
	}
	
	if (nowAction == characterAction::Fall) {
		if (isDireRight && now_vel.x > minVel_inAir) {
			returnAcc.x -= acc_friction;
		}
		if (!isDireRight && now_vel.x < -minVel_inAir) {
			returnAcc.x += acc_friction;
		}
	}

	return returnAcc;
}

/*!
@brief ���̎��̉����x����A���̑��x���v�Z����B�Ԃ��̂͑��x�B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnVelocity = affectedVel;

	int limitX = std::abs(getLimitVelFromAction(nowAction, isDireRight, controller).x);
	int nextVelAbs = std::abs(returnVelocity.x + affectAcc.x);

	// �X�V��̑��x�����E�l�𒴂��Ȃ��悤�ł���Α��x�ɉ����x�𑫂�
	if (nextVelAbs <= limitX) {
		returnVelocity.x += affectAcc.x;
	}
	// ������悤�ł���Ό��E�l�ɐݒ肷��B(�����ɂ����)
	else
		returnVelocity.x = getLimitVelFromAction(nowAction, isDireRight, controller).x;

	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}


Dimention PysicalBullet::affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0 && !collision->getCollisionedSide().bottom) {
		if (isDireRight)
			returnVel.x += std::abs(initVelX);
		else {
			returnVel.x -= std::abs(initVelX);
		}
		returnVel.y += initVelY;
	}

	return returnVel;
}

/*!
@brief �d�͂�L���ɂ���֐��B�����͉̂����x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention PysicalBullet::affectGravity(Dimention affectedAcc, characterAction nowAction)
{
	Dimention returnAcc = affectedAcc;

	if (_validGravityAction[static_cast<int>(nowAction)]) {
		validGravityCounter++;
		validGravityCounter %= validGravityN;
		if(validGravityCounter==0)
			returnAcc.y += acc_gravity;
	}

	return returnAcc;

}

/*!
@brief ���݂̃A�N�V������Ԃ��瑬�x���v�Z���A�Ԃ��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> collision, VirtualController controller)
{

	// Action���؂�ւ�����玞�Ԃ��O�ɂ���B
	if (isSwitching(nowAction))
		timeInAction = 0;

	// �����x��L���ɂ���B
	now_vel = affectInitVelocity(now_vel, nowAction, timeFromBorn, collision, _isDireRight);

	// �����x���v�Z����B
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, now_vel, nowAction, isDireRight);
	}
	else {
		now_acc.x = now_acc.y = 0;
	}
	addAccCounter++;
	addAccCounter %= addAccN;

	// �����x���瑬�x���X�V����B
	now_vel = calcVelocityFromAccel(now_vel, now_acc, nowAction, isDireRight, controller);

	// �����Ă�������Ɛ��������̑��x�����̒��a���Ƃ�B
	now_vel = matchingVelAndDireHorizon(now_vel, nowAction, isDireRight);

	timeInAction++;
	timeFromBorn++;
	//DrawFormatString(100, 70, GetColor(255, 255, 255), "now acc x:%d, y:%d", now_acc.x, now_acc.y);
	return now_vel;
}
