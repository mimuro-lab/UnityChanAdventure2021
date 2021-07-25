
/*!
@file main.cpp
@brief �v���W�F�N�g�̃��C���֐�����`����Ă���CPP�t�@�C��
@date 2020/04/14/11:03
@author mimuro
*/

#include <DxLib.h>
#include "SystemOwner.h"
#include <memory>
using namespace std;

//!@brief �v���W�F�N�g�̃��C���֐��BSystemOwner�N���X�̃I�u�W�F�N�g���������`���A����𑀍삷��B 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	shared_ptr<SystemOwner> owner = make_shared<SystemOwner>();

	if (owner->initialize()) {
		owner->main();
	}

	owner->finalize();

	return 0;
}
