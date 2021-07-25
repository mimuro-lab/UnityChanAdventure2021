
/*!
@file GameScene.cpp
@brief GameScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

/*!
@brief �v���C���[�I�u�W�F�N�g�̍��W�X�V�A�A�j���[�V�����̏����Ȃǂ��s���B
@date 2020/04/21/12:36
@author mimuro
@callgraph
*/
void GameScene::update()
{
	
	ValidSelectWindow();
	counterUpdate();

	if (IsSelected())
		return;	
	
	// �Z���N�g�E�B���h�E�������u�Ԃ̂݃R���g���[���̍X�V���s���B���̏u�Ԃ̓R���g���[����push�i�����ꂽ�u�Ԃ̏�ԁj�͖����������B
	if(IsSelectWindow_Closed())
		Controller::getIns()->update();
	
	// �K���Z���N�g�E�B���h�E���J����Ă��Ȃ�����O��Ƃ���B�I�u�W�F�N�g�̎Q�ƃG���[���o��B
	player->update(stage, dmgObjFromEnemy);	

	Dimention shiftingStage = predictStageShift->update(stage, player, player->getShiftingState());

	// �X�e�[�W����
	stage->update(shiftingStage, player->getStatus());

	// �v���C���[�̒ꂪ�߂荞��ł����甭���i�O�ȊO�̒l��Ԃ��j
	deffOfStageAndBottom = player->adjustStageAndBottom(stage);

	//adjust�����Ă���֐��̓v���C���[���߂荞�񂾍ۂ́u�����o���v�Ɋւ��鏈��

	//stage->adjustBottom(deffOfStageAndBottom);

	//player->adjustStageAndBottom(stage);
	
	// player�ɂ��_���[�W�v�f�̐���
	damageObjs = player->generateDamageObj(damageObjs,stage);

	// �_���[�W�v�f�̍X�V�B
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		//damageObjs[i]->adjustBottom(deffOfStageAndBottom);
		damageObjs[i]->update(stage, shiftingStage, player->getStatus());
	}


	// ���ʂȃ_���[�W�v�f�̏���
	vector<shared_ptr<AbsDamageObj>> refreshedObjs;
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		if (damageObjs[i]->getIsLive())
			refreshedObjs.push_back(damageObjs[i]);
	}

	damageObjs = refreshedObjs;

	// �G�I�u�W�F�N�g�̍X�V
	for (unsigned int i = 0; i < enemys.size(); i++) {
		//enemys[i]->adjustBottom(deffOfStageAndBottom);
		enemys[i]->update(stage, shiftingStage, damageObjs);
		vector<shared_ptr<AbsDamageObj>> addDmg;
		addDmg = enemys[i]->generateDamageObj(addDmg, stage);
		for (unsigned int j = 0; j < addDmg.size(); j++) {
			dmgObjFromEnemy.push_back(addDmg[j]);
		}
	}

	// �G�����������U���v�f���X�V
	for (unsigned int i = 0; i < dmgObjFromEnemy.size(); i++) {
		dmgObjFromEnemy[i]->update(stage, shiftingStage, player->getStatus());
	}
	// ���ʂȍU���v�f�̍폜
	vector<shared_ptr<AbsDamageObj>> deletedDmg;
	for (unsigned int i = 0; i < dmgObjFromEnemy.size(); i++) {
		if (dmgObjFromEnemy[i]->getIsLive())
			deletedDmg.push_back(dmgObjFromEnemy[i]);
	}
	dmgObjFromEnemy = deletedDmg;


	//// �G�I�u�W�F�N�g�ɂԂ������_���[�W�v�f�͍폜
	vector<shared_ptr<AbsDamageObj>> nonDetectEnemyDmgs;// ������̃_���[�W�v�f
	vector<int> deleteInd;// �폜�Ώۂ̃C���f�b�N�X���i�[����ϐ�
	// �폜�Ώۂ̃C���f�b�N�X�𒊏o����B
	for (unsigned int i = 0; i < enemys.size(); i++)
	{
		for (unsigned int j = 0; j < enemys[i]->getDetectedDamagesIndex().size(); j++) {
			deleteInd.push_back(enemys[i]->getDetectedDamagesIndex()[j]);
		}
	}
	sort(deleteInd.begin(), deleteInd.end());
	deleteInd.erase(std::unique(deleteInd.begin(), deleteInd.end()), deleteInd.end());
	// �C���f�b�N�X�̃_���[�W�v�f�ɂԂ������������s�킹��B
	for (unsigned int i = 0; i < deleteInd.size(); i++) {
		damageObjs[deleteInd[i]]->detectEnemy();
	}

	//// �v���C���[�ɂԂ������_���[�W�v�f�i�G�������������́j�͍폜
	vector<shared_ptr<AbsDamageObj>> nonDetectEnemyDmgsFromEnemy;// ������̃_���[�W�v�f
	vector<int> deleteIndFromEnemy;// �폜�Ώۂ̃C���f�b�N�X���i�[����ϐ�
	// �폜�Ώۂ̃C���f�b�N�X�𒊏o����B
	for (unsigned int j = 0; j < player->getDetectedDamagesIndex().size(); j++) {
		deleteIndFromEnemy.push_back(player->getDetectedDamagesIndex()[j]);
	}
	sort(deleteIndFromEnemy.begin(), deleteIndFromEnemy.end());
	deleteIndFromEnemy.erase(std::unique(deleteIndFromEnemy.begin(), deleteIndFromEnemy.end()), deleteIndFromEnemy.end());
	// �C���f�b�N�X�̃_���[�W�v�f�ɂԂ������������s�킹��B
	for (unsigned int i = 0; i < deleteIndFromEnemy.size(); i++) {
		dmgObjFromEnemy[deleteIndFromEnemy[i]]->detectPlayer();
	}

}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	stage->draw();

	for (unsigned int i = 0; i < enemys.size(); i++) {
		if(enemys[i]->getStatusAsParameter()->isActive)
			enemys[i]->draw();
	}

	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		//if (damageObjs[i]->getIsLive())
			damageObjs[i]->draw();
	}
	
	for (unsigned int i = 0; i < dmgObjFromEnemy.size();i++) {
		dmgObjFromEnemy[i]->draw();
	}

	player->draw();
	
	SelectWindow::drawSelectWindow();
}
