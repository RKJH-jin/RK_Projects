#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	_mainCamera = new camera;
	_mainCamera->init(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY, 1);
    _mCameraList.insert(make_pair(mc, _mainCamera));
    return S_OK;
}

void cameraManager::release()
{
	deleteAll();
}

BOOL cameraManager::deleteCamera(string strKey)
{
	mapCameraIter key = _mCameraList.find(strKey);

	if (key != _mCameraList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mCameraList.erase(key);

		return true;
	}

	return false;
}

BOOL cameraManager::deleteAll()
{
	mapCameraIter iter = _mCameraList.begin();

	for (; iter != _mCameraList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mCameraList.erase(iter);
		}
		else ++iter;
	}

	_mCameraList.clear();

	return 0;
}



void cameraManager::mainCameraUpdate(float x, float y)
{
    camera* camera;
	camera = findCamera(mc);
	if (camera->getWidth() / 2 <= x && x < (maxScreenWidth - camera->getWidth() / 2))
	{
		camera->setX(x);		
	}
	if (camera->getHeight() / 2 <= y && y < (maxScreenHeight - camera->getHeight() / 2))
	{
		camera->setY(y);
	}
	camera->updateVertax();
}



void cameraManager::cameraUpdate(string strKey, float x, float y)
{
	camera* camera;
	camera = findCamera(strKey);
	if (camera->getWidth() / 2 <= x && x < (maxScreenWidth - camera->getWidth() / 2))
	{
		camera->setX(x);
	}
	if (camera->getHeight() / 2 <= y && y < (maxScreenHeight - camera->getHeight() / 2))
	{
		camera->setY(y);
	}
	camera->updateVertax();
}

camera* cameraManager::findCamera(string strKey)			// 카메라 찾기
{
	mapCameraIter key = _mCameraList.find(strKey);

	
	if (key != _mCameraList.end())
	{
		return key->second;
	}

	return nullptr;
}

camera* cameraManager::addCamera(string strKey, float x, float y, int width, int height, int mag)
{
	camera* cmr = findCamera(strKey);

	//해당 카메라가 있으면 그 카메라를 반환해라
	if (cmr) return cmr;

	//없으면 새로 하나 할당해줘라
	cmr = new camera;

	if (FAILED(cmr->init(x, y, width, height, mag)))
	{
		SAFE_DELETE(cmr);

		return nullptr;
	}

	_mCameraList.insert(make_pair(strKey, cmr));

	return cmr;

}

void cameraManager::shakeMainCamera()
{

}

void cameraManager::shakeCamera(string strKey)
{
}