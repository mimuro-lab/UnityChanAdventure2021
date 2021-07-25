
/*!
@file CharacterDirect.h
@brief CharacterDirect�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/17:43
@author mimuro
*/

#pragma once
#include "Define.h"
#include "VirtualController.h"

/*!
@class CharacterDirect
@brief Player�L�����̕������X�V����N���X�B
@date 2020/05/04/17:43
@author mimuro
*/
class CharacterDirect
{
public:
	CharacterDirect() = default;
	~CharacterDirect() = default;

	//! �X�V�������s���֐��B
	bool updateDirect(Define::characterAction nowAction, bool nowDirectRight, Define::Status nowStatus, VirtualController _controller);
};