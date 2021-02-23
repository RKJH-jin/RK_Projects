#include "stdafx.h"
#include "MapManager.h"
#include "StuffObject.h"
#include "Character.h"

HRESULT MapManager::init()
{
	//타일 맵을 세팅한다.
	_tileMap = new TileMap;
	_tileMap->init();
	_tileMap->SetTileMap(Vector2(TILECOUNTX, TILECOUNTY));
    JPSMANAGER->SetLinkTileMap(_tileMap);
    JPSMANAGER->init();


	

	return S_OK;
}

void MapManager::release()
{
	_tileMap->release();

	delete _tileMap;

}

void MapManager::update()
{
	_tileMap->update();


	//캐릭터
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vCharacter[i]->update();
	}
}

void MapManager::render()
{
	_tileMap->render();

	//사람들
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vYOrderObject.push_back(_vCharacter[i]);
	}

	// 짐 오브젝트 렌더
	for (int i = 0; i != _vStuffObj.size(); i++)
	{
		_vStuffObj[i]->render();
	}

	//Y_ORDER에 따라 렌더한다.
	RenderYOrder();
}

StuffObject * MapManager::FindStuffObject(string key)
{
	for (int i = 0; i < _vStuffObj.size(); i++)
	{
		if (_vStuffObj[i]->GetName() == key)
		{
			return _vStuffObj[i];
		}
	}
	return nullptr;
}

void MapManager::CreateCharacter(Vector2 pos, Character * obj)
{
	obj->GetTransform()->SetPosition(pos);
	_vCharacter.push_back(obj);
}

void MapManager::DeleteCharacter(int index)
{
	delete _vCharacter[index];
	_vCharacter.erase(_vCharacter.begin() + index);
}

void MapManager::SortYOrder(int s, int e)
{
	if (s >= e) return;
	float pivot = _vYOrderObject[s]->GetTransform()->GetPosition().y;
	int left = s;
	int right = e;

	while (left <= right)
	{
		//left와 pivot을 비교, left가 작으면 ++
		while (_vYOrderObject[left]->GetTransform()->GetPosition().y < pivot) ++left;

		//right와 pivot을 비교, left가 크면 --
		while (_vYOrderObject[right]->GetTransform()->GetPosition().y > pivot) --right;

		//left와 right 둘을 스왑해 정렬해 나간다.
		if (left <= right)
		{
			swap(_vYOrderObject[left], _vYOrderObject[right]);
			++left; --right;
		}
	}

	//재귀함수로 좌우를 끝까지 퀵 정렬한다.
	SortYOrder(s, right);
	SortYOrder(left, e);
}

void MapManager::RenderYOrder()
{

	// 벡터가 비었으면 return한다.
	if (_vYOrderObject.empty()) return;

	//벡터의 원소를 처음부터 끝까지 정렬한다.
	SortYOrder(0, _vYOrderObject.size() - 1);


	//이미지를 렌더한다.
	for (int i = 0; i < _vYOrderObject.size(); i++)
	{
		_vYOrderObject[i]->Render();
	}

	//캐릭터
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vCharacter[i]->render();
	}
	//벡터를 비운다.
	_vYOrderObject.clear();
}
