#include "PredictStageShift.h"

Dimention PredictStageShift::update(shared_ptr<Stage> stage, shared_ptr<Player> player, Dimention shiftinStage)
{
	Dimention fixedShiftingStage = shiftinStage;
	
	//�Ƃ肠�����A�v���C���[�̒�݂̂𒲂ׂ�(2020/06/13)
	int playerBottom = player->getStatus()._y + player->getToBottom();
	int predictBottom = playerBottom - shiftinStage.y;

	int deffOfPredictBottomAndBlockHead = 0;

	int centralX = player->getStatus()._x + shiftinStage.x;

	// �����̒�𒲂ׂ�
	//DrawCircle(centralX, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX, predictBottom - 1, stage)) {//y���W��1�������
		int blockHead = stage->getBlockCell(centralX, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;//�v�Z�̂��߂̍��W�́uy���W��1�������v�̂����2���i��Ɉ����̂ŉ������j
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX, predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
	}
	
	// �E�̒�𒲂ׂ�
	//DrawCircle(centralX + player->getToRight() - 1, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX + player->getToRight() - 1, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(centralX + player->getToRight() - 1, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX + player->getToRight() -1, predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
	}

	// ���̒�𒲂ׂ�
	//DrawCircle(centralX - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX - player->getToLeft(), predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(centralX - player->getToLeft(), predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
	}
	
	return fixedShiftingStage;

}

bool PredictStageShift::IsDetectedStage(int x, int y, shared_ptr<Stage> stage)
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