
/*!
@file Singleton.h
@brief Singleton�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/20:06
@author mimuro
*/

#pragma once

template <typename _T>

/*!
@class Singleton
@brief �I�u�W�F�N�g��������Ȃ�����񑩂���V���O���g���N���X�Bpublic Singleton<class _T>�ƌp������ƌp�����N���X���V���O���g���ɂȂ�B
@date 2020/04/16/20:08
@author mimuro
*/
class Singleton {
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	Singleton(const Singleton& r) = default;
	Singleton& operator=(const Singleton& r) = default;

public:
	static _T* getIns() {
		static _T inst;
		return &inst;
	}
};