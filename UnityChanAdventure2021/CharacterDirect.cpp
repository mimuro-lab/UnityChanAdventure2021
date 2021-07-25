
/*!
@file CharacterDirect.cpp
@brief CharacterDirect�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/17:47
@author mimuro
*/

#include "CharacterDirect.h"

/*!
@brief �A�N�V������Ԃ�run��walk�̎��̂ݕ����̕ϊ����󂯕t����悤�ɂ���B
@date 2020/05/04/17:47
@author mimuro
*/
bool CharacterDirect::updateDirect(Define::characterAction nowAction, bool nowDirectRight, Define::Status nowStatus, VirtualController controller)
{
	// ���̃A�N�V������Ԃ�walk��������R���g���[���̓��͏�ԂŌ�����ς���B
	if (nowAction == Define::characterAction::Walk ||
		nowAction == Define::characterAction::Run /*||
		nowAction == Define::characterAction::Jump_Up ||
		nowAction == Define::characterAction::Jump_MidAir ||
		nowAction == Define::characterAction::Jump_Fall ||
		nowAction == Define::characterAction::Fall*/
		) {
		if (controller.on_right)
			return true;
		if (controller.on_left)
			return false;
	}

	if (nowAction == Define::characterAction::Jump_Up ||
		nowAction == Define::characterAction::Jump_MidAir ||
		nowAction == Define::characterAction::Jump_Fall ||
		nowAction == Define::characterAction::Fall) {
		if (nowStatus._x_speed > 0)
			return true;
		else if (nowStatus._x_speed < 0)
			return false;
		// x���x��0�̎��A�R���g���[���̓��͂Ŕ��f����B
		if (controller.on_right)
			return true;
		if (controller.on_left)
			return false;
	}

	// ��L�̏�ԈȊO�̎��͌��݂̌������ێ�����B
	return nowDirectRight;

}