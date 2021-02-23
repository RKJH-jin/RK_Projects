#include "stdafx.h"
#include "GameObject.h"

//초기화 (그룹, 이미지, 위치)
void GameObject::init(OBJECT_GROUP _group, image* _img, vector3 _pos)
{
	img = _img;
	group = _group;

	pos = _pos;
	zAngle = -PI / 4;
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();

	alpha = 255;
	isRender = true;

	RectRenew();

	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = false;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		isShadow = false;
		break;
	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

	isActive = true;
	isRender = true;
	/*====================================================================
						그림자 등 충돌 처리에 관련 해 설정합니다.
	====================================================================*/
	if (isShadow)
	{
		shadow.pos = vector3(pos.x, pos.y, pos.z);
		shadow.width = 120;
		shadow.height = 20;
		shadow.LT = vector3(pos.x - shadow.width / 2, pos.y, pos.z - shadow.height / 2);
		shadow.RT = vector3(pos.x + shadow.width / 2, pos.y, pos.z - shadow.height / 2);
		shadow.RB = vector3(pos.x + shadow.width / 2, pos.y, pos.z + shadow.height / 2);
		shadow.LB = vector3(pos.x - shadow.width / 2, pos.y, pos.z + shadow.height / 2);
		shadow.rc = RectMakeCenter(pos.x, pos.z, shadow.width, shadow.height);
	}

}

void GameObject::init(OBJECT_GROUP _group, OBJECT_TYPE _type, image* _img, vector3 _pos, float a)
{
	img = _img;
	group = _group;

	pos = _pos;
	margin = a;
	zAngle = -PI / 4;
	if (_img != nullptr)
	{
		size.x = img->getFrameWidth();
		size.z = img->getFrameHeight();
	}

	type = _type;
	alpha = 255;

	RectRenew();
	isRender = true;
	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = false;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		switch (_type)
		{
		case OBJECT_TYPE::DESK:
			topPlane[0] = Linear(vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z));						
			topPlane[1] = Linear(vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z + margin));	
			topPlane[2] = Linear(vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z + margin));			
			topPlane[3] = Linear(vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z));			

			bottomPlane[0] = Linear(vector3(pos.x - size.x / 2 + margin, (float)0, pos.z - margin), vector3(pos.x + size.x / 2, (float)0, pos.z - margin));								
			bottomPlane[1] = Linear(vector3(pos.x + size.x / 2, (float)0, pos.z - margin), vector3(pos.x + size.x / 2 - margin, (float)0, pos.z));								
			bottomPlane[2] = Linear(vector3(pos.x + size.x / 2 - margin, (float)0, pos.z), vector3(pos.x - size.x / 2, (float)0, pos.z));										
			bottomPlane[3] = Linear(vector3(pos.x - size.x / 2, (float)0, pos.z), vector3(pos.x - size.x / 2 + margin, (float)0, pos.z - margin));					

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			dir = DIRECTION::LEFT;
			des = OBJECT_DESTRUCTION::INDESTRUCTIBLE;
			break;
		case OBJECT_TYPE::TABLE:
			topPlane[0] = Linear(vector3(pos.x - size.x / 2 + 51, -size.z / 2, pos.z - 50 - size.z / 2), vector3(pos.x + size.x / 2 - 30, -size.z / 2, pos.z - 50 - size.z / 2));	
			topPlane[1] = Linear(vector3(pos.x + size.x / 2 - 30, -size.z / 2, pos.z - 50 - size.z / 2), vector3(pos.x + size.x / 2 - 51, -size.z / 2, pos.z - size.z / 2));			
			topPlane[2] = Linear(vector3(pos.x + size.x / 2 - 51, -size.z / 2, pos.z - size.z / 2), vector3(pos.x - size.x / 2 + 30, -size.z / 2, pos.z - size.z / 2));		
			topPlane[3] = Linear(vector3(pos.x - size.x / 2 + 30, -size.z / 2, pos.z - size.z / 2), vector3(pos.x - size.x / 2 + 51, -size.z / 2, pos.z - 50 - size.z / 2));

			bottomPlane[0] = Linear(vector3(pos.x - size.x / 2 + 51, (float)0, pos.z - 50), vector3(pos.x + size.x / 2 - 30, (float)0, pos.z - 50));					
			bottomPlane[1] = Linear(vector3(pos.x + size.x / 2 - 30, (float)0, pos.z - 50), vector3(pos.x + size.x / 2 - 51, (float)0, pos.z));							
			bottomPlane[2] = Linear(vector3(pos.x + size.x / 2 - 51, (float)0, pos.z), vector3(pos.x - size.x / 2 + 30, (float)0, pos.z));							
			bottomPlane[3] = Linear(vector3(pos.x - size.x / 2 + 30, (float)0, pos.z), vector3(pos.x - size.x / 2 + 51, (float)0, pos.z - 50));					

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			dir = DIRECTION::LEFT;
			des = OBJECT_DESTRUCTION::INDESTRUCTIBLE;
			break;
		case OBJECT_TYPE::LADDER:
			topPlane[0] = Linear(vector3(pos.x - 60, -440 + margin, pos.z - 440), vector3(pos.x + 60 - margin, -440 + margin, pos.z - 440));				
			topPlane[1] = Linear(vector3(pos.x + 60 - margin, -440 + margin, pos.z - 440), vector3(pos.x + 60, -440 + margin, pos.z - 440 + margin));				
			topPlane[2] = Linear(vector3(pos.x + 60, -440 + margin, pos.z - 440 + margin), vector3(pos.x - 60 + margin, -440 + margin, pos.z - 440 + margin));		
			topPlane[3] = Linear(vector3(pos.x - 60 + margin, -440 + margin, pos.z - 440 + margin), vector3(pos.x - 60, -440 + margin, pos.z - 440));						

			bottomPlane[0] = Linear(vector3(pos.x - 60, (float)0, pos.z - margin), vector3(pos.x + 60 - margin, (float)0, pos.z - margin));			
			bottomPlane[1] = Linear(vector3(pos.x + 60 - margin, (float)0, pos.z - margin), vector3(pos.x + 60, (float)0, pos.z));					
			bottomPlane[2] = Linear(vector3(pos.x + 60, (float)0, pos.z), vector3(pos.x - 60 + margin, (float)0, pos.z));							
			bottomPlane[3] = Linear(vector3(pos.x - 60 + margin, (float)0, pos.z), vector3(pos.x - 60, (float)0, pos.z - margin));					

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			type = OBJECT_TYPE::LADDER;
			dir = DIRECTION::RIGHT;
			des = OBJECT_DESTRUCTION::INDESTRUCTIBLE;
			break;
		case OBJECT_TYPE::HARDPLATFORM:
			topPlane[0] = Linear(vector3(pos.x - 853, (float)-420, pos.z - 150), vector3(pos.x + 853 - 55, (float)-420, pos.z - 150));	
			topPlane[1] = Linear(vector3(pos.x + 853 - 55, (float)-420, pos.z - 150), vector3(pos.x + 853, (float)-420, pos.z - 95));	
			topPlane[2] = Linear(vector3(pos.x + 853, (float)-420, pos.z - 95), vector3(pos.x - 853 + 55, (float)-420, pos.z - 95));	
			topPlane[3] = Linear(vector3(pos.x - 853 + 55, (float)-420, pos.z - 95), vector3(pos.x - 853, (float)-420, pos.z - 150));	

			bottomPlane[0] = Linear(vector3(pos.x - 853, (float)-335, pos.z - 55), vector3(pos.x + 853 - 55, (float)-335, pos.z - 55));	
			bottomPlane[1] = Linear(vector3(pos.x + 853 - 55, (float)-335, pos.z - 55), vector3(pos.x + 853, (float)-335, pos.z));		
			bottomPlane[2] = Linear(vector3(pos.x + 853, (float)-335, pos.z), vector3(pos.x - 853 + 55, (float)-335, pos.z));			
			bottomPlane[3] = Linear(vector3(pos.x - 853 + 55, (float)-335, pos.z), vector3(pos.x - 853, (float)-335, pos.z - 55));		

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			type = OBJECT_TYPE::HARDPLATFORM;
			dir = DIRECTION::RIGHT;
			des = OBJECT_DESTRUCTION::INDESTRUCTIBLE;
			break;
		case OBJECT_TYPE::VENDINGMACHINE:
			topPlane[0] = Linear(vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z));			
			topPlane[1] = Linear(vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z + margin));			
			topPlane[2] = Linear(vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z + margin));	
			topPlane[3] = Linear(vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z));						

			bottomPlane[0] = Linear(vector3(pos.x - size.x / 2, (float)0, pos.z - margin), vector3(pos.x + size.x / 2 - margin, (float)0, pos.z - margin));	
			bottomPlane[1] = Linear(vector3(pos.x + size.x / 2 - margin, (float)0, pos.z - margin), vector3(pos.x + size.x / 2, (float)0, pos.z));			
			bottomPlane[2] = Linear(vector3(pos.x + size.x / 2, (float)0, pos.z), vector3(pos.x - size.x / 2 + margin, (float)0, pos.z));				
			bottomPlane[3] = Linear(vector3(pos.x - size.x / 2 + margin, (float)0, pos.z), vector3(pos.x - size.x / 2, (float)0, pos.z - margin));			

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			dir = DIRECTION::RIGHT;
			imgIndex = PointMake(1, 0);
			des = OBJECT_DESTRUCTION::BEFOREDESTRUCTION;
			destructionCount = 5;
			break;
		case OBJECT_TYPE::PILLAR_LEFT: case OBJECT_TYPE::PILLAR_BIG_LEFT:
			topPlane[0] = Linear(vector3(pos.x - (size.x / 2 - 20) + margin, -size.z + margin, pos.z - size.z + 5), vector3(pos.x + (size.x / 2) - 5, -size.z + margin, pos.z - size.z + 5));		
			topPlane[1] = Linear(vector3(pos.x + (size.x / 2) - 5, -size.z + margin, pos.z - size.z + 5), vector3(pos.x + (size.x / 2) - margin, -size.z + margin, pos.z - size.z + margin));		
			topPlane[2] = Linear(vector3(pos.x + (size.x / 2) - margin, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - (size.x / 2 - 20), -size.z + margin, pos.z - size.z + margin));	
			topPlane[3] = Linear(vector3(pos.x - (size.x / 2 - 20), -size.z + margin, pos.z - size.z + margin), vector3(pos.x - (size.x / 2 - 20) + margin, -size.z + margin, pos.z - size.z + 5));	

			bottomPlane[0] = Linear(vector3(pos.x - (size.x / 2 - 20) + margin, (float)0, pos.z - margin + 5), vector3(pos.x + (size.x / 2) - 5, (float)0, pos.z - margin + 5));			
			bottomPlane[1] = Linear(vector3(pos.x + (size.x / 2) - 5, (float)0, pos.z - margin + 5), vector3(pos.x + (size.x / 2) - margin, (float)0, pos.z));			
			bottomPlane[2] = Linear(vector3(pos.x + (size.x / 2) - margin, (float)0, pos.z), vector3(pos.x - (size.x / 2 - 20), (float)0, pos.z));						
			bottomPlane[3] = Linear(vector3(pos.x - (size.x / 2 - 20), (float)0, pos.z), vector3(pos.x - (size.x / 2 - 20) + margin, (float)0, pos.z - margin + 5));	

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			dir = DIRECTION::LEFT;
			imgIndex = PointMake(1, 0);
			des = OBJECT_DESTRUCTION::BEFOREDESTRUCTION;
			destructionCount = 5;
			break;
		case OBJECT_TYPE::PILLAR_RIGHT: case OBJECT_TYPE::PILLAR_BIG_RIGHT:
			topPlane[0] = Linear(vector3(pos.x - size.x / 2 + 5, -size.z + margin, pos.z - size.z + 5), vector3(pos.x + (size.x / 2 - 20) - margin, -size.z + margin, pos.z - size.z + 5));			
			topPlane[1] = Linear(vector3(pos.x + (size.x / 2 - 20) - margin, -size.z + margin, pos.z - size.z + 5), vector3(pos.x + (size.x / 2 - 20), -size.z + margin, pos.z - size.z + margin));	
			topPlane[2] = Linear(vector3(pos.x + (size.x / 2 - 20), -size.z + margin, pos.z - size.z + margin), vector3(pos.x - (size.x / 2) + margin, -size.z + margin, pos.z - size.z + margin));	
			topPlane[3] = Linear(vector3(pos.x - (size.x / 2) + margin, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2 + 5, -size.z + margin, pos.z - size.z + 5));			

			bottomPlane[0] = Linear(vector3(pos.x - size.x / 2 + 5, (float)0, pos.z - margin + 5), vector3(pos.x + (size.x / 2 - 20) - margin, (float)0, pos.z - margin + 5));	
			bottomPlane[1] = Linear(vector3(pos.x + (size.x / 2 - 20) - margin, (float)0, pos.z - margin + 5), vector3(pos.x + (size.x / 2 - 20), (float)0, pos.z));						
			bottomPlane[2] = Linear(vector3(pos.x + (size.x / 2 - 20), (float)0, pos.z), vector3(pos.x - (size.x / 2) + margin, (float)0, pos.z));					
			bottomPlane[3] = Linear(vector3(pos.x - (size.x / 2) + margin, (float)0, pos.z), vector3(pos.x - size.x / 2 + 5, (float)0, pos.z - margin + 5));		

			// 그리기 전용 선분들, 충돌 처리에서는 안 쓸 거임
			sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
			sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
			sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
			sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());
			dir = DIRECTION::RIGHT;
			imgIndex = PointMake(0, 0);
			des = OBJECT_DESTRUCTION::BEFOREDESTRUCTION;
			destructionCount = 5;
			break;
		case OBJECT_TYPE::PILLAR_PARTICLE_1: case OBJECT_TYPE::PILLAR_PARTICLE_2: case OBJECT_TYPE::PILLAR_PARTICLE_3:
			isRender = false;
			break;
		default:
			break;
		}
	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

	/*====================================================================
						그림자 오브젝트입니다.
	====================================================================*/
	if (isShadow)
	{
		shadow.pos = vector3(pos.x, pos.y, pos.z);
		shadow.width = 120;
		shadow.height = 20;
		shadow.LT = vector3(pos.x - shadow.width / 2, pos.y, pos.z - shadow.height / 2);
		shadow.RT = vector3(pos.x + shadow.width / 2, pos.y, pos.z - shadow.height / 2);
		shadow.RB = vector3(pos.x + shadow.width / 2, pos.y, pos.z + shadow.height / 2);
		shadow.LB = vector3(pos.x - shadow.width / 2, pos.y, pos.z + shadow.height / 2);
		shadow.rc = RectMakeCenter(pos.x, pos.z, shadow.width, shadow.height);
	}

	
}


void GameObject::release()
{

}

void GameObject::update()
{
	RectRenew();
	shadowUpdate();
	switch (type)
	{
	case OBJECT_TYPE::VENDINGMACHINE:
		if (des == OBJECT_DESTRUCTION::DESTRUCTION)
		{
			imgIndex = PointMake(0, 0);
		}
		break;
	default:
		break;
	}
}

void GameObject::render()
{

}

void GameObject::RectRenew()
{
	rc = RectMakeCenter(pos.x, pos.z - size.z / 2 + pos.y, size.x, size.z);
}

void GameObject::shadowUpdate()
{
	/*====================================================================
						그림자 업데이트
	====================================================================*/
	shadow.pos = vector3(pos.x, pos.y, pos.z);
	shadow.width = 120;
	shadow.height = 20;
	shadow.LT = vector3(pos.x - shadow.width / 2, pos.y, pos.z - shadow.height / 2);
	shadow.RT = vector3(pos.x + shadow.width / 2, pos.y, pos.z - shadow.height / 2);
	shadow.RB = vector3(pos.x + shadow.width / 2, pos.y, pos.z + shadow.height / 2);
	shadow.LB = vector3(pos.x - shadow.width / 2, pos.y, pos.z + shadow.height / 2);
	shadow.rc = RectMakeCenter(pos.x, pos.z, shadow.width, shadow.height);
}

void GameObject::PolyLineRender(HDC hdc)
{
	if (KEY_M->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 4; ++i)
		{
			topPlane[i].LinearRender(hdc);
			bottomPlane[i].LinearRender(hdc);
			sideHeight[i].LinearRender(hdc);
		}
	}
}
