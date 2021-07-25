
/*!
@file ConfigScene.h
@brief ConfigScene�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/04/16/19:50
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include <DxLib.h>

/*!
@class ConfigScene
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B�ݒ��ʂ�S������B
@date 2020/04/16/19:52
@author mimuro
*/
class ConfigScene : public AbstractScene
	,private SelectWindow
{
	//! �X�^�[�g��ʂ��玟�̃V�[����I������B
	void SelectScene();
public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	ConfigScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) , SelectWindow(_changer){};
	~ConfigScene() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

