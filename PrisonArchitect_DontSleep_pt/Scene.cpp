#include "stdafx.h"
#include "Scene.h"

HRESULT Scene::init()
{

	return S_OK;
}

void Scene::release()
{
	_mouse->Release();
}

void Scene::update()
{
	_mouse->Update();
	//if (KEYMANAGER->isStayKeyDown('Z')) { DATAMANAGER->GetInfo().soundVolume -= 1; }
	//if (KEYMANAGER->isStayKeyDown('X')) { DATAMANAGER->GetInfo().soundVolume += 1; }

}

void Scene::render()
{
	_mouse->Render();
}
