
/*!
@file GameScene.h
@brief GameScene�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/19:55
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include "ImagePath_Unitychan.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyLoad.h"
#include "Stage.h"
#include "PredictStageShift.h"
#include "AbsDamageObj.h"

using namespace std;

/*!
@class GameScene
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B�Q�[����ʂ�S������B
@date 2020/04/16/19:56
@author mimuro
*/
class GameScene :
	public AbstractScene,
	private SelectWindow
{
	//! �w�i��Stage�̏������s���I�u�W�F�N�g
	shared_ptr<Stage> stage;

	shared_ptr<PredictStageShift> predictStageShift;

	//! Player�̏������ɂȂ��I�u�W�F�N�g
	shared_ptr<Player> player;

	vector<shared_ptr<Enemy>> enemys;

	shared_ptr<EnemyLoad> enemyLoad;
	
	//! ��ʏ�̃_���[�W�v�f
	vector<shared_ptr<AbsDamageObj>> damageObjs;

	//! �G�����������_���[�W�v�f
	vector<shared_ptr<AbsDamageObj>> dmgObjFromEnemy;

	int deffOfStageAndBottom = 0;

public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	GameScene(shared_ptr<ISceneChanger> _changer) :
		AbstractScene(_changer),
		SelectWindow(_changer),
		stage(make_shared<Stage>(Define::blockWidth, Define::blockHeight)),
		player(make_shared<Player>(stage)),
		predictStageShift(make_shared<PredictStageShift>())
	{

		enemyLoad = make_shared<EnemyLoad>();

		for (unsigned int i = 0; i < enemyLoad->getElements().size(); i++) {
			shared_ptr<Enemy> ene = make_shared<Enemy>(stage, enemyLoad->getElements()[i].x, enemyLoad->getElements()[i].y, enemyLoad->getElements()[i].hitPoint);
			enemys.push_back(ene);
		}
	};
	~GameScene() = default;

	//! �Q�[����ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! �Q�[����ʂ̕`����s���֐��B
	void draw() override;
};

