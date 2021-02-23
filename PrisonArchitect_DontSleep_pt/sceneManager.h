#pragma once
#include "singletonBase.h"
class Scene;

class SceneManager : public singletonBase<SceneManager>
{
public:
	typedef vector<Scene*>	vScene;

private:
	vScene _vScene;		//스택에 담긴 씬

public:
	SceneManager();
	~SceneManager() {};

	void ReplaceScene(Scene* scene);
	void PushScene(Scene* scene);
	void PopScene(Scene* scene);

	void Init();
	void Release();
	void Update();
	void Render();

	Scene* GetCurrentScene() { return _vScene[_vScene.size() - 1]; };
	vScene GetsScene() { return _vScene; }

};

