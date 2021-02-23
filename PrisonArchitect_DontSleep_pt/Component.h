#pragma once
#include"GameObject.h"

class GameObject;

class Component abstract
{
protected:
	GameObject* _object;

public:
	virtual void Awake() {};
	virtual void Init() {};
	virtual void Release() { delete this; };
	virtual void Update() {};
	virtual void Render() {};

	void LinkGameObject(GameObject* obj) { _object = obj; }
	GameObject* GetGameObject() { return _object; }

};

