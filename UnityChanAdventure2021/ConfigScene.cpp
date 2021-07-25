
/*!
@file ConfigScene.cpp
@brief ConfigScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/19:53
@author mimuro
*/

#include "ConfigScene.h"

void ConfigScene::update()
{
	SelectWindow::ValidSelectWindow();
	SelectScene();
}

void ConfigScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "ConfigScene");
	SelectWindow::drawSelectWindow();
}

void ConfigScene::SelectScene()
{
}