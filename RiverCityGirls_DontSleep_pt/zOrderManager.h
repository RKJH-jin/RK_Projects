#pragma once
#include "singletonBase.h"

class GameObject;
enum class RENDERTYPE;

/*====================================================================
		Z값에 따라 정렬 한 후 렌더 해 주는 매니저입니다.
		tagZorder는 Zorder에 따라 정렬할 객체 구조체입니다.
====================================================================*/

struct tagZorder 
{
public:
	tagZorder() {}
	~tagZorder() {}

	HDC hdc;			//그릴 hdc
	image* img;			//이미지
	animation* ani;		//애니메이션
	POINT imgIndex;		//프레임 인덱스

	vector3 pos;		//위치
	vector3 zPos;		//Sorting용 pos
	vector3 size;		//크기
	vector3 shadowPos;	//그림자 위치
	RECT rc;			//렉트
	bool isShadow;		//그림자 여부
	int alpha;			//불투명도
	RENDERTYPE renderType;	//렌더 형태

	bool yOffset;
};

class zOrderManager : public singletonBase <zOrderManager>
{
private:
	vector<tagZorder> _vZorder;

public:
	zOrderManager() {}
	~zOrderManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	//벡터에 오브젝트를 넣는다.
	void renderObject(HDC hdc, GameObject* go, RENDERTYPE renderType);
	
	//벡터를 정렬한다.
	void sortVector(int s, int e);

};

