
/*!
@file Utils.cpp
@brief Utils�N���X�̃����o�ނ̒�`���s��CPP�t�@�C��
@date 2020/04/18/15:38\
@author mimuro
*/

#include "CalcUtils.h"
#include <cmath>
#include <DxLib.h>

/*!
@brief  val�̏����_��point�ʂ��l�̌ܓ����Ċۂ߂�B
@date 2020/04/18/15:41
@author mimuro
*/
float CalcUtils::roundPoint(float val, int point) {
    float ret;
    ret = val * pow(10.f, +point - 1);
    ret = (float)(int)(ret + 0.5f);
    return ret * pow(10.f, -point + 1);
}