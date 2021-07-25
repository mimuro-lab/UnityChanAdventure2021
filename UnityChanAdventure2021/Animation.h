
/*!
@file Animation.h
@brief Animation�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/9:28
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Define.h"

/*!
@class Animation
@brief �摜���R�}����\�������������Ɏg�p����N���X�BimagePath�ɂ���摜�n���h����vector��n���ƃA�j���[�V�����̊Ǘ����s����B
@date 2020/04/18/23:13
@author mimuro
*/
class Animation
{
	//! �A�j���[�V�������������摜�Q�̉摜�n���h�����i�[����ϐ��B
	std::vector<int> imageHandles;
	//! update(x, y)���Ăяo�������_�̉摜�C���f�b�N�X�B�O����n�܂�B
	unsigned char NowDraiwngImageIndex = 0;
	//! update(x, y)���Ăяo�������_�̉摜�n���h���B
	int NowDrawingImageHandle = 0;
	//! �A�j���[�V������r���ŏI���������ɏI���̃C���f�b�N�X������ɐݒ肷��B�ݒ肵���C���f�b�N�X�͕\������Ȃ��B�Q�Ƃ����ꍇ�A�O�E�P�Ԗڂ̂ݕ\���B
	char DrawingIndexEnd = 99;
	//! ��̉摜��\��������X�e�b�v���B��j�P�Q�ɐݒ肷��ƂP�b�ԂɂT���̉摜���؂�ւ��B�i�U�Ofps�ŁA�P�Q�X�e�b�v�łP���X�V�j
	char DrawingSteps;
	//! DrawingSteps�𐔂��邽�߂̃J�E���^�[�B
	char DrawingSteps_counter = 0;
	//! �A�j���[�V������`�悷��Ƃ��A���������ɂ��炷���W�ʁB
	char DrawingShiftX = 0;
	//! �A�j���[�V������`�悷��Ƃ��A���������ɂ��炷���W�ʁB
	char DrawingShiftY = 0;
	//! �A�j���[�V�������I��������ǂ����B
	bool IsEnd = false;
	//! �A�j���[�V�����I�����ɉ摜��\���������邩�H
	bool IsEndDrawing = false;
	//! �A�j���[�V����������ׂ̃X�e�[�^�X�B
	Define::Status status;
	//! �摜�̊g��E�k���̔{��
	double scaleRate = 1.0;

	double rotation = 0;

public:

	/*!
	@brief �A�j���[�V�������������摜�Q�Ə������W�͕K���󂯎��B����ȊO�͔C�ӁB
	@date 2020/04/21/9:51
	@author mimuro
	*/
	Animation(std::vector<int> _imageHandles, Define::Status _status , char _DrwaingShiftX = 0, char _DrawingShiftY = 0
		, char _DrawingSteps = 6, char IndexEnd = 99, bool _IsEndDrawing = true, double _scaleRate = 1.0) :
		imageHandles(_imageHandles)
		, NowDrawingImageHandle(_imageHandles[0])
		, status(_status)
		, DrawingShiftX(_DrwaingShiftX)
		, DrawingShiftY(_DrawingShiftY)
		, DrawingIndexEnd(IndexEnd)
		, DrawingSteps(_DrawingSteps)
		, IsEndDrawing(_IsEndDrawing)
		, scaleRate(_scaleRate)
	{};
	~Animation() = default;

	//! �X�V������S���֐��B
	void update(Define::Status _status);
	//! �\��������S���֐��B
	void draw() const;
	//! �A�j���[�V�������I��������ǂ������擾����Btrue�Ȃ�I�������B
	const bool isEnd() const { return IsEnd; };
	//! �A�j���[�V���������ɖ߂��֐��B
	void refreshing();

	//! ����摜�ɂ�����A�����摜����莞�ԕ\�����邽�߂ɐ�����J�E���^�[
	const char getDrawingStepsCounter() { return DrawingSteps_counter; }
	//! �A�j���[�V�����ɂ�����A�\������摜�̔ԍ�
	const char getNowDrawingImageIndex() { return NowDraiwngImageIndex; }
	//! �摜�̖���
	const int getImagesSize() { return imageHandles.size(); }

	void arrangeScale(double rate) {
		scaleRate = rate;
	};

	double getScale() {
		return scaleRate;
	}

	//!�@���W�A���ł͂Ȃ��A360�x�\���œ���
	void arrangeRotation(double rota) {
		rotation = rota;
	}

};

