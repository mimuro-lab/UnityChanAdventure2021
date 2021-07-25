
/*!
@file MenuScene.cpp
@brief MenuScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/03:02
@author mimuro
*/

#include "MenuScene.h"

void MenuScene::update()
{
	SelectWindow::ValidSelectWindow();
	SelectScene();
}

void MenuScene::draw()
{
	DrawFormatString(10, 50, GetColor(255,255,255), "MenuScene");
}

void MenuScene::SelectScene()
{
	SelectWindow::drawSelectWindow();
}