#include "AnimationMovePlayer.h"

Status AnimationMovePlayer::update(
	Status nowStatus,
	characterAction nowAction,
	shared_ptr<CollisionDetect> _collision,
	shared_ptr<Stage> _stage,
	shared_ptr<Animation> _animation, 
	VirtualController controller
)
{
	Status _nextStatus = nowStatus;

	// �N���X���ϐ���nowPoint���X�V
	nowPoint.x = nowStatus._x;
	nowPoint.y = nowStatus._y;

	// Pysical�N���X�ɂ��A���݂̏�Ԃ��猻�݂̑��x���v�Z����B
	nowVelocity = pysical.update(nowAction, nowStatus.directRight, controller, _collision);
	nowVelocity = pysical.resetVelocity(nowVelocity, _collision);

	// PredictPoint�N���X�ɂ��A���̑��x�̍��W�ʒu���Ó��ł��邩���f���A�Ó��ȍ��W�ʒu���v�Z����B
	nextPoint = predictPoint.update(nowPoint, nowVelocity, _collision, _stage);

	// RestrictPoint�N���X�ɂ��A��ʏ�œ����𐧌�����B
	nextPoint = restrictPoint.update(nextPoint, nowVelocity, _collision);

	//restrictPoint.draw();

	// nextPoint��Status�^�ϐ��̍��W�ʒu�ɑ�����A�Ԃ��B
	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	// ���x���������
	_nextStatus._x_speed = nowVelocity.x;
	_nextStatus._y_speed = nowVelocity.y;

	//DrawFormatString(100, 50, GetColor(255, 255, 255), "next point x:%d, y:%d", nextPoint.x, nextPoint.y);

	return _nextStatus;
}


Dimention AnimationMovePlayer::getShiftingStage(shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage)
{

	Dimention returnShifting;
	
	returnShifting.x = returnShifting.y = 0;

	if (restrictPoint.isRestrictHorizon())
	{
		// ���̏���
		if (nowVelocity.y > 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = -std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		// ��̏���
		if (nowVelocity.y < 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		returnShifting.y = -nowVelocity.y;

	}

	if (restrictPoint.isRestrictVertice())
	{
		// �E�̏���
		if (nowVelocity.x > 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, std::abs(nowVelocity.x), nowVelocity.y))
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage, nowVelocity.y);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = -std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		//�@���̏���
		if (nowVelocity.x < 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, std::abs(nowVelocity.x), nowVelocity.y))
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage, nowVelocity.y);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		returnShifting.x = -nowVelocity.x;

	}

	
	return returnShifting;

}