#include "StageLoad.h"

vector<vector<BlockCell>> StageLoad::loadCsv(const char * csvFile, int loadInitXInd, int loadInitYInd, unsigned char loadWidth, unsigned char loadHeight)
{

	if (loadInitXInd < 0)
		return _nowStage;

	vector<vector<BlockCell>> _stage;

	BlockCell initCell;
	initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
	initCell._status = BlockCell::cellStatus::none;

	_stage.assign(blockXNum, vector<BlockCell>(blockYNum, initCell));

	// �e�v�f�̍��W��������

	for (int x = 0; x < loadWidth; x++) {
		for (int y = 0; y < loadHeight; y++) {
			_stage[x][y].x1 = loadInitXInd * blockWidth + x * blockWidth;
			_stage[x][y].x2 = _stage[x][y].x1 + blockWidth;
			_stage[x][y].y1 = loadInitYInd * blockHeight + y * blockHeight;
			_stage[x][y].y2 = _stage[x][y].y1 + blockHeight;
		}
	}

	FILE* fp;
	fopen_s(&fp, csvFile, "r");

	if (fp == NULL) {
		
		("�t�@�C�����J���܂���ł���(in StageLoad::loadCsv)");
		exit(1);
	}

	// CSV�t�@�C�������ォ��E���܂ň�s���ǂݍ��ށB���̎��̍��W�������B
	unsigned int x = 0;
	unsigned int y = 0;
	// �e�v�f�̃C���f�b�N�X��\���ϐ��B
	unsigned char elementInd = 0;

	// _stage�ɑ������Ƃ��Ɏg�p����C���f�b�N�X
	unsigned int _stageXInd = 0;
	unsigned int _stageYInd = 0;

	while (!feof(fp)) {
		int getf = fgetc(fp);

		// ���W�̍X�V
		if (getf == ',') {// �C����������Wx������₷
			x++;
			elementInd = 0;
		}
		else if (getf == '\n') {// ���s����������Wy������₷
			x = 0;
			y++;
			elementInd = 0;
			if(y > loadInitYInd)
				_stageYInd++;
			_stageXInd = 0;
		}
		else {// �C�ł����s�ł��Ȃ����A�v�f��ǂݍ��񂾂Ƃ������Ȃ̂ŁA
			elementInd++;
			int correctInt = getf - 48;

			// x��y���ǂݍ��ݔ͈͂Ȃ��ɂ����_stage�ɑ������B
			if (x >= loadInitXInd && x < (loadInitXInd + loadWidth)) {
				
				if (y >= loadInitYInd && y < (loadInitYInd + loadHeight)) {

					if(_stageXInd < blockXNum && _stageYInd < blockYNum)
						_stage[_stageXInd][_stageYInd]._status = getCellFromInt(correctInt);

					_stageXInd++;

				}
			}
		}
	}

	return _stage;

	fclose(fp);
}

BlockCell::cellStatus StageLoad::getCellFromInt(int inputInt)
{
	switch (inputInt) {
	case 1:
		return BlockCell::cellStatus::block;
		break;
	}

	//�@�ǂ�ɂ����Ă͂܂�Ȃ�������u���b�N����
	return BlockCell::cellStatus::none;
}

vector<vector<BlockCell>> StageLoad::loadFromFileInit()
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitXInd = 0;
	nowLoadInitYInd = 0;
	
	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileForward(unsigned int XInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitXInd += XInd;
	
	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

 	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileBackward(unsigned int XInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	// �������̎��_�ŁAnow��next���blockXNum���������B
	nowLoadInitXInd -= XInd;
	
	if (nowLoadInitXInd < 0)
		nowLoadInitXInd = 0;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileDwonSide(unsigned int YInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitYInd += YInd;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;
}

vector<vector<BlockCell>> StageLoad::loadFromFileUpSide(unsigned int YInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	// �������̎��_�ŁAnow��next���blockXNum���������B
	nowLoadInitYInd -= YInd;

	if (nowLoadInitYInd < 0)
		nowLoadInitYInd = 0;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}