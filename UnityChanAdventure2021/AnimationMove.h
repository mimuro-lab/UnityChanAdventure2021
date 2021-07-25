
/*!
@file AnimationMove.h
@brief AnimationMove�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/14:12
@author mimuro
*/

#pragma once
#include <memory>
#include <vector>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"
#include "Pysical.h"
#include "PredictPoint.h"

/*!
@class AnimationMove
@brief �v���C���[�I�u�W�F�N�g�̍��W�ʒu���v�Z����N���X�B
@date 2020/05/04/14:16
@author mimuro
*/

using namespace Define;
using namespace std;

class AnimationMove
{

protected:

	//! �����v�Z���s���I�u�W�F�N�g�B
	Pysical pysical;

	//! �v�Z���ꂽ���W���K�؂ł��邩�\������I�u�W�F�N�g�B
	PredictPoint predictPoint;

	//! ���݂̑��x���i�[����ϐ��B
	Dimention nowVelocity;

	//! ���̍��W�i�X�V�����O�̍��W�j���i�[����ϐ��B
	Dimention nowPoint;

	//! ���̍��W�i���ۂɓK���������W�j���i�[����ϐ��B
	Dimention nextPoint;

public:
	AnimationMove(int initVelX = 0, int initVelY = 0){
		nowVelocity.x = initVelX;
		nowVelocity.y = initVelY;
	};

	~AnimationMove() = default;
	
	//! �X�V���s���֐��B
	virtual Status update(
		Status nowStatus, 
		characterAction _isAction, 
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Stage> _stage, 
		shared_ptr<Animation> _animation, 
		VirtualController controller);


};

