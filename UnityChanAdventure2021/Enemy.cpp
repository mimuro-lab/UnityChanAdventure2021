#include "Enemy.h"

void Enemy::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages)
{

	statusAsChara._y += shiftingStage.y;
	statusAsChara._x += shiftingStage.x;

	if (statusAsChara._x < 0 + deActiveLeft 
		|| statusAsChara._x > WIN_W + deActiveRight
		|| statusAsChara._y < 0 + deActiveHead
		|| statusAsChara._y > WIN_H + deActiveBottom)
		statusAsPara->isActive = false;
	else
		statusAsPara->isActive = true;

	if (!statusAsPara->isActive)
		return;


	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	collision->update(statusAsChara, _stage);
	collisionPoints = collision->getCollisionPoints();

	statusAsChara.isDead = !statusAsPara->isAlive;

	bool isDetectedDamages = false;
	isDetectedDamages = damagesOverlap->isOverlaped(collisionPoints, _damages, statusAsPara->isAlive);
	damagesOverlap->refreshDetectedDamageIndex();
	detectDmsInd = damagesOverlap->getDetectedDamageIndex();
	if (isDetectedDamages) {
		for (int i = 0;i < detectDmsInd.size(); i++) {
			//printfDx("%d\n",_damages[i]->getDamage());
			statusAsPara->acceptDamage(_damages[i]->getDamage());
		}
	}

	// Status�̍X�V�������s���B
	statusAsChara = animationMove->update(statusAsChara, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// �A�j���[�V�����̉��������s���B
	animation->update(statusAsChara);

	if (animation->isEnd() && animationSwitch->getNowAction() == characterAction::Death) {
		isEnd = true;
	}


	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	if (!isEnd) {
		animation = animationSwitch->update(collision, animation, statusAsChara, controller);
	}

	// �������X�V����B
	statusAsChara.directRight = enemyDirect->updateDirect(animationSwitch->getNowAction(), statusAsChara.directRight, statusAsChara, controller);

}

void Enemy::adjustBottom(int AdjustRange)
{
	statusAsChara._y += AdjustRange;
}

void Enemy::draw()
{
	//�X�e�[�^�X�֌W�̕`�揈��
	if (!isEnd) {
		statusAsPara->draw(statusAsChara._x + 20, statusAsChara._y - 50, 10, 60);
	}

	animation->draw();
	//collision->draw();

	//DrawFormatString(statusAsChara._x, statusAsChara._y, GetColor(255, 255, 255), "hp:%d", statusAsPara->HitPoint);

}

vector<shared_ptr<AbsDamageObj>> Enemy::generateDamageObj(vector<shared_ptr<AbsDamageObj>> _nowDmg, shared_ptr<Stage> stage)
{
	vector<shared_ptr<AbsDamageObj>> returnDmg = _nowDmg;

	if (animationSwitch->getNowAction() == characterAction::Hundgun_horizonal
		&& animation->getNowDrawingImageIndex() == 1
		&& animation->getDrawingStepsCounter() == 1
		) {
		shared_ptr<AbsDamageObj> pushObj = make_shared<Bullet>(stage, statusAsChara._x, statusAsChara._y, 20, statusAsChara.directRight);
		returnDmg.push_back(pushObj);
		//printfDx("%d\n", returnDmg.size());
	}

	int ind = animation->getNowDrawingImageIndex();
	int cnt = animation->getDrawingStepsCounter();
	/*
	// ���U��1�̃_���[�W�I�u�W�F�N�g�̐���
	if (animationSwitch->getNowAction() == characterAction::Soard1_init) {

		returnDmg = Sword1(playerStatus, stage, animation, returnDmg);

	}

	if (animationSwitch->getNowAction() == characterAction::Soard2_init) {

		returnDmg = Sword2(playerStatus, stage, animation, returnDmg);

	}

	if (animationSwitch->getNowAction() == characterAction::Soard3_init) {

		returnDmg = Sword3(playerStatus, stage, animation, returnDmg);

	}
	*/

	return returnDmg;
}