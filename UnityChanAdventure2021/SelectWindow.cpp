
/*!
@file SelectWindow.cpp
@brief SelectWindowクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/18/23:20
@author mimuro
*/

#include "SelectWindow.h"

/*!
@brief セレクトボタンが押されたらセレクトウィンドウが有効になる。
@brief 成功したらtrue、途中で失敗したらfalseを返す。
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
@brief セレクトウィンドウを表示する。関数内の変数の扱いはconstとする。
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
@brief 継承先から直接呼び出される関数。updateSelectWindow()し、updateSelectWindow()に失敗したらreturnして抜け出す。
@date 2020/04/18/23:23
@author mimuro
*/
void SelectWindow::ValidSelectWindow() 
{
	if (!updateSelectWindow())
		return;
}