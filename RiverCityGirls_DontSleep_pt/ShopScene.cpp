#include "stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init()
{
	/*====================================================================
		상점 씬에서 입장에 연출을 진행합니다. 배경음악을 넣어줍니다.
	====================================================================*/
	SOUND_M->playMusic("shopBG");

	/*====================================================================
		맵의 사이즈를 지정합니다.
	====================================================================*/
	_background = IMG_M->findImage("shop_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================
		상점에 아이템을 추가합니다.
	====================================================================*/
	ItemSet();
	_index = 0;



	return S_OK;
}

void ShopScene::release()
{
}

void ShopScene::update()
{
	KeyInput();
}

/*====================================================================
	배경과 아이템, 가격 정보 등을 렌더합니다.
====================================================================*/
void ShopScene::render()
{
	_background->render(getMapDC());

	_select->render(getMapDC(), 1010 - _index * 15, 280 + 80 * _index);

	//폰트에 대해 설정한다.
	SetBkMode(getMapDC(), TRANSPARENT);
	SetTextColor(getMapDC(), RGB(0, 0, 0));
	HFONT font, oldFont;

	//메뉴얼
	font = CreateFont(30, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(getMapDC(), font);
	TextOut(getMapDC(), 50, 650, "B:구입 / X:나가기", strlen("B:구입 / X:나가기"));

	//상점 아이템의 이미지와 텍스트를 출력한다.
	for (int i = 0; i < 4; i++)
	{
		if(i==_index)SetTextColor(getMapDC(), RGB(255, 255, 255));
		if(i!=_index)SetTextColor(getMapDC(), RGB(0, 0, 0));

		//이미지
		_vShopItem[i]._img->render(getMapDC(), 880 - i * 15, 250 + 80 * i);

		//이름과 가격
		font = CreateFont(30, 0, -70, 0, 0, false, false, false,
			DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
		oldFont = (HFONT)SelectObject(getMapDC(), font);
		TextOut(getMapDC(), 930 - i * 15, 230 + 80 * i, _vShopItem[i]._name.c_str(), strlen(_vShopItem[i]._name.c_str()));
		TextOut(getMapDC(), 1050 - i * 15, 250 + 80 * i, to_string(_vShopItem[i]._price).c_str(), strlen(to_string(_vShopItem[i]._price).c_str()));

		//설명
		font = CreateFont(20, 0, -70, 0, 0, false, false, false,
			DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
		oldFont = (HFONT)SelectObject(getMapDC(), font);
		TextOut(getMapDC(), 930 - i * 15, 270 + 80 * i, _vShopItem[i]._explain.c_str(), strlen(_vShopItem[i]._explain.c_str()));
	}

	//폰트를 삭제한다.
	DeleteObject(font);
}

/*====================================================================
	상점에서 판매하는 아이템을 설정합니다.
====================================================================*/
void ShopScene::ItemSet()
{
	for (int i = 0; i < 4; i++)
	{
		shopItem item;
		_vShopItem.push_back(item);
	}
	_vShopItem[0]._img = IMG_M->findImage("shop_aloe");
	_vShopItem[0]._name = "알로에";
	_vShopItem[0]._explain = "20 회복 / 알로에 맛이 나는 음료수";
	_vShopItem[0]._price = 200;
	_vShopItem[0]._heal = 20;

	_vShopItem[1]._img = IMG_M->findImage("shop_hamburger");
	_vShopItem[1]._name = "햄버거";
	_vShopItem[1]._explain = "40 회복 / 참개빵 위에 순쇠고기 패티 두장";
	_vShopItem[1]._price = 400;
	_vShopItem[1]._heal = 40;

	_vShopItem[2]._img = IMG_M->findImage("shop_icecream");
	_vShopItem[2]._name = "아이스크림";
	_vShopItem[2]._explain = "10 회복 / 아이스크림이 얹어진 초코 파르페";
	_vShopItem[2]._price = 100;
	_vShopItem[2]._heal = 10;

	_vShopItem[3]._img = IMG_M->findImage("shop_tempura");
	_vShopItem[3]._name = "덴푸라";
	_vShopItem[3]._explain = "80 회복 / 매점에서 이런 걸 왜 팔지";
	_vShopItem[3]._price = 800;
	_vShopItem[3]._heal = 80;

	_select = IMG_M->findImage("ShopScene_list");
}

/*====================================================================
	키 입력으로 물건을 선택해 구입하거나 나갑니다.
====================================================================*/
void ShopScene::KeyInput()
{
	if (KEY_M->isOnceKeyDown(VK_DOWN))
	{
		SOUND_M->playSFX("menu_cursor");
		_index++;
		if (_index >= 4) _index = 3;
	}

	if (KEY_M->isOnceKeyDown(VK_UP))
	{
		SOUND_M->playSFX("menu_cursor");
		_index--;
		if (_index < 0) _index = 0;
	}

	//구입
	if (KEY_M->isOnceKeyDown('B'))
	{
		int price = _vShopItem[_index]._price;
		int heal = _vShopItem[_index]._heal;
		if (DATA_M->minusPlayerCoin(price))
		{
			SOUND_M->playSFX("menu_confirm");
			DATA_M->plusPlayerHP(heal);
		}
	}

	//나가기
	if (KEY_M->isOnceKeyDown('X'))
	{
		SCENE_M->setPrevScene();
		CAMERA_M->SetMap(*this, IMG_M->findImage("normalStage"));
		DATA_M->loadStageData();
		/*====================================================================
		배경음악을 넣어줍니다.
		====================================================================*/
		SOUND_M->playMusic("hardStageBG");
	}
}
