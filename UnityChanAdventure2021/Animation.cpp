
/*!
@file Animation.cpp
@brief Animation�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/21/9:53
@author mimuro
*/

#include "Animation.h"

/*!
@brief ���Ăяo�����ƂɃA�j���[�V�������P�R�}�i�߂�B���̃R�}�ł�Status�������Ŏ󂯎��B
@par �摜�t�@�C���QimageHandles��S�ĕ\�����邩�ADrawingIndexEnd�𒴂���܂ōX�V����B
@date 2020/04/21/9:56
@author mimuro
*/
void Animation::update(Define::Status _status)
{
	status = _status;

	if (NowDraiwngImageIndex >= imageHandles.size()|| NowDraiwngImageIndex > DrawingIndexEnd) {
		IsEnd = true;
		return;
	}

	NowDrawingImageHandle = imageHandles[NowDraiwngImageIndex];
	
	DrawingSteps_counter++;
	DrawingSteps_counter %= DrawingSteps;
	
	if(DrawingSteps_counter == 0)
		NowDraiwngImageIndex++;
}

void Animation::refreshing()
{
	NowDraiwngImageIndex = 0;
	IsEnd = false;
	DrawingSteps_counter = 0;
}

/*!
@brief update�֐��Ō��߂��`��Ώۂ̉摜��\������BIsEnd��true���ƕ\������߂�B
@date 2020/04/21/9:57
@author mimuro
*/
void Animation::draw() const
{
	
	if (IsEnd && !IsEndDrawing)
		return;
	//printfDx("%d\n", NowDraiwngImageIndex);
	DrawRotaGraph(status._x + DrawingShiftX, status._y + DrawingShiftY, scaleRate, rotation * 2 * Define::PI / 360, NowDrawingImageHandle, true, !status.directRight);
}