
/*!
@file PredictPoint.h
@brief PredictPoint�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/05/04/17:56
@author mimuro
*/

#pragma once

#include "Define.h"
#include "Pysical.h"
#include "CollisionDetect.h"

/*!
@class PredictPoint
@brief ���W���K�؂��ǂ����𔻒f���邽�߂̃N���X�B
@date 2020/05/04/17:59
@author mimuro
*/
using namespace Define;

class PredictPoint
{

	//! �X�V�O�̈ʒu
	Dimention nowPoint;

	//! ���̃R�}�ňʒu����ł��낤���W
	Dimention predictPoint;

	//! ���̍��W����A���̑��x�ɂ�莟�̍��W���v�Z����B
	Dimention calcPredictPoint(Dimention nowPoint, Dimention nowVelocity);

	//! ���������̈�ԋ߂��u���b�N�̈�ԋ߂��ӂ�X���W���擾����B
	int getForwardBlockNearSideHorizon(
		Dimention nowPoint,
		int predictRange,
		std::shared_ptr<CollisionDetect> _collision,
		std::shared_ptr<Stage> _stage
	);

	//! ���������̈�ԋ߂��u���b�N�̈�ԋ߂��ӂ�X���W���擾����B
	int getForwardBlockNearSideVertical(
		Dimention nowPoint,
		int predictRange,
		std::shared_ptr<CollisionDetect> _collision,
		std::shared_ptr<Stage> _stage
	);

public:
	PredictPoint() {
		predictPoint.x = predictPoint.y = 0;
		nowPoint.x = nowPoint.y =  0;
	}
	~PredictPoint() = default;

	//! �X�V�������s���֐��B
	Dimention update(Dimention nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	//! ���������ɓ����ꍇ�̓K�؂ȍ��W�̏C�����s���֐��B
	int fittingPointHorizon(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _verticalRange);

	//! ���������ɓ����ꍇ�̓K�؂ȍ��W�̏C�����s���֐��B
	int fittingPointVertical(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _horizonalRange);

};