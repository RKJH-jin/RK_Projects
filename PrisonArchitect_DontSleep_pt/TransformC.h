#pragma once
#include "Component.h"
#include "JumpPointSearch.h"

class TransformC : public Component
{
private:
	Vector2 _pivot;			//피벗
	Vector2 _pos;			//위치
	Vector2 _index;         //인덱스
	DIRECTION _direction;	//방향

	Vector2 _size;		//크기
	FloatRect _rc;	//렉트

	Camera* _camera;

	bool haveTarget = false;
	Vector2 _target;		//목표지점
	stack<Vector2> _path;	//목표까지의 경로
	Vector2 _endIndex;		//끝 인덱스
	bool arriveEndIndex = false;
public:
	TransformC() {};
	~TransformC() {};

	//게터
	Vector2 GetPosition() { return _pos; }
	Vector2 GetPivot() { return _pivot; }
	DIRECTION GetDirection() { return _direction; }

	RECT GetRect();
	FloatRect GetFloatRect() { return _rc; }

	Vector2 GetIndex() { return _index; }
	Vector2 GetTarget() { return _target; }
	stack<Vector2>& GetPath() { return _path; }
	bool GetHaveTarget() { return haveTarget; }
	Vector2 GetEndIndex() { return _endIndex; }
	bool GetArriveEndIndex() { return arriveEndIndex; }

	//세터
	void SetPosition(Vector2 pos);
	void SetPivot(Vector2 pivot) { _pivot = pivot; _pos = pivot; };
	void SetDirection(DIRECTION direction) { _direction = direction; }
	void SetSize(Vector2 size) { _size = size; }

	void SetCamera(Camera* camera) { _camera = camera; }

	void SetIndex(Vector2 idx) { _index = idx; }
	void SetTarget(Vector2 target) { _target = target; }
	void SetPath(Vector2 endIndex)
	{
		_endIndex = endIndex;
		_index = Vector2((int)(_pos.x / TILESIZE), (int)(_pos.y / TILESIZE));
		_path = JumpPointSearch::GetInstance()->PathFinding(_index, _endIndex);
	}
	void SetHaveTarget(bool boolValue) { haveTarget = boolValue; }
	void SetArriveEndIndex(bool boolValue) { arriveEndIndex = boolValue; }

	//함수
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Translate(Vector2 delta);
	void SetRect();

};

