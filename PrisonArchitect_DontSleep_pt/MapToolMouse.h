#pragma once
#include "Mouse.h"

enum class TILEATTRIBUTE;
enum class MOUSEDRAG;
enum class MOUSESTATE;

class TileMap;
class MapToolScene;

class MapToolMouse : public Mouse
{
private:
	float _zoom;						//줌
	float _prevZoom;					//이전 줌

	GameObject* _cameraPivot;			//카메라 피봇
	GameObject* _cameraGoal;			//카메라 골

	Vector2 _startPoint;				//시작 점
	Vector2 _startIndex;				//시작 인덱스

	Vector2 _endPoint;					//끝 점
	Vector2 _endIndex;					//끝 인덱스

	bool _isDragging;					//드래그 중인지
	MOUSEDRAG _drag;					//드래그 상태

	vector<Vector2> _vSelectIndex;		//선택 타일 인덱스

	TileAttribute* _rollOverObj;			//롤오버 오브젝트

	TileAttribute* _selectObj;				//선택 오브젝트
	Character* _selectChar;					//선택 캐릭터
	int _charNum;

	TileMap* _tileMap;						//타일 맵
	MapToolScene* _scene;					//씬

	//마우스 지역
	FloatRect _mouseArea[4];

public:
	MapToolMouse(MapToolScene* scene);
	~MapToolMouse() {};

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//마우스 렌더
	void BuildRender();

	//마우스 컨트롤
	void Control();
	void Move();
	void OnUICheck();			//유아이 위에 있는 지 체크

    void UIControl();           //유아이
	void BuildControl();		//빌드
	void DestroyControl();		//파괴
	void SelectControl();		//선택
	void DeleteControl();		//삭제

	template<typename T>
	void OnCollisionEnter(T* obj);

	template<typename T>
	void OnCollisionExit(T* obj);

	template<typename T>
	void OnCollisionStay(T* obj);

	void DeleteMouseObject();

};

template<typename T>
inline void MapToolMouse::OnCollisionEnter(T * obj)
{
	SOUNDMANAGER->play("click4", DATAMANAGER->GetInfo().soundVolume);

	obj->MouseEnter();
}

template<typename T>
inline void MapToolMouse::OnCollisionExit(T * obj)
{
	obj->MouseExit();
}

template<typename T>
inline void MapToolMouse::OnCollisionStay(T * obj)
{
	obj->MouseStay();
}