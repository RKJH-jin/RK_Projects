#pragma once
#include "Scene.h"
#include <string>
/*====================================================================
	상점 씬입니다. 게임 씬과 데이터가 연동되어야 하므로 Data Manager를 이용합니다.
====================================================================*/
class shopItem
{
public:
	image* _img;
	string _name;
	string _explain;
	int _price;
	int _heal;
};

class ShopScene : public Scene
{
	vector<shopItem> _vShopItem;
	int _index;
	image* _select;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void ItemSet();
	void KeyInput();
};

