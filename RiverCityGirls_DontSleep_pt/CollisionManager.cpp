#include "stdafx.h"
#include "CollisionManager.h"

#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::LRUDCollision(GameObject* character, GameObject* obj)
{
	checkLeft = checkRight = checkUp = checkDown = false;
	vector3 interVector; // 교차점을 담을 벡터
	if (obj->bottomPlane[0].getStart().y == 0)
	{
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
						if (obj->type == OBJECT_TYPE::LADDER)
						{
							if (obj->bottomPlane[2].getEnd().x < character->pos.x &&
								character->pos.x < obj->bottomPlane[2].getStart().x &&
								(GetAsyncKeyState(VK_UP) & 0x8001))
							{
								_stageM->getPlayer()->setIsClimb(true);
							}
							if (!(_stageM->getPlayer()->getInfo().isClimb))
							{
								character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
							}
						}
						else
						{
							character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
							checkUp = true;
						}
					}
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
				character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
						Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // 윗변,밑변 선분이 우측 선분과 교차하면
					{
						if (character->shadow.LT.x < interVector.x)
						{
							character->pos.x = interVector.x + character->shadow.width / 2; // 교차 점에서 오른쪽으로 보정
							checkUp = true;
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector) ||
						Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector)) // 윗변, 밑변 선분이 좌측 선분과 교차하면
					{
						if (character->shadow.RT.x > interVector.x)
						{
							character->pos.x = interVector.x - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
							checkUp = true;
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
						checkDown = true;
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
							checkDown = true;
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector) ||
						Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector)) // 밑변 선분이 좌측변이랑 교차하면
					{
						if (character->shadow.LB.x < interVector.x)
						{
							character->pos.x = interVector.x + character->shadow.width / 2; // 교차 점에서 오른쪽으로 보정
							checkDown = true;
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
			if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&
				character->shadow.LT.z < obj->bottomPlane[2].getEnd().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (character->preShadow.LT.z < obj->bottomPlane[2].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &tempV)) // 좌측변이 밑변과 겹쳤을 때(1차 보정)
						{
							character->pos.x = obj->bottomPlane[2].getStart().x + character->shadow.width / 2;
							checkLeft = true;
						}
					}

					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // 좌측 선분이 우측변이랑 교차하면
						Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &interVector))	   // 좌측 선분이 윗변이랑 교차하면 
					{
						if (obj->bottomPlane[0].getEnd().z < character->shadow.LT.z) // 그림자 윗변이 오브젝트 윗변보다 아래에 있을 경우
						{
							character->pos.x = obj->bottomPlane[1].getX(character->shadow.LT.z) + character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
							checkLeft = true;
						}
						else // 그림자 윗변이 오브젝트 윗변보다 위에 있을 경우
						{
							if (character->preShadow.LB.z > obj->bottomPlane[0].getEnd().z)
							{
								character->pos.x = obj->bottomPlane[1].getStart().x + character->shadow.width / 2;
								checkLeft = true;
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
							checkLeft = true;
						}
					}

					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // 좌측 선분이 우측변이랑 교차하면
						Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &interVector))	   // 좌측 선분이 밑변이랑 교차하면 
					{
						if (obj->bottomPlane[2].getStart().z > character->shadow.LB.z) // 그림자 밑변이 오브젝트 밑변보다 위에 있을 경우
						{
							character->pos.x = obj->bottomPlane[1].getX(character->shadow.LB.z) + character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
							checkLeft = true;
						}
						else // 그림자 밑변이 오브젝트 밑변보다 아래에 있을 경우
						{
							if (character->preShadow.LT.z < obj->bottomPlane[2].getStart().z)
							{
								character->pos.x = obj->bottomPlane[1].getEnd().x + character->shadow.width / 2;
								checkLeft = true;
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
					if (character->preShadow.RB.z > obj->bottomPlane[0].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &tempV)) // 우측 선분이 오브젝트의 윗변과 겹치면(1차보정)
						{
							character->pos.x = obj->bottomPlane[0].getStart().x - character->shadow.width / 2;
							checkRight = true;
						}
					}
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||	// 우측 선분이 좌측변이랑 교차하면
						Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &interVector))		// 우측 선분이 밑변이랑 교차하면
					{
						if (character->shadow.RB.z < obj->bottomPlane[2].getEnd().z) // 그림자 밑변이 오브젝트 밑변보다 위에 있을 경우
						{
							character->pos.x = obj->bottomPlane[3].getX(character->shadow.RB.z) - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
							checkRight = true;
						}
						else // 그림자 밑변이 오브젝트 밑변보다 아래에 있을 경우
						{
							if (character->preShadow.RT.z < obj->bottomPlane[2].getEnd().z)
							{
								character->pos.x = obj->bottomPlane[3].getStart().x - character->shadow.width / 2;
								checkRight = true;
							}
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
							checkRight = true;
						}
					}
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // 우측 선분이 좌측변이랑 교차하면
						Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &interVector))		// 우측 선분이 윗변이랑 교차하면
					{
						if (character->shadow.RT.z > obj->bottomPlane[0].getStart().z) // 그림자 윗변이 오브젝트 윗변보다 밑에 있을 경우
						{
							character->pos.x = obj->bottomPlane[3].getX(character->shadow.RT.z) - character->shadow.width / 2; // 교차 점에서 왼쪽으로 보정
							checkRight = true;
						}
						else // 그림자 윗변이 오브젝트 윗변보다 위에 있을 경우
						{
							if (character->preShadow.RT.z > obj->bottomPlane[0].getStart().z)
							{
								character->pos.x = obj->bottomPlane[3].getEnd().x - character->shadow.width / 2;
								checkRight = true;
							}
						}
					}
				}
			}
		}
	}
	if (checkUp || checkDown || checkLeft || checkRight)
	{
		character->obstacle = obj;
	}
}

void CollisionManager::playerWallCollsion()
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

	// 수영장과 충돌
	if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		vector3 temp;
		tagWall pool = _stageM->getStage()->getPool();
		if (pool.LT.x < character->shadow.RB.x &&
			character->shadow.LB.x < pool.RT.x)  // 플레이어 아래쪽 최대치 (수영장 충돌)
		{
			if (character->shadow.LB.z > pool.RT.z)
			{
				character->pos.z = pool.RT.z - character->shadow.height / 2;
			}
		}
		if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(Linear(pool.RT, pool.RB), &temp))  // 수영장의 오른쪽과 충돌 시
		{
			character->pos.x = Linear(pool.RT, pool.RB).getX(character->shadow.LB.z) + character->shadow.width / 2;
		}
	}

	if (_stageM->getStage()->getLockEventStart() == true && _stageM->getStage()->getLockEventEnd() == false) // 지역락 걸렸을 때
	{
		if (character->shadow.LT.x < CAMERA_M->GetX() - WINSIZEX / 2)
		{
			character->pos.x = CAMERA_M->GetX() - WINSIZEX / 2 + character->shadow.width / 2;
		}
		else if (character->shadow.RB.x > CAMERA_M->GetX() + WINSIZEX / 2)
		{
			character->pos.x = CAMERA_M->GetX() + WINSIZEX / 2 - character->shadow.width / 2;
		}
	}
	
		
	
}

void CollisionManager::enemyWallColiision(GameObject* character)
{
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
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vLeftWall[i].RB, vLeftWall[i].LB), &interVector)) // 그림자 윗변이 왼쪽 벽이랑 교차하면
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

	// ������� �浹
	if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		vector3 temp;
		tagWall pool = _stageM->getStage()->getPool();
		if (pool.LT.x < character->shadow.RB.x &&
			character->shadow.LB.x < pool.RT.x)  // 플레이어 아래쪽 최대치 (수영장 충돌)
		{
			if (character->shadow.LB.z > pool.RT.z)
			{
				character->pos.z = pool.RT.z - character->shadow.height / 2;
			}
		}
		if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(Linear(pool.RT, pool.RB), &temp))   // 수영장의 오른쪽과 충돌 시
		{
			character->pos.x = Linear(pool.RT, pool.RB).getX(character->shadow.LB.z) + character->shadow.width / 2;
		}
	}
}


void CollisionManager::playerObjectCollision()
{
	playerWallCollsion();
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
				if (obj->dir == DIRECTION::LEFT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// 캐릭터의 z값이 윗변보다 밑에 있고
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// 캐릭터의 z값이 밑변보다 위에 있고
					{
						float tempMaxUz = obj->bottomPlane[1].getX(character->shadow.LT.z);				// 오브젝트 위의 최대값
						if (obj->bottomPlane[1].getStart().x < tempMaxUz) tempMaxUz = obj->bottomPlane[1].getStart().x;
						float tempMaxDz = obj->bottomPlane[3].getX(character->shadow.RB.z);
						if (tempMaxDz < obj->bottomPlane[3].getStart().x) tempMaxDz = obj->bottomPlane[3].getStart().x;

						if (tempMaxDz < character->shadow.RB.x &&
							character->shadow.LT.x < tempMaxUz)											// 맥스값들보다 사이에 있으면
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
									_stageM->getPlayer()->getInfo().isStand = true;
									_stageM->getPlayer()->setState(PL_STATE::IDLE);

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
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// 캐릭터의 z값이 윗변보다 밑에 있고
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// 캐릭터의 z값이 밑변보다 위에 있고
					{
						float tempMaxUz = obj->bottomPlane[3].getX(character->shadow.RT.z);				// 오브젝트 위의 최대값
						if (tempMaxUz < obj->bottomPlane[3].getEnd().x) tempMaxUz = obj->bottomPlane[3].getEnd().x;
						float tempMaxDz = obj->bottomPlane[1].getX(character->shadow.LB.z);
						if (obj->bottomPlane[1].getEnd().x < tempMaxDz) tempMaxDz = obj->bottomPlane[1].getEnd().x;

						if (character->shadow.LB.x < tempMaxDz &&
							tempMaxUz < character->shadow.RT.x)
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
									_stageM->getPlayer()->getInfo().isStand = true;

									_stageM->getPlayer()->setState(PL_STATE::IDLE);
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
							_stageM->getPlayer()->setJumpPower(0);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::enemyObjectCollision(Enemy* enemy)
{

	GameObject* character = enemy->getObj();
	enemyWallColiision(character);
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();

	if (character->pos.y > 0) character->pos.y = 0;
	for (int i = 0; i < vObj.size(); ++i)
	{
		GameObject* obj = vObj[i]->getObj();
		if (obj->group == OBJECT_GROUP::OBJECT)
		{
			if (enemy->getInfo().isSky) // 공중에 있을 때
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// 캐릭터의 z값이 윗변보다 밑에 있고
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// 캐릭터의 z값이 밑변보다 위에 있고
					{
						float tempMaxUz = obj->bottomPlane[1].getX(character->shadow.LT.z);				// 오브젝트 위의 최대값
						if (obj->bottomPlane[1].getStart().x < tempMaxUz) tempMaxUz = obj->bottomPlane[1].getStart().x;
						float tempMaxDz = obj->bottomPlane[3].getX(character->shadow.RB.z);
						if (tempMaxDz < obj->bottomPlane[3].getStart().x) tempMaxDz = obj->bottomPlane[3].getStart().x;

						if (tempMaxDz < character->shadow.RB.x &&
							character->shadow.LT.x < tempMaxUz)											// 맥스값들보다 사이에 있으면
						{
							if (character->prePos.y < character->pos.y) // 낙하 중일 때
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // 해당 범위에 들어가면
								{
									if (enemy->getEnemyType() == ENEMY_TYPE::CHEERLEADER ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLBOY ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLGIRL)
									{
										// y값 보정
										character->pos.y = obj->topPlane[0].getStart().y;
										// 상태보정
										enemy->setPlatform(obj);
										enemy->SetState(EN_STATE::EN_IDLE);
										enemy->getInfo().jumpPower = 0;
										enemy->getInfo().isSky = false;
									}
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
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// 캐릭터의 z값이 윗변보다 밑에 있고
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// 캐릭터의 z값이 밑변보다 위에 있고
					{
						float tempMaxUz = obj->bottomPlane[3].getX(character->shadow.RT.z);				// 오브젝트 위의 최대값
						if (tempMaxUz < obj->bottomPlane[3].getEnd().x) tempMaxUz = obj->bottomPlane[3].getEnd().x;
						float tempMaxDz = obj->bottomPlane[1].getX(character->shadow.LB.z);
						if (obj->bottomPlane[1].getEnd().x < tempMaxDz) tempMaxDz = obj->bottomPlane[1].getEnd().x;

						if (character->shadow.LB.x < tempMaxDz &&
							tempMaxUz < character->shadow.RT.x)
						{
							if (character->prePos.y < character->pos.y) // 낙하 중일 때
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // 해당 범위에 들어가면
								{
									if (enemy->getEnemyType() == ENEMY_TYPE::CHEERLEADER ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLBOY ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLGIRL)
									{
										// y값 보정
										character->pos.y = obj->topPlane[0].getStart().y;
										// 상태보정
										enemy->setPlatform(obj);
										enemy->SetState(EN_STATE::EN_IDLE);
										enemy->getInfo().jumpPower = 0;
										enemy->getInfo().isSky = false;
									}
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
			}
			else // 공중이 아닐 때(isSky == false)
			{
				if (character->pos.y == 0) // 지면일 때
				{
					LRUDCollision(character, obj);
				}
				else // 지면이 아닐 때(오브젝트 위일 때)
				{
					if (enemy->getPlatform() != nullptr)
					{
						if (enemy->getPlatform()->bottomPlane[0].getStart().z > character->shadow.LB.z ||					// 벗어나면
							character->shadow.LT.z > enemy->getPlatform()->bottomPlane[2].getStart().z ||					// 벗어나면
							enemy->getPlatform()->bottomPlane[3].getX(character->shadow.RB.z) > character->shadow.RB.x ||	// 벗어나면
							character->shadow.LT.x > enemy->getPlatform()->bottomPlane[1].getX(character->shadow.LT.z) ||	// 벗어나면
							character->shadow.LT.x > enemy->getPlatform()->bottomPlane[0].getEnd().x ||						// 벗어나면
							character->shadow.RB.x < enemy->getPlatform()->bottomPlane[2].getEnd().x)						// 벗어나면
						{
							enemy->SetState(EN_STATE::EN_JUMP);
							enemy->getInfo().isSky = true;
							enemy->getInfo().jumpPower = 0;
						}
					}
				}
			}
		}
	}
}

void CollisionManager::destructObject()
{

	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (vObj.empty() == false)
	{
		for (int i = 0; i < vObj.size(); ++i)
		{
			if (vObj[i]->getObj()->type == OBJECT_TYPE::VENDINGMACHINE)
			{
				if (vObj[i]->getObj()->des == OBJECT_DESTRUCTION::BEFOREDESTRUCTION)
				{
					RECT temp;
					if (IntersectRect(&temp, &_player->getInfo().attackRc, &vObj[i]->getObj()->rc))
					{
						vObj[i]->getObj()->destructionCount -= 1;
					}

					if (vObj[i]->getObj()->destructionCount <= 0)
					{
						vObj[i]->getObj()->des = OBJECT_DESTRUCTION::DESTRUCTION;
					}
				}
			}
		}
	}
}

void CollisionManager::bossDestructObject(Enemy* enemy)
{
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (vObj.empty() == false)
	{
		for (int i = 0; i < vObj.size(); ++i)
		{
			if (vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_BIG_LEFT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_BIG_RIGHT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_LEFT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_RIGHT)
			{
				if (vObj[i]->getObj()->des == OBJECT_DESTRUCTION::BEFOREDESTRUCTION)
				{
					vector3 temp = vector3((enemy->getInfo().rcAttack.right + enemy->getInfo().rcAttack.left) / 2, 0, (enemy->getInfo().rcAttack.bottom + enemy->getInfo().rcAttack.top) / 2);
					if (enemy->getInfo().dest == DIRECTION::LEFT)
					{
						if (vObj[i]->getObj()->bottomPlane[2].getStart().x < temp.x &&
							temp.x < vObj[i]->getObj()->bottomPlane[0].getEnd().x &&
							vObj[i]->getObj()->bottomPlane[0].getStart().z < enemy->getObj()->shadow.LB.z &&
							enemy->getObj()->shadow.LT.z < vObj[i]->getObj()->bottomPlane[2].getStart().z)
						{
							_stageM->getStage()->getObjectM()->particleSwitch(vObj[i]->getObj()->type);
							_stageM->getStage()->getObjectM()->popObject(i);
							break;
						}
					}
					else if (enemy->getInfo().dest == DIRECTION::RIGHT)
					{
						if (vObj[i]->getObj()->bottomPlane[0].getStart().x < temp.x &&
							temp.x < vObj[i]->getObj()->bottomPlane[2].getEnd().x &&
							vObj[i]->getObj()->bottomPlane[0].getStart().z < enemy->getObj()->shadow.RB.z &&
							enemy->getObj()->shadow.RT.z < vObj[i]->getObj()->bottomPlane[2].getStart().z)
						{
							_stageM->getStage()->getObjectM()->particleSwitch(vObj[i]->getObj()->type);
							_stageM->getStage()->getObjectM()->popObject(i);
							break;
						}
					}
				}
			}
		}
	}
}

