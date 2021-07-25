#include "EnemyLoad.h"

EnemyType EnemyLoad::getType(int _readValue)
{
	switch (_readValue) {
	case 0:
		return EnemyType::Enemy1;
		break;
	case 1:
		return EnemyType::Enemy2;
		break;
	}
	return EnemyType::_end;
}

bool EnemyLoad::getAlive(int _readValue)
{
	if (_readValue == 1)
		return true;
	if (_readValue == 0)
		return false;

	return true;
}

EnemyLoad::EnemyLoad()
{


	FILE* fp;
	fopen_s(&fp, "Stage/Enemy/sample_enemy.csv", "r");

	if (fp == NULL) {

		("�t�@�C�����J���܂���ł���(in StageLoad::loadCsv)");
		exit(1);
	}

	string csvCell = {};

	int cellEnemy[5] = {};

	int ind = 0;

	while (!feof(fp)) {
		int getf = fgetc(fp);

		// ���W�̍X�V
		if (getf == ',') {// �C����������Wx������₷
			//int l = stoi(csvCell);
			cellEnemy[ind] = stoi(csvCell);
			ind++;
			csvCell.clear();
		}
		else if (getf == '\n') {// ���s����������Wy������₷
			EnemyElement ele;
			ele.type = getType(cellEnemy[0]);
			ele.x = cellEnemy[1];
			ele.y = cellEnemy[2];
			ele.isAlive = getAlive(cellEnemy[3]);
			ele.hitPoint = cellEnemy[4];
			elements.push_back(ele);
			ind = 0;
		}
		else {// �C�ł����s�ł��Ȃ����A�v�f��ǂݍ��񂾂Ƃ������Ȃ̂ŁA
			
			char value;

			value = getf;

			csvCell.push_back(value);

		}
	}

	fclose(fp);
}