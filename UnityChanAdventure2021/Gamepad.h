
/*!
@file Gamepad.h
@brief Gamepad�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/0:44
@author mimuro
*/

#pragma once
#include "Singleton.h"
#include <array>

/*!
@class Gamepad
@brief �Q�[���R���g���[���iPS3�j�ɃA�N�Z�X���A��Ԃ���͕����݂̂ŊǗ�����N���X�B
@date 2020/04/21/0:44
@author mimuro
*/
class Gamepad
{
	//! �Q�[���p�b�h�̃L�[����
	const static int PAD_KEY_NUM = 16;

	//! �ǂ̃{�^�����ǂ̃{�^���Ɋ��蓖�����Ă��邩������
	std::array<int, PAD_KEY_NUM> _idArray = { 0 };
	
	//! 16�{�^����pad���͏�Ԋi�[
	std::array<int, PAD_KEY_NUM> _pad = { 0 };

protected:

	Gamepad();
	//! �Q�[���p�b�h�̔z�u�̒�`
	enum class ePad {
		left,
		right,
		up,
		down,
		sikaku,
		maru,
		sankaku,
		batu,
		start,
		select
	};

	//! �X�V
	void update();

	//! eID�̃{�^���̓��͏�Ԃ��擾
	int get(ePad eID) const;
};

