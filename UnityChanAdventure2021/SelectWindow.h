
/*!
@file SelectWindow.h
@brief SelectWindow�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/18/23:12
@author mimuro
*/

#pragma once
#include "Controller.h"
#include "ISceneChanger.h"
#include <memory>

/*!
@class SelectWindow
@brief �Z���N�g��ʂ̏�����S���N���X�B�Z���N�g��ʂ�L���ɂ������V�[���Ɍp��������Ǝg�p�ł���B
@date 2020/04/18/23:13
@author mimuro
*/
class SelectWindow
{
	//! �ЂƂO�̃R�}�̃Z���N�g�E�B���h�E�̏�ԁB�E�B���h�E�̗���������m���邽�߂̕ϐ��B
	bool _preIsSelected = false;

	//! �V�[���ύX�̂��߂̃R�[���o�b�N�BSystemLooper��changeScene�֐���p���邽�߂ɒ�`�B
	std::shared_ptr<ISceneChanger> changerInSelectWindow;

	//! �Z���N�g�{�^���������ꂽ����ێ�����B�ȑO�̏�Ԃ�ێ�����ϐ��i�C���[�W�̓t���b�v�t���b�v��H�j
	bool _IsSelected = false;

	//! �Z���N�g�E�B���h�E������ꂽ�u�Ԃ��@�m����B�Z���N�g�E�B���h�E�������u�Ԃ̂݃R���g���[���̍X�V���K�v�B
	bool _IsClosed = false;

	//! �ЂƂO�̃V�[���ɖ߂邩��I�����邽�߂̕ϐ��B
	bool isReturn = false;

	//! �Z���N�g�E�B���h�E���g�p����ׂ̑O�����̊֐��B
	const bool updateSelectWindow();

public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	SelectWindow(std::shared_ptr<ISceneChanger> _changer) : changerInSelectWindow(_changer) {};
	~SelectWindow() = default;

	//! �Z���N�g�E�B���h�E��L���ɂ���ׂ̊֐��B
	void ValidSelectWindow();

	//! �Z���N�g�E�B���h�E��\������֐��B
	void drawSelectWindow() const;

	//! ���݃Z���N�g�E�B���h�E���L���ɂȂ��Ă��邩�ǂ������m�F���邽�߂̊֐��B
	bool const IsSelected() const { return _IsSelected; }

	//! �Z���N�g�E�B���h�E�̗�������m�F���邽�߂̊֐��B
	bool const IsSelectWindow_Closed() const { return _IsClosed; }
};