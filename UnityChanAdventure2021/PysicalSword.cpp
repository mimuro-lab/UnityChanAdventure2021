#include "PysicalSword.h"

/*!
@brief ���݂̃A�N�V������Ԃ��瑬�x���v�Z���A�Ԃ��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalSword::update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> collision, VirtualController controller)
{

	// Action���؂�ւ�����玞�Ԃ��O�ɂ���B
	if (isSwitching(nowAction))
		timeInAction = 0;

	// �����x���v�Z����B
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		//now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, nowAction, isDireRight);
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
