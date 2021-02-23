#include "stdafx.h"
#include "MapToolScene.h"
#include "UpperUI.h"
#include "Character.h"
#include "HelperUI.h"
void MapToolScene::AddUI()
{
	_vUI.push_back(new HelperUI);
	_vUI.push_back(new UpperUI);

	_descriptionUI = new DescriptionUI;
	_infoUI = new InfoUI;
	_infoUI->SetActive(false);

	addUnderBarUI("지형", Vector2(50, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 0, 0);
	addUnderBarUI("벽", Vector2(110, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 1, 0);
	addUnderBarUI("물품", Vector2(170, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonGreen"), 3, 0);
	addUnderBarUI("지역", Vector2(230, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonGray"), 0, 0);

	addUnderBarUI("인원", Vector2(1140, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 6, 0);
	addUnderBarUI("해고", Vector2(1200, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonOrange"), 1, 0);

	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//지형
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//벽
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//물품
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//지역

	addUnderBarWindowUI(Vector2(1140, WINSIZEY - 275), Vector2(200, 400), 0.7f);	//인원
	addUnderBarWindowUI(Vector2(1140, WINSIZEY - 275), Vector2(0, 0), 0.7f);		//해고

	for (int i = 0; i < 6; ++i) setLinkUnderBarUI(i, i);

	// 오브젝트 버튼 유아이 추가
	map<string, TileAttribute*>::iterator miTileObject;
	miTileObject = DATAMANAGER->GetMTileObject()->begin();

	int count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::TERRAIN)
		{
			addObjectButtonUIInWindowUI(
				0,                                          // 지형 인덱스
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage("terrain"),
				miTileObject->second->GetInfo()._frame
			);
			count++;
		}
		++miTileObject;
	}

	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::WALL)
		{
			addObjectButtonUIInWindowUI(
				1,                                          // 벽 윈도우창 인덱스
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage(miTileObject->second->GetKey()),
				Vector2(1, 3)
			);
			count++;
		}
		++miTileObject;
	}


	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::OBJECT)
		{
			addObjectButtonUIInWindowUI(
				2,                                          // 물품 윈도우창 인덱스
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage(miTileObject->second->GetKey()),
				Vector2(0, 0)
			);
			count++;
		}
		++miTileObject;
	}

	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::AREA)
		{
			addObjectButtonUIInWindowUI(
				3,                                          // 지역 윈도우창 인덱스
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage("buttonGray"),
				Vector2(0, 0)
			);
			count++;
		}
		++miTileObject;
	}

	//직원버튼
	map<string, Character*>::iterator miChar;
	miChar = DATAMANAGER->GetMCharacter()->begin();
	count = 0;
	for (; miChar != DATAMANAGER->GetMCharacter()->end(); ++miChar)
	{
		addObjectButtonUIInWindowUI(
			4,                                          // 직원 윈도우창 인덱스
			miChar->second->GetName(),
			miChar->second->GetKey(),
			Vector2(1065 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
			Vector2(48, 48),
			Vector2(72, 72),
			IMAGEMANAGER->FindImage(miChar->second->GetKey()),
			Vector2(0, 0)
		);
		count++;
	}

	// 시계 추가
	_clockUI = new ClockUI(Vector2(WINSIZEX / 2 + 550, WINSIZEY / 2 - 250), 0.8f, Vector2(200, 250));

	// 속도 조절 버튼 추가
	for (int i = 0; i < 5; ++i)
	{
		string name = "time_play" + to_string(i);
		addPlayButtonUI(name, Vector2(WINSIZEX / 2 + 475 + 35 * i, WINSIZEY / 2 - 150), Vector2(35, 24), 1.0f, IMAGEMANAGER->FindImage(name));
	}

	//하늘
	_sky = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY), Pivot::Center);
}


void MapToolScene::renderUI()
{
	//하늘
	if (19 <= DATAMANAGER->GetInfo().time.hour && DATAMANAGER->GetInfo().time.hour < 21)
	{
		D2DRenderer::GetInstance()->FillRectangle(_sky, D2D1::ColorF::DarkOrange, DATAMANAGER->GetInfo().skyAlpha);
	}
	else
	{
		D2DRenderer::GetInstance()->FillRectangle(_sky, D2D1::ColorF::DarkBlue, DATAMANAGER->GetInfo().skyAlpha);
	}

	//UI
	for (int i = 0; i < _vUI.size(); i++)
	{
		_vUI[i]->render();
	}

	//시계
	_clockUI->render();
	Vector2 vTemp = Vector2(WINSIZEX / 2, WINSIZEY - 10);
	IMAGEMANAGER->FindImage("screenEdge")->SetScale(0.7f);
	IMAGEMANAGER->FindImage("screenEdge")->SetAlpha(0.8f);
	IMAGEMANAGER->FindImage("screenEdge")->Render(vTemp);

	for (BarButtonUI* u : _vUnderBarUI)
	{
		u->render();
	}

	for (WindowUI* u : _vUnderBarWindowUI)
	{
		u->render();
	}

	for (PlayButtonUI* u : _vPlayButtonUI)
	{
		u->render();
	}

	_infoUI->render();
	_descriptionUI->render();
}

void MapToolScene::addUnderBarUI(string strName, Vector2 pos, float scale, Image * img)
{
	BarButtonUI* temp = new BarButtonUI(strName, pos, scale, img);
	temp->setIsRender(true);
	_vUnderBarUI.push_back(temp);
}

void MapToolScene::addUnderBarUI(string strName, Vector2 pos, float scale, Image * img, int frameX, int frameY)
{
	BarButtonUI* temp = new BarButtonUI(strName, pos, scale, img, frameX, frameY);
	temp->setIsRender(true);
	_vUnderBarUI.push_back(temp);
}

void MapToolScene::addUnderBarWindowUI(Vector2 pos, Vector2 size, float scale)
{
	WindowUI* temp = new WindowUI(pos, size, scale);
	_vUnderBarWindowUI.push_back(temp);
}

void MapToolScene::addObjectButtonUIInWindowUI(int arrNum, string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame = Vector2(0, 0))
{
	_vUnderBarWindowUI[arrNum]->addObjectButtonUI(strName, key, pos, rcSize, imgSize, img, frame);
}

void MapToolScene::setLinkUnderBarUI(int arrNum, int arrNum2)
{
	_vUnderBarUI[arrNum]->setLinkWindowUI(_vUnderBarWindowUI[arrNum2]);
}

void MapToolScene::addSingleUI(string strName, Vector2 pos, float scale, Image * img)
{

}

void MapToolScene::addPlayButtonUI(string strName, Vector2 pos, Vector2 size, float scale, Image* img)
{
	PlayButtonUI* temp = new PlayButtonUI(strName, pos, size, scale, img);
	_vPlayButtonUI.push_back(temp);
}