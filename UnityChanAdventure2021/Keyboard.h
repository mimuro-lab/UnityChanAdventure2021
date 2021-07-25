
/*!
@file Keyboard.h
@brief Keyboard�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/20:04
@author mimuro
*/

#pragma once
#include <array>

/*!
@class Keyboard
@brief �L�[�{�[�h�ɃA�N�Z�X���A�L�[�{�[�h�̏�Ԃ���͕����݂̂ŊǗ�����N���X�B
@date 2020/04/16/20:00
@author mimuro
*/
class Keyboard {

protected:
	//! �X�V
	bool update();	
	
	//! keyCode�̃L�[��������Ă���t���[�������擾
	int getPressingCount(int keyCode);

	//! keyCode�̃L�[��������Ă���t���[�������擾
	int getReleasingCount(int keyCode);

private:
	//! �L�[�{�[�h�̃L�[����
	static const int KEY_NUM = 256;	

	//! ������J�E���^
	std::array<int, KEY_NUM> _pressingCount;
	
	//! ������J�E���^
	std::array<int, KEY_NUM> _releasingCount;
	
	//! keyCode���L���ȃL�[�ԍ����₤
	bool isAvailableCode(int keyCode);
};