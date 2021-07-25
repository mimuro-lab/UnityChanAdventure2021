#pragma once

#include "Singleton.h"
#include <vector>
#include <DxLib.h>

using namespace std;

class ImagePath_Object :
	public Singleton<ImagePath_Object>
{
	ImagePath_Object() = default;
	friend Singleton< ImagePath_Object >;
public:

	//! characterActionAction�̉摜�ւ̃p�X���܂Ƃ߂��ϐ��B
	const vector<int> bulletNormal = {
		LoadGraph("images/Object/Bullet/bullet_normal.jpg")
	};

};