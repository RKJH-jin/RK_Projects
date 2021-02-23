#include "stdafx.h"
#include "CollisionManager.h"

#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::LRUDCollision(GameObject* character, GameObject* obj)
{
	vector3 interVector; // 교차점을 담을 벡터
	/*====================================================================
								위 / 아래 충돌
	====================================================================*/
	//==================================위==================================//
	if (character->prePos.z > character->pos.z) // 플레이어가 위쪽으로 움직였을 때
	{
		if (obj->bottomPlane[2].getEnd().x < character->shadow.RT.x &&
			character->shadow.LT.x < obj->bottomPlane[2].getStart().x) // 오브젝트의 x 범위 안에 들어왔을 때
		{
			if (character->shadow.RT.z < obj->bottomPlane[2].getEnd().z &&
				obj->bottomPlane[2].getEnd().z < character->shadow.RB.z) // 윗변이 오브젝트의 밑면을 넘어가면
			{
				if (character->preShadow.LT.z >= obj->bottomPlane[2].getStart().z) // 밑에서 위로 올라간거면
				{
					character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
				}
			}
		}
		else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // 윗변 선분이 교차하면
				{
					if (character->shadow.LT.x < interVector.x)
					{
						character->pos.x = interVector.x + character->shadow.width / 2; // 교차 점에서 오른쪽으로 보정
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector) ||
					Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector)) // 윗변 선분이 좌측 선분과 교차하면
				{
					if (character->shadow.RT.x > interVector.x)
					{
						character->pos.x = interVector.x - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
				}
			}
		}
	}
	//==================================아래==================================//
	else if (character->prePos.z < character->pos.z) // 플레이어가 아래로 움직였을 때
	{
		if (obj->bottomPlane[0].getStart().x < character->shadow.RB.x &&
			character->shadow.LB.x < obj->bottomPlane[0].getEnd().x) // 오브젝트의 x 범위 안에 들어왔을 때
		{
			if (character->shadow.LT.z < obj->bottomPlane[0].getStart().z &&
				obj->bottomPlane[0].getStart().z < character->shadow.LB.z) // 밑변이 오브젝트의 윗변을 넘어가면
			{
				if (character->preShadow.LB.z <= obj->bottomPlane[0].getStart().z)	// 위에서 아래로 내려가면
				{
					character->pos.z = obj->bottomPlane[0].getStart().z - character->shadow.height / 2;
				}
			}
		}
		else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||
					Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector)) // 밑변 선분이 좌측변이랑 교차하면
				{
					if (interVector.x < character->shadow.RB.x)
					{
						character->pos.x = interVector.x - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector)) // 밑변 선분이 좌측변이랑 교차하면
				{
					if (interVector.x > character->shadow.LB.x)
					{
						character->pos.x = interVector.x + character->shadow.width / 2; // 교차 점에서 오른쪽으로 보정
					}
				}
			}
		}
	}
	/*====================================================================
								좌 / 우 충돌
	====================================================================*/
	//==================================좌==================================//
	if (character->prePos.x > character->pos.x) // 플레이어가 왼쪽으로 움직였을 때
	{
		if (obj->bottomPlane[1].getStart().z < character->shadow.LB.z &&
			character->shadow.LT.z < obj->bottomPlane[1].getEnd().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (character->preShadow.RB.z < obj->bottomPlane[2].getStart().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &tempV)) // 좌측변이 밑변과 겹쳤을 때(1차 보정)
					{
						character->pos.x = obj->bottomPlane[2].getStart().x + character->shadow.width / 2;
					}
				}

				if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // 좌측 선분이 우측변이랑 교차하면
					Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &interVector))	   // 좌측 선분이 윗변이랑 교차하면 
				{
					if (obj->bottomPlane[1].getStart().z < character->shadow.LT.z) // 그림자 윗변이 오브젝트 윗변보다 아래에 있을 경우
					{
						character->pos.x = obj->bottomPlane[1].getX(character->shadow.LT.z) + character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 윗변이 오브젝트 윗변보다 위에 있을 경우
					{
						if (character->preShadow.LB.z == character->shadow.LB.z)
						{
							character->pos.x = obj->bottomPlane[1].getStart().x + character->shadow.width / 2;
						}
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (character->preShadow.LB.z > obj->bottomPlane[0].getStart().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &tempV)) // 좌측변이 윗변과 겹쳤을 때(1차 보정)
					{
						character->pos.x = obj->bottomPlane[0].getEnd().x + character->shadow.width / 2;
					}
				}

				if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // 좌측 선분이 우측변이랑 교차하면
					Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &interVector))	   // 좌측 선분이 밑변이랑 교차하면 
				{
					if (character->shadow.LB.z < obj->bottomPlane[2].getStart().z) // 그림자 밑변이 오브젝트 밑변보다 위에 있을 경우
					{
						character->pos.x = obj->bottomPlane[1].getX(character->shadow.LB.z) + character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 밑변이 오브젝트 밑변보다 아래에 있을 경우
					{
						if (character->preShadow.LB.z == character->shadow.LB.z)
						{
							character->pos.x = obj->bottomPlane[1].getEnd().x + character->shadow.width / 2;
						}
					}
				}
			}
		}
	}
	//==================================우==================================//
	else if (character->prePos.x < character->pos.x) // 플레이어가 오른쪽으로 움직였을 때
	{
		if (obj->bottomPlane[0].getStart().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[2].getEnd().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (character->preShadow.RT.z > obj->bottomPlane[0].getEnd().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &tempV)) // 우측 선분이 오브젝트의 윗변과 겹치면(1차보정)
					{
						character->pos.x = obj->bottomPlane[0].getStart().x - character->shadow.width / 2;
					}
				}

				if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // 우측 선분이 좌측변이랑 교차하면
					Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &interVector))		// 우측 선분이 밑변이랑 교차하면
				{
					if (character->shadow.RB.z < obj->bottomPlane[2].getEnd().z) // 그림자 밑변이 오브젝트 밑변보다 위에 있을 경우
					{
						character->pos.x = obj->bottomPlane[3].getX(character->shadow.RB.z) - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 밑변이 오브젝트 밑변보다 아래에 있을 경우
					{
						character->pos.x = obj->bottomPlane[3].getStart().x - character->shadow.width / 2;
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (character->preShadow.RT.z < obj->bottomPlane[2].getStart().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &tempV)) // 우측 선분이 오브젝트의 밑변과 겹치면(1차보정)
					{
						character->pos.x = obj->bottomPlane[2].getEnd().x - character->shadow.width / 2;
					}
				}
				if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // 우측 선분이 좌측변이랑 교차하면
					Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &interVector))		// 우측 선분이 윗변이랑 교차하면
				{
					if (character->shadow.RT.z > obj->bottomPlane[0].getStart().z) // 그림자 윗변이 오브젝트 윗변보다 밑에 있을 경우
					{
						character->pos.x = obj->bottomPlane[3].getX(character->shadow.RT.z) - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 윗변이 오브젝트 윗변보다 위에 있을 경우
					{

							character->pos.x = obj->bottomPlane[3].getEnd().x - character->shadow.width / 2;
						
					}
				}
			}
		}
	}
}

void CollisionManager::objectCollision()
{
	wallCollsion();
	GameObject* character = _stageM->getPlayer()->getPObj();
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (character->pos.y > 0) character->pos.y = 0;
	for (int i = 0; i < vObj.size(); ++i)
	{
		GameObject* obj = vObj[i]->getObj();

		if (obj->group == OBJECT_GROUP::OBJECT)
		{
			if (_stageM->getPlayer()->getInfo().isSky) // 공중에 있을 때
			{
				// 오브젝트와 겹치면
				if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// 캐릭터의 z값이 윗변보다 밑에 있고
					character->shadow.LT.z < obj->bottomPlane[2].getStart().z &&					// 캐릭터의 z값이 밑변보다 위에 있고
					obj->bottomPlane[3].getX(character->shadow.RB.z) < character->shadow.RB.x &&	// 캐릭터의 x값이 좌측변보다 우측에 있고
					character->shadow.LT.x < obj->bottomPlane[1].getX(character->shadow.LT.z))		// 캐릭터의 x값이 우측변보다 좌측에 있고
				{
					if (character->prePos.y < character->pos.y) // 낙하 중일 때
					{
						if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
							character->pos.y <= obj->topPlane[0].getStart().y + 5) // 해당 범위에 들어가면
						{
							// y값 보정
							character->pos.y = obj->topPlane[0].getStart().y;
							// 상태보정
							_stageM->getPlayer()->setPlatform(obj);
							_stageM->getPlayer()->setState(_stageM->getPlayer()->getInfo().preState);
							_stageM->getPlayer()->setJumpPower(0);
							_stageM->getPlayer()->setIsSky(false);
						}
						else if (character->pos.y > obj->topPlane[0].getStart().y + 5) // 낙하 중 오브젝트 높이보다 낮을 때
						{
							LRUDCollision(character, obj);
						}
					}
					else if (character->pos.y < character->prePos.y) // 점프 중일 때 
					{
						if (obj->topPlane[0].getStart().y < character->pos.y) // 오브젝트 높이보다 낮으면 충돌처리
						{
							LRUDCollision(character, obj);
						}
					}
				}
				// 오브젝트와 안겹쳤을때 (필요한가?)
				else
				{
					if (obj->topPlane[0].getStart().y < character->pos.y) // 오브젝트 높이보다 낮으면 충돌처리
					{
						LRUDCollision(character, obj);
					}
				}
			}
			else // 공중이 아닐 때(isSky == false)
			{
				if (character->pos.y == 0) // 지면일 때
				{
					LRUDCollision(character, obj);
				}
				else // 지면이 아닐 때(오브젝트 위일 때)
				{
					if (_stageM->getPlayer()->getPlatform() != nullptr)
					{
						if (_stageM->getPlayer()->getPlatform()->bottomPlane[0].getStart().z > character->shadow.LB.z ||					// 벗어나면
							character->shadow.LT.z > _stageM->getPlayer()->getPlatform()->bottomPlane[2].getStart().z ||					// 벗어나면
							_stageM->getPlayer()->getPlatform()->bottomPlane[3].getX(character->shadow.RB.z) > character->shadow.RB.x ||	// 벗어나면
							character->shadow.LT.x > _stageM->getPlayer()->getPlatform()->bottomPlane[1].getX(character->shadow.LT.z) ||	// 벗어나면
							character->shadow.LT.x > _stageM->getPlayer()->getPlatform()->bottomPlane[0].getEnd().x ||						// 벗어나면
							character->shadow.RB.x < _stageM->getPlayer()->getPlatform()->bottomPlane[2].getEnd().x)						// 벗어나면
						{
							_stageM->getPlayer()->setState(PL_STATE::JUMP);
							_stageM->getPlayer()->setIsSky(true);

						}
					}
				}
			}
		}
	}
}

void CollisionManager::wallCollsion()
{
	GameObject* character = _stageM->getPlayer()->getPObj();
	vector<tagWall> vLeftWall = _stageM->getStage()->getLeftWall();
	vector<tagWall> vRightWall = _stageM->getStage()->getRightWall();
	vector<tagWall> vBackWall = _stageM->getStage()->getBackWall();
	tagWall floor = _stageM->getStage()->getFloor();

	vector3 interVector;
	for (int i = 0; i < vBackWall.size(); ++i) // 플레이어 위쪽 최대치 (뒷 벽 충돌)
	{
		if (character->shadow.LT.z < vBackWall[i].LB.z)
		{
			if (character->shadow.RT.x > vBackWall[i].LB.x &&
				character->shadow.LT.x < vBackWall[i].RB.x)
			{
				character->pos.z = vBackWall[i].LB.z + character->shadow.height / 2;
			}
		}
	}

	for (int i = 0; i < vLeftWall.size(); ++i)
	{
		if (character->preShadow.LT.z < vLeftWall[i].LB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vLeftWall[i].RB, vLeftWall[i].LB), &interVector))  // 그림자 윗변이 왼쪽 벽이랑 교차하면
			{
				character->pos.x = interVector.x + character->shadow.width / 2;
			}
		}
	}

	for (int i = 0; i < vRightWall.size(); ++i)
	{
		if (character->preShadow.RT.z < vRightWall[i].RB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vRightWall[i].LB, vRightWall[i].RB), &interVector))  // 그림자 윗변이 오른쪽 벽이랑 교차하면
			{
				character->pos.x = interVector.x - character->shadow.width / 2;
			}
		}
	}

	// 바닥과 충돌
	if (character->shadow.LB.z > floor.LB.z) // 플레이어 아래쪽 최대치 (바닥 충돌)
	{
		character->pos.z = floor.LB.z - character->shadow.height / 2;
	}
	if (character->shadow.LB.x < floor.LT.x) // 바닥 왼쪽
	{
		character->pos.x = floor.LT.x + character->shadow.width / 2;
	}
	if (character->shadow.RB.x > floor.RT.x) // 바닥 오른쪽
	{
		character->pos.x = floor.RT.x - character->shadow.width / 2;
	}

}
