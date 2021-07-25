
/*!
@file ISceneChanger.h
@brief ISceneChanger�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/04/16/2:50
*/

#pragma once
#include "Define.h"

/*!
@class ISceneChanger
@brief SystemLooper�N���X������changeScene�����o�֐����O���N���X�Ŏg�p����ׂ̃C���^�[�t�F�[�X�B
@date 2020/04/16/2:50
*/
class ISceneChanger {
public:
	ISceneChanger() = default;
	~ISceneChanger() = default;
	//! ���̃N���X���p�������N���X�͕K�����̊֐����`���Ȃ���΂Ȃ�Ȃ��悤�ɖ񑩂���B
	virtual void changeScene(eScene Next, const bool stackPop) = 0;
};