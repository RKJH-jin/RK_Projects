#include "stdafx.h"
#include "JumpPointSearch.h"

#include "Tile.h"
#include "TileObject.h"
#include "TileMap.h"

JumpPointSearch::JumpPointSearch()
{
}

JumpPointSearch::~JumpPointSearch()
{
}

HRESULT JumpPointSearch::init()
{
	TILENUMX = _tileMap->GetCount().x;
	TILENUMY = _tileMap->GetCount().y;

	return S_OK;
}

void JumpPointSearch::release()
{
}

void JumpPointSearch::update()
{

}

void JumpPointSearch::render()
{

}


void JumpPointSearch::addOpenList(Tile* currentTile)
{

	linearLeft(currentTile);
	linearRight(currentTile);
	linearUp(currentTile);
	linearDown(currentTile);

	linearLU(currentTile);
	linearRU(currentTile);
	linearLD(currentTile);
	linearRD(currentTile);

}

void JumpPointSearch::pathFinder(Tile* currentTile)
{
	if (_vOpenList.empty()) return;

	Tile* temp = _vOpenList.top(); // 제일 앞에있는거 할당
	_vOpenList.pop();

	for (int i = 0; i < _vCloseList.size(); ++i) // 탐색했던 타일인지 확인
	{
		if (temp->GetIndex() == _vCloseList[i]->GetIndex()) // 탐색했던 타일이면 리턴?
		{
			return;
		}
	}

	_vCloseList.push_back(temp); // 꺼낸 노드를 닫힌 목록에 넣는다(탐색이 끝난 노드란 얘기)

	if (temp->GetIndex() == _endTile->GetIndex()) // 꺼낸 노드가 도착지라면
	{
		while (!_vOpenList.empty())
		{
			_vCloseList.push_back(_vOpenList.top());
			_vOpenList.pop();
		}

		_vResultList.push(_endTile->GetIndex());
		Tile* saveTile = _endTile->GetParentTile();

		while (true)
		{
			if (saveTile->GetParentTile() == nullptr) break;
			_vResultList.push(saveTile->GetIndex());
			saveTile = saveTile->GetParentTile();
		}

		return; // 도착했으니 종료
	}


	switch (temp->GetDirection())
	{
	case SEARCHDIRECTION::LEFT:
		if (temp->GetIndex().y == 0)
		{
			linearLeft(temp);
			linearLD(temp);
		}
		else if (temp->GetIndex().y == TILENUMY - 1)
		{
			linearLeft(temp);
			linearLU(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearLU(temp);
				linearLeft(temp);
				linearLD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true)
			{
				linearLU(temp);
				linearLeft(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearLeft(temp);
				linearLD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::RIGHT:
		if (temp->GetIndex().y == 0)
		{
			linearRight(temp);
			linearRD(temp);
		}
		else if (temp->GetIndex().y == TILENUMY - 1)
		{
			linearRight(temp);
			linearRU(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearRU(temp);
				linearRight(temp);
				linearRD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true)
			{
				linearRU(temp);
				linearRight(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearRight(temp);
				linearRD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::UP:
		if (temp->GetIndex().x == 0)
		{
			linearUp(temp);
			linearRU(temp);
		}
		else if (temp->GetIndex().x == TILENUMX - 1)
		{
			linearLU(temp);
			linearUp(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearLU(temp);
				linearUp(temp);
				linearRU(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == true)
			{
				linearLU(temp);
				linearUp(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearUp(temp);
				linearRU(temp);
			}
		}
		break;
	case SEARCHDIRECTION::DOWN:
		if (temp->GetIndex().x == 0)
		{
			linearDown(temp);
			linearRD(temp);
		}
		else if (temp->GetIndex().x == TILENUMX - 1)
		{
			linearDown(temp);
			linearLD(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearLD(temp);
				linearDown(temp);
				linearRD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == true)
			{
				linearLD(temp);
				linearDown(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearDown(temp);
				linearRD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::UPPERLEFT:
		linearLU(temp);
		linearLeft(temp);
		linearUp(temp);
		linearRU(temp);
		linearLD(temp);
		break;
	case SEARCHDIRECTION::UPPERRIGHT:
		linearRU(temp);
		linearRight(temp);
		linearUp(temp);
		linearLU(temp);
		linearRD(temp);
		break;
	case SEARCHDIRECTION::LOWERLEFT:
		linearLD(temp);
		linearLeft(temp);
		linearDown(temp);
		linearRD(temp);
		linearLU(temp);
		break;
	case SEARCHDIRECTION::LOWERRIGHT:
		linearRD(temp);
		linearRight(temp);
		linearDown(temp);
		linearLD(temp);
		linearRU(temp);
		break;
	}

	_currentTile = temp; // 현재 노드를 바꿔줍니다
}


stack<Vector2> JumpPointSearch::PathFinding(Vector2 start, Vector2 end)
{
	_startTile = _tileMap->GetvTile()[start.y * TILENUMX + start.x];
	_currentTile = _startTile;
	_endTile = _tileMap->GetvTile()[end.y * TILENUMX + end.x];

	addOpenList(_currentTile);


	//길찾기
	while (!_vOpenList.empty())
	{
		pathFinder(_currentTile);
	}

	//타일 정보 리셋
	for (int i = 0; i < _vCloseList.size(); ++i)
	{
		_vCloseList[i]->ResetInfo();
	}
	_vCloseList.clear();

	//swap으로 메모리 해제
	vector<Tile*> swapTemp;
	swapTemp.swap(_vCloseList);

	priority_queue<Tile*, vector<Tile*>, compare> swapPriTemp;
	swapPriTemp.swap(_vOpenList);

	stack<Vector2> resTemp;
	resTemp.swap(_vResultList);

	return resTemp;
}


/*=============================================================

						상하좌우 함수

==============================================================*/
void JumpPointSearch::linearLeft(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0) break; // 인덱스 예외처리

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX - count)];
		if (node->GetTileEmpty() == false) break; // 탐색 조건 - 벽 (비어있지 않으면)

		// 탐색 조건 - 분기
		if (node->GetIndex().x - 1 >= 0)
		{
			// 반시계 방향 확인
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::LEFT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::LEFT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRight(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX + count)];
		if (node->GetTileEmpty() == false) break; // // 탐색 조건 - 벽 (비어있지 않으면)

		// 탐색 조건 - 분기
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			// 반시계 방향 확인
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::RIGHT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::RIGHT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::RIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearUp(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + startX];
		if (node->GetTileEmpty() == false) break; // // 탐색 조건 - 벽

		// 탐색 조건 - 분기
		if (node->GetIndex().y - 1 >= 0)
		{
			// 반시계 방향 확인
			if (node->GetIndex().x - 1 > 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::UP;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().x + 1 <= TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::UP;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UP;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearDown(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY + count >= TILENUMY) break;

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + startX]; // 확인할 노드 선언
		if (node->GetTileEmpty() == false) break; // 탐색 조건 - 벽

		// 탐색 조건 - 분기
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			// 반시계 방향 확인
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::DOWN;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::DOWN;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::DOWN;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

/*=============================================================

						대각선 함수

==============================================================*/
void JumpPointSearch::linearLU(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0 || startY - count < 0) break;                                                        // 이동할 위치가 인덱스를 벗어나면

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + (startX - count)];           // 이동하고
		if (node->GetTileEmpty() == false) break;                                                                   // 이동한 위치가 막힌 곳이면
		if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false) break; // 대각선이 막혀있어 실제로는 이동이 불가한 경우

		// 탐색 조건 - 분기
		bool counterClockwise = false;
		bool clockwise = false;

		// 반시계 방향 탐색
		if (node->GetIndex().x - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// 시계 방향 탐색
		if (node->GetIndex().y - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // 분기가 맞으면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // 둘 다 막혀있으면

		CHECKDIVERGENT checkValue1 = subLinearLeft(node);
		CHECKDIVERGENT checkValue2 = subLinearUp(node);

		// 탐색 조건 - 대각선 전용 분기
		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)       //분기를 만났으면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)              //목적지에 도착했다면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRU(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX || startY - count < 0) break;                                                // 이동할 위치가 인덱스를 벗어나면

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + (startX + count)];                                    // 이동하고
		if (node->GetTileEmpty() == false) break;                                                                   // 이동한 위치가 막힌 곳이면
		if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false) break; // 대각선이 막혀있어 실제로는 이동이 불가한 경우

		// 탐색 조건 - 분기
		bool counterClockwise = false;
		bool clockwise = false;

		// 반시계 방향 탐색
		if (node->GetIndex().y - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// 시계 방향 탐색
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // 분기가 맞으면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // 둘 다 막혀있으면

		// 탐색 조건 - 대각선 전용 분기
		CHECKDIVERGENT checkValue1 = subLinearRight(node);
		CHECKDIVERGENT checkValue2 = subLinearUp(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)           // 분기를 만났다면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)                  // 목적지에 도착했다면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearLD(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0 || startY + count >= TILENUMY) break;                                                    // 이동할 위치가 인덱스를 벗어나면

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + (startX - count)];                                        // 이동하고
		if (node->GetTileEmpty() == false) break;                                                                       // 이동한 위치가 막힌 곳이면
		if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false) break;     // 대각선이 막혀있어 실제로는 이동이 불가한 경우

		// 탐색 조건 - 분기
		bool counterClockwise = false;
		bool clockwise = false;

		// 반시계 방향 탐색
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// 시계 방향 탐색
		if (node->GetIndex().x - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // 분기가 맞으면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // 둘 다 막혀있으면

		// 탐색 조건 - 대각선 전용 분기
		CHECKDIVERGENT checkValue1 = subLinearLeft(node);
		CHECKDIVERGENT checkValue2 = subLinearDown(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRD(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;


	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX || startY + count >= TILENUMY) break;                                          // 이동할 위치가 인덱스를 벗어나면

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + (startX + count)];                           // 이동하고
		if (node->GetTileEmpty() == false) break;                                                                     // 이동한 위치가 막힌 곳이면
		if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false) break;   // 대각선이 막혀있어 실제로는 이동이 불가한 경우

		// 탐색 조건 - 분기
		bool counterClockwise = false;
		bool clockwise = false;

		// 반시계 방향 탐색
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// 시계 방향 탐색
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // 분기가 맞으면
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // 둘 다 막혀있으면

		// 탐색 조건 - 대각선 전용 분기
		CHECKDIVERGENT checkValue1 = subLinearRight(node);
		CHECKDIVERGENT checkValue2 = subLinearDown(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

/*=============================================================

					대각선 보조 탐색 함수

==============================================================*/
CHECKDIVERGENT JumpPointSearch::subLinearLeft(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX - count)];
		if (node->GetTileEmpty() == false) break;

		// 탐색 조건 - 분기
		if (node->GetIndex().x - 1 >= 0)
		{
			// 반시계 방향 확인
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearRight(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX + count)];
		if (node->GetTileEmpty() == false) break;

		// 탐색 조건 - 분기
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			// 반시계 방향 확인
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearUp(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY - count)* TILENUMX + (startX)];
		if (node->GetTileEmpty() == false) break;

		// 탐색 조건 - 분기
		if (node->GetIndex().y - 1 >= 0)
		{
			// 반시계 방향 확인
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearDown(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY + count >= TILENUMY) break;

		Tile* node = _tileMap->GetvTile()[(startY + count)* TILENUMX + (startX)];
		if (node->GetTileEmpty() == false) break;

		// 탐색 조건 - 분기
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			// 반시계 방향 확인
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// 시계 방향 확인
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// 탐색 조건 - 종점
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

