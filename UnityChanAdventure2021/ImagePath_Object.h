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

	//! characterActionActionの画像へのパスをまとめた変数。
	const vector<int> bulletNormal = {
		LoadGraph("images/Object/Bullet/bullet_normal.jpg")
	};

};