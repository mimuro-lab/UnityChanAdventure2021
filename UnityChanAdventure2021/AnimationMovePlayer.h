#pragma once

#include "AnimationMove.h"
#include "RestrictPoint.h"

class AnimationMovePlayer :
	public AnimationMove
{
	//! ��ʏ�̓����𐧌�����B
	RestrictPoint restrictPoint;

public:
	AnimationMovePlayer() {}
	~AnimationMovePlayer() = default;

	//! �X�V���s���֐��B
	Status update(
		Status nowStatus, 
		characterAction _isAction, 
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Stage> _stage, 
		shared_ptr<Animation> _animation, 
		VirtualController controller) override;

	//! �_���[�W�ɂ��X�V�B
	
	//! shiftingStage�̍X�V���s���֐��B
	Dimention getShiftingStage(shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage);
};

