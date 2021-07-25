#pragma once

class VirtualController
{
public:
	VirtualController() = default;
	~VirtualController() = default;

	void clear();

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
};

