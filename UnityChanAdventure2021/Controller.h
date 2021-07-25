
/*!
@file Controller.h
@brief Controller�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/18/20:14
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <vector>
#include "Keyboard.h"
#include "Gamepad.h"
#include "Singleton.h"

/*!
@class Controller
@brief ���[�U����̓��͏��𑍊�����N���X�B
@date 2020/04/18/20:16
@author mimuro
*/
class Controller final:
	public Singleton<Controller>,
	private Keyboard,
	private Gamepad
{
	Controller() = default;
	friend Singleton< Controller >;
	//! �E�����{�^�����͏��
	bool push_right = false;
	bool on_right = false;
	//! �������{�^�����͏��
	bool push_left = false;
	bool on_left = false;
	//! ������{�^�����͏��
	bool push_up = false;
	bool on_up = false;
	//! �������{�^�����͏��
	bool push_down = false;
	bool on_down = false;
	//! �X�^�[�g�{�^�����͏��
	bool push_start = false;
	bool on_start = false;
	//! �Z���N�g�{�^�����͏��
	bool push_select = false;
	bool on_select = false;
	//! �`�i�Z�j�{�^�����͏��
	bool push_A = false;
	bool on_A = false;
	//! �a�i�~�j�{�^�����͏��
	bool push_B = false;
	bool on_B = false;
	//! �w�i���j�{�^�����͏��
	bool push_X = false;
	bool on_X = false;
	//! �x�i���j�{�^�����͏��
	bool push_Y = false;
	bool on_Y = false;

public:

	//! �S�Ă̓��͏�Ԃ��X�V����B
	void update();
	//! �E�����{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushRight() { return push_right; }
	//! �������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushLeft() { return push_left; }
	//! ������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushUp() { return push_up; }
	//! �������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushDown() { return push_down; }
	//! �X�^�[�g�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushStart() { return push_start; }
	//! �Z���N�g�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPushSelect() { return push_select; }
	//! �`�i�Z�j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPush_A() { return push_A; }	
	//! �a�i�~�j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPush_B() { return push_B; }	
	//! �w�i���j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPush_X() { return push_X; }	
	//! �x�i���j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getPush_Y() { return push_Y; }	

	//! �E�����{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnRight() { return on_right; }
	//! �������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnLeft() { return on_left; }
	//! ������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnUp() { return on_up; }
	//! �������{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnDown() { return on_down; }
	//! �X�^�[�g�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnStart() { return on_start; }
	//! �Z���N�g�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOnSelect() { return on_select; }
	//! �`�i�Z�j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOn_A() { return on_A; }
	//! �a�i�~�j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOn_B() { return on_B; }
	//! �w�i���j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOn_X() { return on_X; }
	//! �x�i���j�{�^�����͏�Ԃ̎擾�i�����ꂽ�u�ԁj
	const bool getOn_Y() { return on_Y; }

};

