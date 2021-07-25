
/*!
@file MenuScene.h
@brief MenuScene�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/03:02
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include <DxLib.h>
#include <memory>

using namespace std;

/*!
@class MenuScene
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B���j���[��ʂ�S������B
@date 2020/04/16/03:02
@author mimuro
*/
class MenuScene : public AbstractScene, private SelectWindow
{
	//! �X�^�[�g��ʂ��玟�̃V�[����I������B
	void SelectScene();

public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	MenuScene(shared_ptr<ISceneChanger> _changer)  : AbstractScene(_changer), SelectWindow(_changer) {};
	~MenuScene() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

