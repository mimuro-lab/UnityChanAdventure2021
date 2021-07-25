
/*!
@file Player.h
@brief Player�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/12:26
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Define.h"
#include "ImagePath_Unitychan.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMovePlayer.h"
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "Bullet.h"
#include "Sword.h"
#include "AbsDamageObj.h"
#include "CalcDamagesOverlap.h"
#include "PlayerStatus.h"
#include <memory>
#include <vector>

/*!
@class Player
@brief Player�L�����̏����S�ʂ�S���N���X�B
@date 2020/04/21/12:28
@author mimuro
*/
class Player
{

	//! �R���g���[��
	VirtualController controller;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;

	//! �X�e�[�W���ړ������鑬�x
	Dimention shiftingStage;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	std::shared_ptr<AnimationMovePlayer> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<CollisionDetect> collision;

	//! �A�N�V������Ԃ�؂�ւ��鏈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<AnimationSwitch> animationSwitch;

	//! �v���C���[�I�u�W�F�N�g���ǂ����̕����Ɍ��������肷��I�u�W�F�N�g�B
	std::shared_ptr<CharacterDirect> playerDirect;

	//! Player����̃_���[�W�I�u�W�F�N�g���������Ă��邩�𔻒肷��I�u�W�F�N�g�B
	std::shared_ptr<CalcDamagesOverlap> damagesOverlap;

	vector<vector<Define::Dimention>> collisionPoints;

	vector<int> detectDmsInd;

	std::shared_ptr<PlayerStatus> statusAsPara;
	
	VirtualController updateController();

	int toBottom = 30;
	int toRight = 10;
	int toLeft = 10;

	bool isDead = false;
	bool isEnd = false;

public:

	Player(std::shared_ptr<Stage> _stage)
	{
		// �������̐ݒ�B
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;

		playerStatus._x_speed = playerStatus._y_speed = 0;

		playerStatus.directRight = true;
		playerStatus.isDamaging = false;

		shiftingStage.x = shiftingStage.y = 0;

		statusAsPara = std::make_shared<PlayerStatus>();
		statusAsPara->HitPoint = 100;
		statusAsPara->AllHitPoint = 1000;
		statusAsPara->lessHitPoint = statusAsPara->AllHitPoint / 4;
		statusAsPara->isAlive = true;

		animation = std::make_shared<Animation>(ImagePath_Unitychan::getIns()->unityChan_Fall, playerStatus);

		animationMove = std::make_shared<AnimationMovePlayer>();

		collision = std::make_shared<CollisionDetect>(_stage, playerStatus, 10, 10, 10, 10, 15, toBottom, toRight, toLeft);

		animationSwitch = std::make_shared<AnimationSwitch>();

		playerDirect = std::make_shared<CharacterDirect>();

		damagesOverlap = std::make_shared<CalcDamagesOverlap>();
		
	};

	~Player() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update(std::shared_ptr<Stage> _stage, std::vector<std::shared_ptr<AbsDamageObj>> _damagesFromEnemys);

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw();

	void pushPlayerFromStage(std::shared_ptr<Stage> _stage);

	int adjustStageAndBottom(std::shared_ptr<Stage> _stage);

	const Define::Status getStatus() { return playerStatus; }

	const Dimention getShiftingState() { return shiftingStage; }

	vector<shared_ptr<AbsDamageObj>> generateDamageObj(vector<shared_ptr<AbsDamageObj>> _nowDmg, shared_ptr<Stage> stage);

	bool isCollisionedInSideBottom() {
		return collision->getCollisionedInSide().bottom;
	}

	int getToBottom() { return toBottom; }
	int getToRight() { return toRight; }
	int getToLeft() { return toLeft; }

	vector<int> getDetectedDamagesIndex() {
		return detectDmsInd;
	}

	bool getIsEnd() { return isEnd; }

};
