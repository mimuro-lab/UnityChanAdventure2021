
/*!
@file Task.h
@brief Task�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/04/21/12:46
*/

#pragma once

/*!
@class Task
@brief update��draw�֐���K�����l�ɐݒ肷��C���^�[�t�F�[�X�N���X�B
@date 2020/04/21/12:46
*/
class Task {
public:
    virtual ~Task() {}
    //! �����������͎������Ă����Ȃ��Ă�����
    virtual void initialize() {}     
    //! �I�������͎������Ă����Ȃ��Ă�����
    virtual void finalize() {}     
    //! �X�V�����͕K���p����Ŏ�������
    virtual void update() = 0;   
    //! �`�揈���͕K���p����Ŏ�������
    virtual void draw() = 0;   
};