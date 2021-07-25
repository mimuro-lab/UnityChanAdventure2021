#pragma once
#include <DxLib.h>
#include "Define.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMoveSword.h"
#include "AnimationSwitchSword.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "AbsDamageObj.h"
#include "ImagePath_Effect.h"
#include <memory>
#include <vector>

using namespace std;
using namespace Define;

class Sword : public AbsDamageObj
{
	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int damage = 1;

	int livingTime = 10;
	int livingCounter = 0;

	//! ���z�R���g���[��
	VirtualController controller;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Status damageStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	shared_ptr<AnimationMoveSword> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<CollisionDetect> collision;

	//! �A�N�V������Ԃ�؂�ւ��鏈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<AnimationSwitchSword> animationSwitch;

	//! �v���C���[�I�u�W�F�N�g���ǂ����̕����Ɍ��������肷��I�u�W�F�N�g�B
	shared_ptr<CharacterDirect> damageDirect;

	int toHead, toBottom, toRight, toLeft;

public:
	Sword(shared_ptr<Stage> _stage, int init_x, int init_y, bool isDireRight) {
		// �������̐ݒ�B
		damageStatus._x = init_x;
		damageStatus._y = init_y;

		damageStatus.directRight = true;

		animation = make_shared<Animation>(ImagePath_Effect::getIns()->star_pink, damageStatus, 0, 0, 6, 99, isDireRight, 0.2);

		animationMove = make_shared<AnimationMoveSword>(0, 0, isDireRight);

		toHead = 5;
		toBottom = 2;
		toRight = 5;
		toLeft = 5;

		collision = make_shared<CollisionDetect>(_stage, damageStatus, 3, 3, 3, 3, 5, 2, 5, 5);

		animationSwitch = make_shared<AnimationSwitchSword>();

		damageDirect = make_shared<CharacterDirect>();
	}

	~Sword() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) override;

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw() override;

	void adjustBottom(int AdjustRange) override;	
	
	vector<vector<Dimention>> getCollisionPoints() override {
		return collisionPoints;
	}

	vector<int> getRange() override {
		vector<int> retRange;
		retRange.push_back(toHead);
		retRange.push_back(toBottom);
		retRange.push_back(toRight);
		retRange.push_back(toLeft);
		return retRange;
	}

	void detectEnemy() override {
		// Sword�I�u�W�F�N�g�͓G�ɂԂ����Ă������Ȃ��B
	}

	void detectPlayer() override {
		// Sword�I�u�W�F�N�g�͓G�ɂԂ����Ă������Ȃ��B
	}

	int getDamage() override {
		return damage;
	}

};

