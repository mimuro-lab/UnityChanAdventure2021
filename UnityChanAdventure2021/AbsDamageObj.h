#pragma once
#include "Stage.h"
#include "Define.h"
#include <memory>
#include <vector>

class AbsDamageObj
{
protected:
	bool isLive = true;
	bool isDetectEnemy = false;

	// [side][number]
	// side��0,1,2,3������Ahead,bottom,right,left
	// number�́Ahead,bottom�͍�����E�Aright,left�͏ォ�牺
	vector<vector<Define::Dimention>> collisionPoints;

public:
	AbsDamageObj() = default;
	~AbsDamageObj() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	virtual void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) = 0;

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	virtual void draw() = 0;

	const bool getIsLive() { return isLive; }

	virtual void adjustBottom(int AdjustRange) = 0;

	virtual vector<vector<Dimention>> getCollisionPoints() = 0;

	virtual vector<int> getRange() = 0;

	virtual void detectEnemy() = 0;

	virtual void detectPlayer() = 0;

	virtual int getDamage() = 0;

};

