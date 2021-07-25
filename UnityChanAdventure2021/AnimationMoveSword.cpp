#include "AnimationMoveSword.h"


/*!
@brief Status�^�̌��݌��݂̏�Ԃ���͂��A���̃R�}�̍��W�ʒu���X�V����Ԃ��B
@date 2020/05/04/14:38
@author mimuro
*/
Status AnimationMoveSword::update(
	Status nowStatus,
	characterAction nowAction,
	shared_ptr<CollisionDetect> _collision,
	shared_ptr<Stage> _stage,
	shared_ptr<Animation> _animation,
	VirtualController controller,
	Status playerStatus
)
{
	Status _nextStatus = nowStatus;

	// �N���X���ϐ���nowPoint���X�V
	nowPoint.x = nowStatus._x + playerStatus._x_speed;
	nowPoint.y = nowStatus._y + playerStatus._y_speed;

	// Pysical�N���X�ɂ��A���݂̏�Ԃ��猻�݂̑��x���v�Z����B
	nowVelocity = damagePysic->update(nowAction, nowStatus.directRight, _collision, controller);
	nowVelocity = damagePysic->resetVelocity(nowVelocity, _collision);

	// PredictPoint�N���X�ɂ��A���̑��x�̍��W�ʒu���Ó��ł��邩���f���A�Ó��ȍ��W�ʒu���v�Z����B
	//nextPoint = predictPoint.update(nowPoint, nowVelocity, _collision, _stage);
	nextPoint = nowPoint;

	// nextPoint��Status�^�ϐ��̍��W�ʒu�ɑ�����A�Ԃ��B
	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	// ���x���������
	_nextStatus._x_speed = nowVelocity.x;
	_nextStatus._y_speed = nowVelocity.y;

	//DrawFormatString(100, 50, GetColor(255, 255, 255), "next point x:%d, y:%d", nextPoint.x, nextPoint.y);

	return _nextStatus;

}