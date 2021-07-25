
/*!
@file SystemLooper.h
@brief SystemLooper�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/15/15:12
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <stack>
#include <memory>
#include "Controller.h"
#include "Fps.h"
#include "ISceneChanger.h"
#include "AbstractScene.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "ConfigScene.h"
#include "GameScene.h"

using namespace std;

/*!
@class SystemLooper
@brief ���[�v���鏈���̒��S��S���N���X
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper : public ISceneChanger,
	public enable_shared_from_this<SystemLooper>
{	
	//! �V�[�����Ǘ�����ϐ��B�e�v�f��shred_ptr<AbstractScene>�^��stack�^���g�p����B
	stack <shared_ptr<AbstractScene>> scene;

	//! FPS�������{�����߂̃I�u�W�F�N�g�B
	Fps _fps;
public:
	//! �������������s���֐��B
	SystemLooper();
	~SystemLooper() = default;

	//! �������������s���֐��B
	bool Initialize();

	//! �G���[�������s���֐��B
	bool Error() const;

	//! ��ʏ������s���֐��B
	bool scrProcess() const;

	//! ���C���̌J��Ԃ��������s���֐��B
	void loop();

	//! �V�[���ւ����s���֐��B
	void changeScene(eScene NextScene, const bool stackClear) override;
};

