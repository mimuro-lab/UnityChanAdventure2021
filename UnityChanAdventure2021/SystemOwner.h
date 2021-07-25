
/*!
@file SystemOwner.h
@brief SystemOwner�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/04/16/3:41
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Define.h"
#include "SystemLooper.h"
#include <memory>
#include "ImagePath_Effect.h"

using namespace std;

/*!
@class SystemOwner
@brief ������������I�������S�ʂ�S���N���X
@date 2020/04/14/23:43
@author mimuro
*/

class SystemOwner
{
public:
	SystemOwner() = default;
	~SystemOwner() = default;

	//! �������������s���֐��B
	bool initialize() const;
	
	//! �I���������s���֐��B
	bool finalize() const;

	//! ���s�̒��S������S���֐��B���������������������ꍇ�Ŏ��s�����B
	bool main() const;

};

