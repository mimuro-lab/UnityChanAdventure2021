
/*!
@file SelectWindow.cpp
@brief SelectWindow�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/18/23:20
@author mimuro
*/

#include "SelectWindow.h"

/*!
@brief �Z���N�g�{�^���������ꂽ��Z���N�g�E�B���h�E���L���ɂȂ�B
@brief ����������true�A�r���Ŏ��s������false��Ԃ��B
@date 2020/04/18/23:22
@author mimuro
*/
const bool SelectWindow::updateSelectWindow()
{

	_preIsSelected = _IsSelected;

	if (Controller::getIns()->getPushSelect()) {
		_IsSelected = !_IsSelected;
	}

	if (_IsSelected) {
		if (Controller::getIns()->getPushRight())
			isReturn = false;
		if (Controller::getIns()->getPushLeft())
			isReturn = true;

		if (Controller::getIns()->getPush_A()) {
			if (isReturn)
				changerInSelectWindow->changeScene(eScene::eNone, true);
			else
			{
				isReturn = false;
				_IsSelected = false;
			}
		}
	}

	if (_preIsSelected && !_IsSelected)
		_IsClosed = true;
	else 
		_IsClosed = false;

	return true;
}

/*!
@brief �Z���N�g�E�B���h�E��\������B�֐����̕ϐ��̈�����const�Ƃ���B
@date 2020/04/18/23:23
@author mimuro
*/
void SelectWindow::drawSelectWindow() const
{
	if (!_IsSelected)
		return;
	DrawFormatString(100, 100, GetColor(255, 255, 255), "SelectWindow\n return to a previous scene?");

	unsigned int yesColor, noColor;
	yesColor = noColor = GetColor(255, 255, 255);

	if (isReturn)
		yesColor = GetColor(255, 0, 0);
	else
		noColor = GetColor(255, 0, 0);

	DrawFormatString(120, 150, yesColor, "yes");
	DrawFormatString(170, 150, noColor, "no");

}

/*!
@brief �p���悩�璼�ڌĂяo�����֐��BupdateSelectWindow()���AupdateSelectWindow()�Ɏ��s������return���Ĕ����o���B
@date 2020/04/18/23:23
@author mimuro
*/
void SelectWindow::ValidSelectWindow() 
{
	if (!updateSelectWindow())
		return;
}