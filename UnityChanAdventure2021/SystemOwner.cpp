
/*!
@file SystemOwner.cpp
@brief SystemOwner�N���X�̃����o�ނ̒�`���s��CPP�t�@�C��
@date 2020/04/16/3:41
@author mimuro
*/

#include "SystemOwner.h"


/*!
@brief DxLib��̏����������s���B��ɃE�B���h�E��`��Ɋւ��鏈���ł���B
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::initialize() const
{
	SetAlwaysRunFlag(TRUE);						//�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(TRUE);		//�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
	SetOutApplicationLogValidFlag(FALSE);		//���O�o�͂��Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//�t���X�N���[�����ɏc������ێ�����
	//SetUseASyncChangeWindowModeFunction(TRUE, NULL, NULL);
	SetWindowText("UnitychanAdventure");					//�E�B���h�E�^�C�g����t����
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɕύX
	SetWindowSizeExtendRate(1.0);				//�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;					//�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
	SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);		//�Q�[����ʂ̉𑜓x��ݒ肷��
	if (DxLib_Init()) {							//DX���C�u��������������
		return false;							//�ُ�I�������瑦���ɂ�߂�
	}
	SetDrawScreen(DX_SCREEN_BACK);				//����ʏ�����ݒ肷��
	SetWindowPosition(-000, 100);					//�E�B���h�E�̏����ʒu��ݒ肷��

	ImagePath_Effect::getIns()->load();

	return true;
}

/*!
@brief DxLib�̏I���������s���B
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::finalize() const
{
	DxLib_End();
	return true;
}

/*!
@brief SystemLooper�N���X�̃I�u�W�F�N�g�𐶐����A�������Ǘ�����B
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::main() const
{
	
	shared_ptr<SystemLooper> looper = make_shared<SystemLooper>();

	if (!looper->Initialize())
		return false;

	while (!looper->Error()) {
		if (!looper->scrProcess())
			break;
		looper->loop();
	}

	return true;
}