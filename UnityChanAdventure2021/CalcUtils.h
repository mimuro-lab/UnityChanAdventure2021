
/*!
@file CalcUtils.h
@brief CalcUtils�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/18/15:38
@author mimuro
*/

#pragma once

class CalcUtils final
{
public:
    CalcUtils() = delete;

    //! float�^�̕ϐ��̏����_�ȉ����l�̌ܓ�����֐��B
    static float roundPoint(float val, int point);
};