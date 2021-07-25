
/*!
@file CollisionDetect.cpp
@brief CollisionDetect�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/16:36
@author mimuro
*/

#include "CollisionDetect.h"

/*!
@par ����E�����E�E���E�����̓����蔻��𒲂ׂ�֐��B����return���Ȃ��B
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::update(Define::Status __nowStatus, std::shared_ptr<Stage> __stage)
{

	Define::Status statusForInside = __nowStatus;
	//��̂߂荞�݂𒲂ׂ�
	statusForInside._y++;

	collisionedInSide.head = detectHead(__stage, statusForInside);

	statusForInside._y--;

	//���̂߂荞�݂𒲂ׂ�
	statusForInside._y--;

	collisionedInSide.bottom = detectBottom(__stage, statusForInside);

	statusForInside._y++;
	//�E�̂߂荞�݂𒲂ׂ�
	statusForInside._x++;

	collisionedInSide.right = detectHead(__stage, statusForInside);

	statusForInside._x--;

	//���̂߂荞�݂𒲂ׂ�
	statusForInside._x--;

	collisionedInSide.left = detectBottom(__stage, statusForInside);

	statusForInside._x++;

	_stage = __stage;
	nowStatus = __nowStatus;

	collisionedSide.head = detectHead(__stage, __nowStatus);

	collisionedSide.bottom = detectBottom(__stage, __nowStatus);

	// �����A������ɂ߂荞��ł�����A���E�̓����蔻��͂Ȃ��B�i�߂荞�񂾏�ԂōX�V����邩���΂ɓ�����������ɂȂ��Ă��܂��j
	if (!collisionedInSide.bottom ) {

		collisionedSide.right = detectRight(__stage, __nowStatus);

		collisionedSide.left = detectLeft(__stage, __nowStatus);
	}
	else {
		printfDx("");
	}
}

vector<vector<Dimention>> CollisionDetect::getCollisionPoints()
{
	vector<vector<Dimention>> returnPoints;

	Dimention initCell;
	initCell.x = initCell.y = 0;

	vector<Dimention> Head(headPoints+1, initCell);
	returnPoints.push_back(Head);

	vector<Dimention> Bottom(bottomPoints+1, initCell);
	returnPoints.push_back(Bottom);

	vector<Dimention> Right(rightPoints+1, initCell);
	returnPoints.push_back(Right);

	vector<Dimention> Left(leftPoints+1, initCell);
	returnPoints.push_back(Left);



	//head
	for (int i = 0; i < headPoints; i++) {
		// �u���b�N��0 �` blockHeight - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		returnPoints[0][i].x = x;
		returnPoints[0][i].y = y;
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	returnPoints[0][headPoints].x = x;
	returnPoints[0][headPoints].y = y;

	//bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		returnPoints[1][i].x = x;
		returnPoints[1][i].y = y;
	}

	x = nowStatus._x + toRight - 1;
	y = nowStatus._y + toBottom;
	returnPoints[1][bottomPoints].x = x;
	returnPoints[1][bottomPoints].y = y;

	//right
	for (int i = 0; i <= rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		returnPoints[2][i].x = x;
		returnPoints[2][i].y = y;
	}
	x = nowStatus._x + toRight;
	y = nowStatus._y + toBottom - 1;
	returnPoints[2][rightPoints].x = x;
	returnPoints[2][rightPoints].y = y;

	//left
	for (int i = 0; i <= leftPoints; i++) {
		// �u���b�N��0 �` blockWidth - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		returnPoints[3][i].x = x;
		returnPoints[3][i].y = y;
	}
	x = nowStatus._x - toLeft - 1;
	y = nowStatus._y + toBottom - 1;
	returnPoints[3][leftPoints].x = x;
	returnPoints[3][leftPoints].y = y;

	return returnPoints;
}

/*!
@par �E���̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectRight(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i <= rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}
	int x = nowStatus._x + toRight;
	int y = nowStatus._y + toBottom - 1;
	if (IsDetectedStage(x, y, _stage))
		return true;
	return false;
}

/*!
@par �����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectLeft(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i <= leftPoints; i++) {
		// �u���b�N��0 �` blockWidth - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}
	int x = nowStatus._x - toLeft - 1;
	int y = nowStatus._y + toBottom - 1;
	if (IsDetectedStage(x, y, _stage))
		return true;
	return false;
}

/*!
@par ����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectHead(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i < headPoints; i++) {
		// �u���b�N��0 �` blockHeight - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		if (IsDetectedStage(x, y, stage))
			return true;
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	if (IsDetectedStage(x, y, stage))
		return true;
	return false;
}
/*!
@par �����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectBottom(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}

	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y + toBottom;
	if (IsDetectedStage(x, y, stage))
		return true;
	return false;
}

/*!
@par �����蔻��̕`����s���֐��B�����Ԃ��Ȃ��B
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::draw()
{
	// head
	for (int i = 0; i <= headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	unsigned int color = GetColor(0, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(255,0,  0);
	DrawCircle(x, y, 2, color, false);

	// bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / bottomPoints) * i;
		int y = nowStatus._y + toBottom;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255,0,  0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x + toRight - 1;
	y = nowStatus._y + toBottom;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor( 255,0, 0);
	DrawCircle(x, y, 2, color, false);
	

	// right
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x + toRight;
	y = nowStatus._y + toBottom - 1;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(255, 0, 0);
	DrawCircle(x, y, 2, color, false);

	// left
	for (int i = 0; i <= leftPoints; i++) {
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x - toLeft - 1;
	y = nowStatus._y + toBottom - 1;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(0, 255, 0);
	DrawCircle(x, y, 2, color, false);
}

/*!
@par x,y���W�ɃX�e�[�W�̃u���b�N�����邩�ǂ����B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::IsDetectedStage(int x, int y, shared_ptr<Stage> stage)
{
	// x, y���W���X�e�[�W�̂ǂ̃C���f�b�N�X�ɒl���邩�H
	unsigned char _CellXNum = (x - stage->getPointLeftUpX()) / stage->getBlockWidth() - stage->getAbsIndInitDrawingLeftUpX();
	unsigned char _CellYNum = (y - stage->getPointLeftUpY()) / stage->getBlockHeight() - stage->getAbsIndInitDrawingLeftUpY();

	//�X�e�[�W�䂩��͂ݏo��Ȃ�ǂɏՓ˂����Ƃ������ƁB
	if (_CellXNum < 0 || _CellYNum < 0 || _CellXNum >= stage->getBlockXNum() || _CellYNum >= stage->getBlockYNum()) {
		return false;
	}

	// �����Ax, y�ɂ���X�e�[�W�̗v�f��block��������Փ˂Ɣ���B
	if (stage->getStage()[_CellXNum][_CellYNum]._status == Define::BlockCell::cellStatus::block) {
		return true;
	}

	// �ǂ��ɂ��Փ˂��Ȃ����false��Ԃ��B
	return false;
}

/*!
@par ���������ɂ����āA_to�̕�����_range����ɏ�ǂ����邩�ǂ����𔻒f����֐��B
@brief _range��1�u���b�N���𒴂��Ă�����A_to�̕�������_range�܂ł̊Ԃ��u���b�N�̗L���𔻒肷��B
@date 2020/05/04/16:57
@author mimuro
*/
bool CollisionDetect::calcShitingCollisionedSideVertical(toShiftDirect _to, char _range, char _horizonal_range)
{
	isCollisionedEdge = false;
	// �p��x���W
	int edge_x = nowStatus._x;
	// �E�����Ȃ�
	if (_horizonal_range > 0) {
		edge_x = nowStatus._x + toRight + std::abs(_horizonal_range);
	}
	else if (_horizonal_range < 0) {
		edge_x = nowStatus._x - toLeft - std::abs(_horizonal_range);
	}

	// range��0��������1��𒲂ׂ�
	if (_range == 0) {
		switch (_to) {
			case toShiftDirect::head:
				for (int i = 0; i <= headPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y - toHead - 1;
					if (IsDetectedStage(x, y, _stage)) 
						return true;
				}
				return false;
				break;
			case toShiftDirect::bottom:
				for (int i = 0; i < bottomPoints - 1; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y + toBottom + 1;
					if (IsDetectedStage(x, y, _stage))
						return true;
				}
				return false;
				break;
		}
		return false;
	}

	// _range���u���b�N�̕��𒴂��Ă��܂��Ă�����A�v���C���[�I�u�W�F�N�g��Botton����_stage->blockHeight�����ǂ̗L���𒲂ׂ�B

	unsigned char BlocksIn_range = 1;//_range�̒��ɂ����̃u���b�N�����邩�H

	if (_range > _stage->blockHeight)
		BlocksIn_range = _range / _stage->blockHeight;

	switch (_to) {
	case toShiftDirect::head:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++) {

			for (int i = 0; i < headPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y - toHead - block * _stage->blockHeight - std::abs(_range);
				//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x + toRight - 1;
			int y = nowStatus._y - toHead - block * _stage->blockHeight - std::abs(_range);
			//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			// �p�𒲂ׂ�
			//DrawCircle(edge_x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(edge_x, y, _stage)) {
				isCollisionedEdge = true;
				//return true;
			}
		}
		return false;
		break;
	case toShiftDirect::bottom:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < bottomPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + block * _stage->blockHeight + std::abs(_range);
				//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
				if (IsDetectedStage(x, y, _stage)) {
					collisionSideRange.bottom = block * _stage->blockHeight;
					return true;
				}
			}	
			int x = nowStatus._x + toRight - 1;
			int y = nowStatus._y + toBottom + block * _stage->blockHeight + std::abs(_range);
			//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(x, y, _stage))
				return true;
			// �p�𒲂ׂ�
			//DrawCircle(edge_x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(edge_x, y, _stage)) {
				isCollisionedEdge = true;
				//return true;
			}
		}
		return false;
		break;
	}
	
	//�G���[�����A�Ƃ肠�����Ԃ����Ă��鎖�ɂ���BcalcShitingCollisionedSideHorizon
	return true;
}

/*!
@par ���������ɂ����āA_to�̕�����_range����ɏ�ǂ����邩�ǂ����𔻒f����֐��B
@brief _range��1�u���b�N���𒴂��Ă�����A_to�̕�������_range�܂ł̊Ԃ��u���b�N�̗L���𔻒肷��B
@date 2020/05/04/16:58
@author mimuro
*/
bool CollisionDetect::calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range, char _vertical_range)
{
	// �p��y���W
	int edge_y = nowStatus._y;
	isCollisionedEdge = false;
	// �������Ȃ�
	if (_vertical_range > 0) {
		edge_y = nowStatus._y + toBottom + std::abs(_vertical_range);
	}
	// ������Ȃ�
	else if (_vertical_range < 0) {
		edge_y = nowStatus._y - toHead - std::abs(_vertical_range);
	}

	// range��0��������A1��̍��W�𒲂ׂ�B
	if (_range == 0) {
		switch (_to) {
		case CollisionDetect::toShiftDirect::left:
				for (int i = 0; i < leftPoints - 1; i++) {
					int x = nowStatus._x - toLeft - 1;
					int senceHeight = (toHead + toBottom) / rightPoints;
					int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
					if (IsDetectedStage(x, y, _stage))
						return true;
				}
			break;
		case CollisionDetect::toShiftDirect::right:
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			break;
		}
	}

	Status calcStatus;

	// _range���u���b�N�̕��𒴂��Ă��܂��Ă�����A�v���C���[�I�u�W�F�N�g��Botton����_stage->blockWidth�����ǂ̗L���𒲂ׂ�B
	unsigned char BlocksIn_range = 1;//_range�̒��ɂ����̃u���b�N�����邩�H

	if (std::abs(_range) > _stage->blockWidth)
		BlocksIn_range = std::abs(_range) / _stage->blockWidth + 1;

	switch (_to) {
	case toShiftDirect::right:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x + toRight + _range + Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i;
				//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x + toRight + std::abs(_range) - Define::blockWidth * block;
			int y = nowStatus._y + toBottom - 1;
			//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			//�p�𒲂ׂ�
			//DrawCircle(x, edge_y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, edge_y, _stage)) {
				//return true;
				isCollisionedEdge = true;
			}
		}
		break;

	case toShiftDirect::left:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < leftPoints; i++) {
				int x = nowStatus._x - toLeft - std::abs(_range) - Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i;
				//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x - toLeft - std::abs(_range) - Define::blockWidth * block;
			int y = nowStatus._y + toBottom - 1;
			//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			//�p�𒲂ׂ�
			//DrawCircle(x, edge_y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, edge_y, _stage)) {
				//return true;
				isCollisionedEdge = true;
			}
		}
		break;
	}

	//�G���[�����A�Ƃ肠�����Ԃ����Ă��鎖�ɂ���B
	return false;
}

/*!
@par _to�̕����́A���S���W����̓����蔻��͈̔͂�Ԃ��֐��B
@date 2020/05/04/16:59
@author mimuro
*/
const char CollisionDetect::getRange(toShiftDirect _to)
{
	switch (_to) {
	case toShiftDirect::head:
		return toHead;
		break;
	case toShiftDirect::bottom:
		return toBottom;
		break;
	case toShiftDirect::right:
		return toRight;
		break;
	case toShiftDirect::left:
		return toLeft;
		break;
	}
	return 0;
}