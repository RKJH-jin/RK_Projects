#include "stdafx.h"
#include "ObjectManager.h"
#include "AllObjects.h"
#include "StageManager.h"

HRESULT ObjectManager::init()
{
	return S_OK;
}

void ObjectManager::release()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->release();
		delete _vObject[i];
		break;
	}
	_vObject.clear();
}

void ObjectManager::update()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (_vObject[i]->getObj()->isRender) _vObject[i]->update();
	}

	particleMove();
}

void ObjectManager::render()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (_vObject[i]->getObj()->isRender) _vObject[i]->render();
		if (_vObject[i]->getObj()->isRender) _vObject[i]->getObj()->PolyLineRender(getMapDC());
	}

	for (int i = 0; i < _vParticleLeftUp.size(); ++i)
	{
		if (_vParticleLeftUp[i]->getObj()->isRender) _vParticleLeftUp[i]->render();
	}
	for (int i = 0; i < _vParticleLeftDown.size(); ++i)
	{
		if (_vParticleLeftDown[i]->getObj()->isRender) _vParticleLeftDown[i]->render();
	}
	for (int i = 0; i < _vParticleRightUp.size(); ++i)
	{
		if (_vParticleRightUp[i]->getObj()->isRender) _vParticleRightUp[i]->render();
	}
	for (int i = 0; i < _vParticleRightDown.size(); ++i)
	{
		if (_vParticleRightDown[i]->getObj()->isRender) _vParticleRightDown[i]->render();
	}
}

Object * ObjectManager::findHardPlatform()
{
	if (_vObject.empty() == false)
	{
		for (int i = 0; i < _vObject.size(); ++i)
		{
			if (_vObject[i]->getObj()->type == OBJECT_TYPE::HARDPLATFORM)
			{
				return _vObject[i];
			}
		}
	}
	else return nullptr;
}

void ObjectManager::particleInit(vector3 pos, OBJECT_TYPE type)
{
	switch (type)
	{
	case OBJECT_TYPE::PILLAR_LEFT:
		for (int i = 0; i < PARTICLEMAX; ++i)
		{
			int tempNum = RND->getInt(3);
			int tempNum1 = RND->getFromIntTo(20, 40);
			int tempNum2 = RND->getFromIntTo(10, 25);
			vector3 tempPos = vector3(pos.x + tempNum1 * (i % 3), pos.y - tempNum2 * (i / 3), pos.z);

			switch (tempNum)
			{
			case 0:
				_vParticleLeftUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_1, tempPos));
				break;
			case 1:
				_vParticleLeftUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_2, tempPos));
				break;
			case 2:
				_vParticleLeftUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_3, tempPos));
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_TYPE::PILLAR_RIGHT:
		for (int i = 0; i < PARTICLEMAX; ++i)
		{
			int tempNum = RND->getInt(3);
			int tempNum1 = RND->getFromIntTo(20, 40);
			int tempNum2 = RND->getFromIntTo(10, 25);
			vector3 tempPos = vector3(pos.x + tempNum1 * (i % 3), pos.y - tempNum2 * (i / 3), pos.z);

			switch (tempNum)
			{
			case 0:
				_vParticleRightUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_1, tempPos));
				break;
			case 1:
				_vParticleRightUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_2, tempPos));
				break;
			case 2:
				_vParticleRightUp.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_3, tempPos));
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_TYPE::PILLAR_BIG_LEFT:
		for (int i = 0; i < PARTICLEMAX; ++i)
		{
			int tempNum = RND->getInt(3);
			int tempNum1 = RND->getFromIntTo(20, 40);
			int tempNum2 = RND->getFromIntTo(10, 25);
			vector3 tempPos = vector3(pos.x + tempNum1 * (i % 3), pos.y - tempNum2 * (i / 3), pos.z);

			switch (tempNum)
			{
			case 0:
				_vParticleLeftDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_1, tempPos));
				break;
			case 1:
				_vParticleLeftDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_2, tempPos));
				break;
			case 2:
				_vParticleLeftDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_3, tempPos));
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		for (int i = 0; i < PARTICLEMAX; ++i)
		{
			int tempNum = RND->getInt(3);
			int tempNum1 = RND->getFromIntTo(20, 40);
			int tempNum2 = RND->getFromIntTo(10, 25);
			vector3 tempPos = vector3(pos.x + tempNum1 * (i % 3), pos.y - tempNum2 * (i / 3), pos.z);

			switch (tempNum)
			{
			case 0:
				_vParticleRightDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_1, tempPos));
				break;
			case 1:
				_vParticleRightDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_2, tempPos));
				break;
			case 2:
				_vParticleRightDown.push_back(new StandingObj(OBJECT_TYPE::PILLAR_PARTICLE_3, tempPos));
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}



}

void ObjectManager::particleSwitch(OBJECT_TYPE type)
{
	switch (type)
	{
	case OBJECT_TYPE::PILLAR_LEFT:
		for (int i = 0; i < _vParticleLeftUp.size(); ++i)
		{
			if (_vParticleLeftUp[i]->getObj()->isRender) _vParticleLeftUp[i]->getObj()->isRender = false;
			else
			{
				_vParticleLeftUp[i]->getObj()->isRender = true;
				_vParticleLeftUp[i]->setTimer(TIME_M->getWorldTime());
			}
		}

		break;
	case OBJECT_TYPE::PILLAR_RIGHT:
		for (int i = 0; i < _vParticleRightUp.size(); ++i)
		{
			if (_vParticleRightUp[i]->getObj()->isRender) _vParticleRightUp[i]->getObj()->isRender = false;
			else
			{
				_vParticleRightUp[i]->getObj()->isRender = true;
				_vParticleRightUp[i]->setTimer(TIME_M->getWorldTime());
			}
		}
		break;
	case OBJECT_TYPE::PILLAR_BIG_LEFT:
		for (int i = 0; i < _vParticleLeftDown.size(); ++i)
		{
			if (_vParticleLeftDown[i]->getObj()->isRender) _vParticleLeftDown[i]->getObj()->isRender = false;
			else
			{
				_vParticleLeftDown[i]->getObj()->isRender = true;
				_vParticleLeftDown[i]->setTimer(TIME_M->getWorldTime());
			}
		}
		break;
	case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		for (int i = 0; i < _vParticleRightDown.size(); ++i)
		{
			if (_vParticleRightDown[i]->getObj()->isRender) _vParticleRightDown[i]->getObj()->isRender = false;
			else
			{
				_vParticleRightDown[i]->getObj()->isRender = true;
				_vParticleRightDown[i]->setTimer(TIME_M->getWorldTime());
			}
		}
		break;
	default:
		break;
	}

}

void ObjectManager::particleMove()
{
	for (int i = 0; i < _vParticleLeftUp.size(); ++i)
	{
		if (_vParticleLeftUp[i]->getObj()->isRender)
		{
			if ((TIME_M->getWorldTime() - _vParticleLeftUp[i]->getTimer()) < 0.5f)
			{
				switch (_vParticleLeftUp[i]->getObj()->type)
				{
				case OBJECT_TYPE::PILLAR_PARTICLE_1:
					_vParticleLeftUp[i]->getObj()->pos.y += 5.0f;
					break;
				case OBJECT_TYPE::PILLAR_PARTICLE_2:
					_vParticleLeftUp[i]->getObj()->pos.y += 6.0f;
					_vParticleLeftUp[i]->getObj()->pos.x += 1.0f;
					break;
				case OBJECT_TYPE::PILLAR_PARTICLE_3:
					_vParticleLeftUp[i]->getObj()->pos.y += 4.0f;
					_vParticleLeftUp[i]->getObj()->pos.x -= 0.5f;
					break;
				default:
					break;
				}
			}
			else _vParticleLeftUp[i]->getObj()->isRender = false;
		}
	}

	for (int i = 0; i < _vParticleLeftDown.size(); ++i)
	{
		if ((TIME_M->getWorldTime() - _vParticleLeftDown[i]->getTimer()) < 0.5f)
		{
			switch (_vParticleLeftDown[i]->getObj()->type)
			{
			case OBJECT_TYPE::PILLAR_PARTICLE_1:
				_vParticleLeftDown[i]->getObj()->pos.y += 5.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_2:
				_vParticleLeftDown[i]->getObj()->pos.y += 6.0f;
				_vParticleLeftDown[i]->getObj()->pos.x += 1.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_3:
				_vParticleLeftDown[i]->getObj()->pos.y += 4.0f;
				_vParticleLeftDown[i]->getObj()->pos.x -= 0.5f;
				break;
			default:
				break;
			}
		}
		else _vParticleLeftDown[i]->getObj()->isRender = false;
	}

	for (int i = 0; i < _vParticleRightUp.size(); ++i)
	{
		if ((TIME_M->getWorldTime() - _vParticleRightUp[i]->getTimer()) < 0.5f)
		{
			switch (_vParticleRightUp[i]->getObj()->type)
			{
			case OBJECT_TYPE::PILLAR_PARTICLE_1:
				_vParticleRightUp[i]->getObj()->pos.y += 5.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_2:
				_vParticleRightUp[i]->getObj()->pos.y += 6.0f;
				_vParticleRightUp[i]->getObj()->pos.x += 1.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_3:
				_vParticleRightUp[i]->getObj()->pos.y += 4.0f;
				_vParticleRightUp[i]->getObj()->pos.x -= 0.5f;
				break;
			default:
				break;
			}
		}
		else _vParticleRightUp[i]->getObj()->isRender = false;
	}

	for (int i = 0; i < _vParticleRightDown.size(); ++i)
	{
		if ((TIME_M->getWorldTime() - _vParticleRightDown[i]->getTimer()) < 0.5f)
		{
			switch (_vParticleRightDown[i]->getObj()->type)
			{
			case OBJECT_TYPE::PILLAR_PARTICLE_1:
				_vParticleRightDown[i]->getObj()->pos.y += 5.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_2:
				_vParticleRightDown[i]->getObj()->pos.y += 6.0f;
				_vParticleRightDown[i]->getObj()->pos.x += 1.0f;
				break;
			case OBJECT_TYPE::PILLAR_PARTICLE_3:
				_vParticleRightDown[i]->getObj()->pos.y += 4.0f;
				_vParticleRightDown[i]->getObj()->pos.x -= 0.5f;
				break;
			default:
				break;
			}
		}
		else _vParticleRightDown[i]->getObj()->isRender = false;
	}
}


void ObjectManager::pushObject(OBJECT_TYPE type, vector3 pos)
{
	switch (type)
	{
	case OBJECT_TYPE::DESK:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::TABLE:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::VENDINGMACHINE:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	case OBJECT_TYPE::LADDER:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::HARDPLATFORM:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::PILLAR_LEFT: case OBJECT_TYPE::PILLAR_BIG_LEFT:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	case OBJECT_TYPE::PILLAR_RIGHT: case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	default:
		break;
	}
}

void ObjectManager::pushItem(ITEM_TYPE type, vector3 pos)
{
	_vObject.push_back(new ItemObj(type, pos));

}

void ObjectManager::pushWeapon(WEAPON_TYPE type, vector3 pos)
{
	_vObject.push_back(new Weapon(type, pos));

}

void ObjectManager::popObject(int index)
{
	for (int i = 0; i < _vObject.size();)
	{
		if (i == index)
		{
			SAFE_DELETE(_vObject[i]);
			_vObject.erase(_vObject.begin() + i);
			break;
		}
		else  i++;
	}
}

