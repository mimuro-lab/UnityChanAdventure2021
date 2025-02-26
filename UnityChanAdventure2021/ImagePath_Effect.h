#pragma once

#include "Singleton.h"
#include <vector>
#include <DxLib.h>

using namespace std;

class ImagePath_Effect :
	public Singleton<ImagePath_Effect>
{
	ImagePath_Effect() = default;
	friend Singleton< ImagePath_Effect >;
public:

	//! characterActionActionの画像へのパスをまとめた変数。
	vector<int> star_pink;

	//LoadDivGraph("images/Effect/pipo-mapeffect011.png", 20, 5, 5, 120, 120, bulletNormal);
	//LoadDivGraph("images/Effect/pipo-mapeffect011.png", 20, 5, 4, 120, 120, bulletNormal);
	void load() {
		int _bulletNormal[25];
		LoadDivGraph("images/Effect/star/120/pipo-mapeffect011h.png", 20, 5, 4, 120, 120, _bulletNormal);
		vector<int> vec(begin(_bulletNormal), end(_bulletNormal));
		star_pink = vec;
	}

};