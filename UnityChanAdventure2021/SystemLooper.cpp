
/*!
@file SystemLooper.cpp
@brief SystemLooper�N���X�̃����o�ނ̒�`���s��CPP�t�@�C��
@date 2020/04/15/15:27
@author mimuro
*/

#include "SystemLooper.h"

/*!
@brief ���R���X�g���N�^��shared_from_this()���g�p�ł��Ȃ��A�R���X�g���N�^�Ăяo�����ɂ͊��S�ɃI�u�W�F�N�g�𐶐��ł��Ă��Ȃ��B����ĕϐ�scene.push()�����s�ł��Ȃ��B
@date 2020/04/16/3:14
@author mimuro
*/
SystemLooper::SystemLooper()
{}

/*!
@brief SystemOwner�N���X���ŃI�u�W�F�N�g��������̂݌Ăяo�����֐��B
@brief private�ȃ����o�ϐ���ύX���邩��const�����Ă͂Ȃ�Ȃ��B�iscene.push()�̎g�p�j
@date 2020/04/16/3:31
@author mimuro
*/
bool SystemLooper::Initialize()
{
	scene.push(make_shared<StartScene>(shared_from_this()));
	return true;
}

/*!
@brief SystemOwner�N���X�̃��C����while���̈����Ŏ��s�����֐��B��蔭������true��Ԃ��A��肪�������false��Ԃ��B
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::Error() const
{
	return false;
}

/*!
@brief �\��ʁE����ʏ������ʃN���A�A���b�Z�[�W�����Ȃǂ��s���B
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::scrProcess() const
{
	if (ScreenFlip() != 0)
		return false;
	if (ProcessMessage() != 0)
		return false;
	if (ClearDrawScreen() != 0)
		return false;

	return true;
}

/*!
@brief ���[�v�̒��S�̏��������s�Bstock�^�ł���scene�̏��top�̗v�f�̏������s�킹��B
@date 2020/04/15/17:31
@author mimuro
*/
void SystemLooper::loop()
{
	Controller::getIns()->update();
	_fps.wait();
	_fps.draw();
	scene.top()->update();
	scene.top()->draw();
}


/*!
@brief SystemLooper�N���X�ł̓V�[���������o�ϐ�scene�ŊǗ����邪�A���̃V�[���̕ύX�͂��̊֐��ōs���B
@brief ���̊֐���ISceneChanger�C���^�[�t�F�[�X�N���X�ɋL�ڂ���Ă���֐��ł���A�e�V�[���N���X����Ăяo�����B
@date 2020/04/16/14:29
@author mimuro
*/
void SystemLooper::changeScene(eScene Next, const bool stackPop)
{
	
	if (stackPop) 
		scene.pop();

	switch (Next) {
	case eScene::eStartScene:
		scene.push(make_shared<StartScene>(shared_from_this()));
		break;
	case eScene::eMenuScene:
		scene.push(make_shared<MenuScene>(shared_from_this()));
		break;
	case eScene::eConfigScene:
		scene.push(make_shared<ConfigScene>(shared_from_this()));
		break;
	case eScene::eGameScene:
		scene.push(make_shared<GameScene>(shared_from_this()));
		break;
	default:
		break;
	}
	
}