
/*!
@file Fps.h
@brief Fps�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/18/23:02
@author mimuro
*/

#pragma once
#include <list>

/*!
@class Fps
@brief SystemLooper�N���X�̈�񓖂���̏����̎��Ԃ����ɂ���Fps�����S���N���X�B
@date 2020/04/18/23:03
@author mimuro
*/
class Fps {

public:
    Fps();
    void wait();
    void draw() const;

private:
    std::list<int> _list;
    float    _fps;
    unsigned _counter;

    void        updateAverage();
    void        regist();
    unsigned    getWaitTime() const;

};