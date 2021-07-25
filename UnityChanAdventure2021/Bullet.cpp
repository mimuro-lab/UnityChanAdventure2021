#include "Bullet.h"

void Bullet::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, Status playerStatus)
{
	livingCounter++;

	if (livingCounter < livingTime && !isDetectEnemy)
		isLive = true;
	else
		isLive = false;

	controller.clear();
	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	damageStatus._y += shiftingStage.y;
	damageStatus._x += shiftingStage.x;
	collision->update(damageStatus, _stage);

	collisionPoints = collision->getCollisionPoints();

	// Status�̍X�V�������s���B
	damageStatus = animationMove->update(damageStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// �A�j���[�V�����̉��������s���B
	animation->update(damageStatus);

	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	animation = animationSwitch->update(collision, animation, damageStatus, controller);

	// �������X�V����B
	damageStatus.directRight = damageDirect->updateDirect(animationSwitch->getNowAction(), damageStatus.directRight, damageStatus, controller);

}

void Bullet::draw()
{
	animation->draw();
	//collision->draw();
}

void Bullet::adjustBottom(int AdjustRange)
{
	damageStatus._y += AdjustRange;
}

void Bullet::detectEnemy() {
	isDetectEnemy = true;
}

void Bullet::detectPlayer() {
	isDetectEnemy = true;
}