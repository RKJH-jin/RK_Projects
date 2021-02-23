#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "TransformC.h"

GameObject::GameObject()
{
	_isActive = true;
	_isRender = true;

	_transform = AddComponent<TransformC>();
}

GameObject * GameObject::CreateObject(GameObject * parent)
{
	GameObject* object = new GameObject();
	object->_transform = object->AddComponent<TransformC>();

	if (parent == NULL) {}
	else object->SetParent(parent);

	return object;
}

void GameObject::SetParent(GameObject * parent)
{
	_parent = parent;
	_parent->_vChild.push_back(this);
}

void GameObject::AddChild(GameObject * child)
{
	_vChild.push_back(child);
	child->_parent->RemoveChild(child);
	child->_parent = this;
}

void GameObject::RemoveChild(GameObject * child)
{
	for (int i = 0; i < _vChild.size(); i++)
	{
		if (_vChild[i] != child) continue;
		_vChild.erase(_vChild.begin() + i);
		break;
	}
}

void GameObject::RemoveComponent(Component * component)
{
	for (auto itr = _vComponent.begin(); itr != _vComponent.end(); itr++)
	{
		if (*itr == component)
		{
			_vComponent.erase(itr);
			component->Release();
			return;
		}
	}
}

void GameObject::SetActive(bool active)
{
	_isActive = active;

	for (GameObject* c : _vChild)
		c->SetActive(active);
}

void GameObject::SetRender(bool render)
{
	_isRender = render;

	for (GameObject* c : _vChild)
		c->SetRender(render);
}

void GameObject::Init()
{
	for (GameObject* c : _vChild)
		c->Init();

	for (Component* c : _vComponent)
		c->Init();
}

void GameObject::Release()
{
	if (_parent) _parent->RemoveChild(this);

	for (GameObject* c : _vChild)
		c->Release();

	for (int i = _vComponent.size() - 1; i >= 0; i--)
		_vComponent[i]->Release();
	delete this;
}

void GameObject::Update()
{
	if (!_isActive) return;

	for (GameObject* c : _vChild)
		c->Update();

	for (Component* c : _vComponent)
		c->Update();
}

void GameObject::Render()
{
	if (!_isActive || !_isRender) return;

	for (Component* c : _vComponent)
		c->Render();

	for (GameObject* c : _vChild)
		c->Render();
}
