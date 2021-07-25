
/*!
@file StartScene.cpp
@brief StartScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/20:01
@author mimuro
*/

#include "StartScene.h"

void StartScene::update()
{
	SelectScene();

	if (Controller::getIns()->getPush_A())
		GoNextScene();
}

void StartScene::draw()
{
	unsigned int gameTextColor, menuTextColor, configTextColor;

	gameTextColor = menuTextColor = configTextColor = GetColor(255, 255, 255);

	switch (nextSceneSelected) {
	case game:
		gameTextColor = GetColor(255, 0, 0);
		break;
	case menu:
		menuTextColor = GetColor(255, 0, 0);
		break;
	case config:
		configTextColor = GetColor(255, 0, 0);
		break;
	}
	DrawFormatString(50, 50, gameTextColor, "GAME");
	DrawFormatString(50, 70, menuTextColor, "MENU");
	DrawFormatString(50, 90, configTextColor, "CONF");
}


const void StartScene::SelectScene()
{
	if (Controller::getIns()->getPushDown()) {
		if (nextSceneSelected < _end - 1)
			nextSceneSelected++;
	}
	
	if (Controller::getIns()->getPushUp()) {
		if (nextSceneSelected > none + 1)
			nextSceneSelected--;
	}
}

const void StartScene::GoNextScene()
{
	switch (nextSceneSelected) {
	case game:
		changer->changeScene(eScene::eGameScene, false);
		break;
	case menu:
		changer->changeScene(eScene::eMenuScene, false);
		break;
	case config:
		changer->changeScene(eScene::eConfigScene, false);
		break;
	}

}