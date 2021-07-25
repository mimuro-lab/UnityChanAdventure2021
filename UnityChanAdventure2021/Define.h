#pragma once

/*!
@file Define.h
@brief ���낢��Ȓ�`���܂Ƃ܂�ׂ̃w�b�_�t�@�C��
@date 2020/04/15/0:19
@author mimuro
*/

/*!
@enum eScene
@brief �V�[���̒�`�A�N���X���Ɣ��Ȃ��悤�ɃV�[���̓���'e'��t����悤�ɂ���B
@date 2020/04/15/16:47
@author mimuro
*/
enum class eScene {
	eNone,
	eStartScene,
	eMenuScene,
	eConfigScene,
	eGameScene,
};

/*!
@class Define
@brief ������p�����[�^�̒�`��ێ�����N���X
@date 2020/04/15/0:19
@author mimuro
*/
#pragma once
namespace Define{

	//! �E�B���h�E�T�C�Y��
	const static int WIN_W = 1080;

	//! �E�B���h�E�T�C�Y�c
	const static int WIN_H = 608;
	
	//! �~����
	const static float PI = 3.141592654f; 

	//! �v���C���[��G�̃X�e�[�^�X�Ǘ��̍\����
	struct Status {
		int _x = 0;
		int _y = 0;
		int _y_speed = 0;
		int _x_speed = 0;
		bool isDamage = false;
		bool isDamaging = false;
		bool isDead = false;
		bool directRight = true;
	};
	
	//! �X�e�[�W�̃u���b�N�̃T�C�Y
	unsigned static char blockWidth = 30;
	unsigned static char blockHeight = 30;

	//! �X�e�[�W�̃u���b�N�̐�
	static unsigned char blockXNum = 80;
	static unsigned char blockYNum = 40;

	//! �X�e�[�W�̃u���b�N���̃X�e�[�^�X
	struct BlockCell {
		enum class cellStatus {
			none, block,
		};
		int x1, y1, x2, y2;
		cellStatus _status;
	};

	//! �X�N���[����ʂ̒[�����̍��W
	static int scrollVerticeLeft = 200;
	static int scrollVerticeRight = 450;

	static int scrollHorizonHead = 200;
	static int scrollHorizonBottom = 450;

	//! �v���C���[�I�u�W�F�N�g��G�I�u�W�F�N�g�̊�{�s���̕��ށB
	enum class characterAction {
		Brake, Crouch, Death, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk
		, Hundgun_init, Hundgun_end, Hundgun_horizonal
		, Soard1_init, Soard1_end, Soard2_init, Soard3_init
		, _end
	};

	//! ���W����舵�����̎����̒�`
	struct Dimention {
		int x = 0;
		int y = 0;
	};

	static unsigned char Accel_gravity = 1;

};