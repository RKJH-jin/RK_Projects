#include "stdafx.h"
#include "sceneManager.h"
#include "Scene.h"
#include "TitleScene.h"

SceneManager::SceneManager()
{
}

void SceneManager::ReplaceScene(Scene * scene)
{
	for (Scene* s : _vScene) s->release();
	_vScene.clear();

	_vScene.push_back(scene);
	scene->init();
}

void SceneManager::PushScene(Scene * scene)
{
	_vScene.push_back(scene);
	scene->init();
}

void SceneManager::PopScene(Scene * scene)
{
	_vScene[_vScene.size() - 1]->release();
	_vScene.pop_back();
}

void SceneManager::Init()
{
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	GetCurrentScene()->update();
}

void SceneManager::Render()
{
	GetCurrentScene()->render();
}
