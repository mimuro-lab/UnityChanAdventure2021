#pragma once
#include <DxLib.h>
#include "Define.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMoveBullet.h"
#include "AnimationSwitchBullet.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "AbsDamageObj.h"
#include <memory>
#include <vector>

using namespace std;
using namespace Define;

// �G�E�v���C���[�E����������炸�A��ʏ�̃_���[�W�v�f�B
// ����𐶐�����I�u�W�F�N�g�́ADamageObj�Ȃ��Œ�`���ꂽ�����݂̂��w��B
class Bullet : public AbsDamageObj
{

	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int damage = 5;

	int livingTime = 100;
	int livingCounter = 0;
	
	//! ���z�R���g���[��
	VirtualController controller;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Status damageStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	shared_ptr<AnimationMoveBullet> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<CollisionDetect> collision;

	//! �A�N�V������Ԃ�؂�ւ��鏈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	shared_ptr<AnimationSwitchBullet> animationSwitch;

	//! �v���C���[�I�u�W�F�N�g���ǂ����̕����Ɍ��������肷��I�u�W�F�N�g�B
	shared_ptr<CharacterDirect> damageDirect;

	int toHead, toBottom, toRight, toLeft;

public:
	Bullet(shared_ptr<Stage> _stage, int init_x, int init_y, int initVel, bool isDireRight) {
		// �������̐ݒ�B
		damageStatus._x = init_x;
		damageStatus._y = init_y;

		damageStatus.directRight = isDireRight;


		animation = make_shared<Animation>(ImagePath_Object::getIns()->bulletNormal, damageStatus, 0, 0, 6, 99, true, 0.2);

		animationMove = make_shared<AnimationMoveBullet>(initVel, 0, isDireRight);


		int heads, bottoms, rights, lefts;

		heads = bottoms = 1;
		rights = 3;
		lefts = 3;

		toRight = toLeft = 5;
		toHead = 5;
		toBottom = 2;

		collision = make_shared<CollisionDetect>(_stage, damageStatus, heads, bottoms, rights, lefts, toHead, toBottom, toRight, toLeft);

		animationSwitch = make_shared<AnimationSwitchBullet>();

		damageDirect = make_shared<CharacterDirect>();
	}
	~Bullet() = default;

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

	void detectEnemy() override;

	void detectPlayer() override;

	int getDamage() override {
		return damage;
	}
};

