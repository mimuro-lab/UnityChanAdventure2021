
/*!
@file AnimationSwitch.h
@brief AnimationSwitch�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/15:03
@author mimuro
*/

#pragma once
#include "CollisionDetect.h"
#include "Controller.h"
#include "Animation.h"
#include "Define.h"
#include "ImagePath_Unitychan.h"
#include "PlayerStatus.h"
#include "VirtualController.h"
#include <memory>

/*!
@class AnimationSwitch
@brief �A�j���[�V�����̏�Ԃ�؂�ւ���ׂ̃N���X
@date 2020/05/04/15:03
@author mimuro
*/

using namespace Define;
using namespace std;

class AnimationSwitch
{

	//! �A�j���[�V�����̐؂�ւ��ɂ́A�A�j���[�V�����̏�Ԃ��󂯎��K�v������B
	shared_ptr<Animation> _animation;

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������characterAction�ɑΉ��j
	vector<bool> IsAction_canSwitching;

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	//! ���̃A�N�V�������i�[���Ă����ϐ��B
	characterAction nextAction;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Status playerStatus;

	//! ���A�N�V���������̃R���{�ɂ��邩�ǂ����B
	bool soardCombContinue = false;

	//! �A�N�V������Ԃ�؂�ւ��Ă��悢����Ԃ��B
	bool acceptSwitching(shared_ptr<Animation> animation, characterAction nowAction);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	characterAction getNextAction(
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Animation> _animation, 
		Status playerStatus,
		characterAction nowAction
		, VirtualController controller);
	
	//! getNextAction�ɂ�蓾�����̃A�N�V������Ԃ�K������Ă悢���ǂ�����Ԃ��֐��B
	bool acceptNextAction(characterAction nowAction, characterAction nextAction, Status _playerStatus);

	//! animation�����t���b�V�����Ă��悢�����f����֐��B
	bool isRefresh(characterAction nowAction, shared_ptr<Animation> __animation);
	

	//! ���U���̃R���{������
	bool getSoardComb(characterAction nowAction, shared_ptr<Animation> __animation, bool nowCombContinue, VirtualController controller);

protected:

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	characterAction nowAction;

	//! �A�j���[�V������؂�ւ���֐��B
	virtual shared_ptr<Animation> switchingAnimation(characterAction next, Status _playerStatus);

public:
	AnimationSwitch(characterAction initAction = characterAction::Walk)
	{ 
		// nowAction�͍ŏ��AFall����n�߂�B
		nowAction = initAction;
		
		// IsAction_canSwitchin�̏������B Idle, Walk, Run, Fall�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = vector<bool>(static_cast<int>(characterAction::_end), false);

		IsAction_canSwitching[static_cast<int>(characterAction::Idle)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Walk)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Run)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Fall)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_MidAir)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_Fall)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Hundgun_init)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Hundgun_horizonal)]
			= true;
	};
	~AnimationSwitch() = default;

	//! �X�V���s���֐��B
	shared_ptr<Animation> update(
		shared_ptr<CollisionDetect> collision,
		shared_ptr<Animation> animation,
		Status playerStatus,
		VirtualController controller);

	//! ���݂ǂ̃A�N�V������Ԃ����擾����֐��B
	characterAction getNowAction() { return nowAction; }

};

