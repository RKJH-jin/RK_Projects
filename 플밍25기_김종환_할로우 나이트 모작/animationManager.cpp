#include "stdafx.h"
#include "animationManager.h"

animationManager::animationManager()
{
}

animationManager::~animationManager()
{
}

HRESULT animationManager::init()
{
    return S_OK;
}

void animationManager::release()
{
	deleteAll();
}

void animationManager::update()
{
}

void animationManager::render()
{
}

BOOL animationManager::deleteAnimation(string strKey)
{
	mapIterAnimation key = _mAnimation.find(strKey);

	if (key != _mAnimation.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mAnimation.erase(key);

		return true;
	}

	return false;
}

BOOL animationManager::deleteAll()
{
	mapIterAnimation iter = _mAnimation.begin();

	for (; iter != _mAnimation.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mAnimation.erase(iter);
		}
		else ++iter;
	}

	_mAnimation.clear();

	return 0;
}

animation* animationManager::findAnimation(string strKey)
{
	mapIterAnimation key = _mAnimation.find(strKey);

	//찾았다
	if (key != _mAnimation.end())
	{
		return key->second;
	}

	return nullptr;
}

void animationManager::resetExceptCurrentAni(string strKey)
{
	mapIterAnimation key = _mAnimation.find(strKey);

	for (_miAnimation = _mAnimation.begin(); _miAnimation != _mAnimation.end(); ++_miAnimation)
	{
		if (_miAnimation != key)
		{
			_miAnimation->second->stop();
		}
	}
}

void animationManager::resetCurrentAni(string strKey)
{
	mapIterAnimation key = _mAnimation.find(strKey);

	for (_miAnimation = _mAnimation.begin(); _miAnimation != _mAnimation.end(); ++_miAnimation)
	{
		if (_miAnimation == key)
		{
			_miAnimation->second->stop();
			break;
		}
	}
}

animation* animationManager::addAnimation(string imgStrKey, string aniStrKey, BOOL reverse, BOOL loop, int fps)
{
	image* img = IMAGEMANAGER->findImage(imgStrKey);
	animation* ani = findAnimation(aniStrKey);

	if (ani) return ani;

	//없으면 새로 하나 할당해줘라
	ani = new animation;

	if (FAILED(ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight())))
	{
		SAFE_DELETE(ani);

		return nullptr;
	}
	else
	{
		ani->setDefaultPlayFrame(reverse, loop);
		ani->setFPS(fps);
		ani->stop();
	}

	_mAnimation.insert(make_pair(aniStrKey, ani));

	return ani;
}

animation* animationManager::addAnimation(string imgStrKey, string aniStrKey, int idxStart, int idxEnd, BOOL reverse, BOOL loop, int fps)
{
	image* img = IMAGEMANAGER->findImage(imgStrKey);
	animation* ani = findAnimation(aniStrKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (ani) return ani;

	//없으면 새로 하나 할당해줘라
	ani = new animation;

	if (FAILED(ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight())))
	{
		SAFE_DELETE(ani);

		return nullptr;
	}
	else
	{
		ani->setPlayFrame(idxStart, idxEnd, reverse, loop);
		ani->setFPS(fps);
		ani->stop();
	}

	_mAnimation.insert(make_pair(aniStrKey, ani));

	return ani;
}

animation* animationManager::addAnimation(string strKey, int totalW, int totalH, int frameW, int frameH, BOOL reverse, BOOL loop, int fps)
{
	animation* ani = findAnimation(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (ani) return ani;

	//없으면 새로 하나 할당해줘라
	ani = new animation;

	if (FAILED(ani->init(totalW, totalH, frameW, frameH)))
	{
		SAFE_DELETE(ani);

		return nullptr;
	}
	else
	{
		ani->setDefaultPlayFrame(reverse, loop);
		ani->setFPS(fps);
		ani->stop();
	}

	_mAnimation.insert(make_pair(strKey, ani));

	return ani;
}


void animationManager::updateAnimation(string strKey, int num)
{
	animation* ani = findAnimation(strKey);
	ani->frameUpdate(TIMEMANAGER->getElapsedTime() * num);
}

void animationManager::aniRender(string imgStrKey, string aniStrKey, HDC hdc, float x, float y)
{
	animation* ani = findAnimation(aniStrKey);
	image* img = IMAGEMANAGER->findImage(imgStrKey);

	img->aniRender(hdc, x, y, ani);
}

