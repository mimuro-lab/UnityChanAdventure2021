#include "VirtualController.h"

void VirtualController::clear()
{

	//! �E�����{�^�����͏��
	push_right = false;
	on_right = false;
	//! �������{�^�����͏��
	push_left = false;
	on_left = false;
	//! ������{�^�����͏��
	push_up = false;
	on_up = false;
	//! �������{�^�����͏��
	push_down = false;
	on_down = false;
	//! �`�i�Z�j�{�^�����͏��
	push_A = false;
	on_A = false;
	//! �a�i�~�j�{�^�����͏��
	push_B = false;
	on_B = false;
	//! �w�i���j�{�^�����͏��
	push_X = false;
	on_X = false;
	//! �x�i���j�{�^�����͏��
	push_Y = false;
	on_Y = false;
}