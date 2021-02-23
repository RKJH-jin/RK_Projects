#pragma once
#include <vector>

class Component;
class TransformC;

struct Color
{
	float r; float g; float b; float a;
};

class GameObject
{
protected:
	/* ==================================================
		오브젝트 멤버
	================================================== */
	string _name;				//이름
	string _key;				//키
	string _tag;				//태그
	string _description;		//설명
	vector<string> _vDescription;	//설명벡터
	bool _isActive;				//활성화 여부
	bool _isRender;				//렌더 여부

	/* ==================================================
		컴포넌트
	================================================== */
	vector<Component*> _vComponent;		//컴포넌트 벡터
	TransformC* _transform;				//트랜스폼

	/* ==================================================
		부모 자식 오브젝트
	================================================== */
	GameObject* _parent;				//부모
	vector<GameObject*> _vChild;		//자식 벡터

public:
	GameObject();
	~GameObject() {}

	/* ==================================================
		오브젝트와 클론 생성
	================================================== */

	//오브젝트 만들기
	static GameObject* CreateObject(GameObject* parent = NULL);

	//클론 만들기
	template<typename T>
	T* GetClone();

	/* ==================================================
		부모 자식 설정
	================================================== */

	//부모 설정
	void SetParent(GameObject* parent);
	
	//자식 추가
	void AddChild(GameObject* child);
	
	//자식 제거
	void RemoveChild(GameObject* child);



	/* ==================================================
		컴포넌트 게터 세터
	================================================== */

	//컴포넌트 벡터 게터
	template<typename T>
	vector<T*> GetvComponent();

	//컴포넌트 게터
	template<typename T>
	T * GetComponent();

	//컴포넌트 추가
	template<typename T>
	T * AddComponent();

	//컴포넌트 제거
	void RemoveComponent(Component* component);

	//트랜스폼 게터
	TransformC* GetTransform() { return _transform; };

	
	/* ==================================================
		게터
	================================================== */
	GameObject* GetParent() { return _parent; };
	vector<GameObject*> GetvChild() { return _vChild; };
	//GameObject* GetChildByName(string name);

	string GetName() { return _name; };						//이름
	string GetTag() { return _tag; };						//태그
	string GetKey() { return _key; }						//키
	string GetDescription() { return _description; };		//설명

	bool GetActive() { return _isActive; }

	/* ==================================================
		세터
	================================================== */
	void SetName(string name) { _name = name; }
	void SetKey(string key) { _key = key; }
	void SetTag(string tag) { _tag = tag; }
	void SetDescription(string des) { _description = des; }
	void AddDescription(string des) { _vDescription.push_back(des); }

	void SetActive(bool active);
	void SetRender(bool render);
	/* ==================================================
		함수
	================================================== */
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

template<typename T>
inline vector<T*> GameObject::GetvComponent()
{
	vector<T*> componentVector;
	for (auto c : _vComponent)
	{
		if (dynamic_cast<T*>(c)) componentVector.push_back((T*)c);
	}
	return componentVector;
}

//컴포넌트 게터
template<typename T>
inline T * GameObject::GetComponent()
{
	for (Component* c : _vComponent)
	{
		if (dynamic_cast<T*>(c)) return (T*)c;
	}
	return NULL;
}

//컴포넌트 추가
template<typename T>
inline T * GameObject::AddComponent()
{
	Component* component = new T();
	component->LinkGameObject(this);
	_vComponent.push_back(component);
	component->Awake();
	return (T*)component;
}

//클론 만들기
template<typename T>
inline T * GameObject::GetClone()
{
	T* object = new T();
	memmove(object, this, sizeof(T*));
	return object;
}
