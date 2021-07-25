
/*!
@file AbstractScene.h
@brief AbstractScene�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/04/16/2:40
@author mimuro
*/

#pragma once
#include "ISceneChanger.h"
#include <memory>

using namespace std;

/*!
@class AbstractScene
@brief �V�[�����Ǘ�����N���X�ASystemLooper�Ŏg�p�B�e�V�[���N���X�͂��̃N���X���p������B
@date 2020/04/14/16:00
@author mimuro
*/
class AbstractScene
{
	int unsigned steps_counter = 0;
protected:
	//! �S�ẴV�[���N���X��IScneChanger�^�̃I�u�W�F�N�g����������BSystemLooper�N���X��changeScene�����o�֐����Ăяo�����߁B������R�[���o�b�N�Ƃ�����B
	shared_ptr<ISceneChanger> changer;

	//! �p����̎n�܂肩��̃X�e�b�v�����J�E���g����B
	void counterUpdate() { steps_counter++; };

	//! �X�e�b�v���J�E���^�[�̒l���l������B
	const int getCounter() { return steps_counter; };

public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��Achanger�ɑ������B
	AbstractScene(shared_ptr<ISceneChanger> _changer): changer(_changer){};

	~AbstractScene() = default;

	//! �p����̃V�[���N���X�ł͕K��update()�֐�����鎖��񑩂���B
	virtual void update() = 0;

	//! �p����̃V�[���N���X�ł͕K��draw()�֐�����鎖��񑩂���B
	virtual void draw() = 0;
};

