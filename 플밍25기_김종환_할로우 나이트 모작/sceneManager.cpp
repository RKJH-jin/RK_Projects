#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
    _currentScene = NULL;

    return S_OK;
}

void sceneManager::release()
{
    mapSceneIter miSceneList = _mSceneList.begin();

    for (; miSceneList != _mSceneList.end();)
    {
        if (miSceneList->second != NULL)
        {
            if (miSceneList->second == _currentScene) miSceneList->second->release();
            SAFE_DELETE(miSceneList->second);
            miSceneList = _mSceneList.erase(miSceneList);
        }
        else ++miSceneList;
    }
    _mSceneList.clear();
}

void sceneManager::update()
{
    if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
    if (_currentScene) _currentScene->render();
}

gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
    if (!scene) return nullptr;

    _mSceneList.insert(make_pair(sceneName, scene));

    return scene;
}



//나중에 눈여겨봤다가 자기입맛 또는 팀프로젝트의 구조대로 손봐야하면 손볼것
HRESULT sceneManager::changeScene(string sceneName)
{
    //이터레이터에 찾고자 하는 씬의 키 값을 넣는다
    mapSceneIter find = _mSceneList.find(sceneName);

    //찾고자 하는 씬이 존재하지 않으면 실패를 알린다
    if (find == _mSceneList.end()) return E_FAIL;

    //찾고자 하는 씬이 현재 씬과 같으면 바꿀필요가 없음
    if (find->second == _currentScene) return S_OK;

    //씬을 바꾸는데 성공했으면  init()함수를 바로 실행시킨다
    if (SUCCEEDED(find->second->init()))
    {
        //현재 씬의 릴리즈 함수를 실행시켜 메모리 해제를 하고
        if (_currentScene) _currentScene->release();

        //바꾸려는 씬을 현재씬으로 체인지
        _currentScene = find->second;

        return S_OK;
    }
    return E_FAIL;
}