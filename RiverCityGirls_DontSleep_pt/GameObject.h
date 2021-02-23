#pragma once
#include "Linear.h"

/*====================================================================
	Z-Order와 충돌 처리를 위해 Player, Enemy, Object 등
	게임 오브젝트에 전체적으로 쓰이는 GameObject 클래스입니다.
====================================================================*/


struct tagShadow
{
	RECT rc;
	vector3 LT, RT, RB, LB;
	vector3 pos;
	float width, height;
};

class GameObject
{
public:
	GameObject* obstacle;
	OBJECT_GROUP group;		//그룹
	OBJECT_TYPE type;		//오브젝트 타입
	OBJECT_DESTRUCTION des; //파괴가능 여부
	int destructionCount;	//파괴까지 횟수
	WEAPON_TYPE weaponType;	//무기 타입
	ITEM_TYPE itemType;		//아이템 타입
	
	DIRECTION dir;			//오브젝트 방향

	image* img;				//이미지
	POINT imgIndex;			//프레임 인덱스
	animation* ani;			//애니메이션
	animation* ani1;		//애니메이션
	vector3 pos;			//위치
	vector3 prePos;			//이전 위치
	vector3 size;			//크기 (x,z)
	RECT rc;				//렉트

	Linear topPlane[4];		//위 평면
	Linear bottomPlane[4];	//아래 평면
	Linear sideHeight[4];	// 그리기 전용 선분들, 충돌 처리에는 안 씀

	int alpha;				//불투명도 (0~255)

	float angle;			//각도
	float zAngle;			//Z각도
	float margin;			//z여백

	bool isActive;			//활성화 여부
	bool isRender;			//렌더 여부
	bool isShadow;			//그림자가 있는지
	bool isBroken;			//오브젝트 파괴여부

	tagShadow shadow;		//그림자 구조체
	tagShadow preShadow;
public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos);				//초기화
	virtual void init(OBJECT_GROUP _group, OBJECT_TYPE _type, image* _img, vector3 _pos, float a);		//오브젝트 여백 초기화

	virtual void release();
	virtual void update();
	virtual void render();
	
/*====================================================================
								FUNCTION
====================================================================*/
	void RectRenew();		//렉트 갱신
	void shadowUpdate();
	void PolyLineRender(HDC hdc);	//디버깅용 선 렌더


/*====================================================================
								SETTER
====================================================================*/
	void setGOAni(animation* an) { ani = an; }
	void setPosX(float x) { pos.x = x; }
	void setPosY(float y) { pos.y = y; }
	void setPosZ(float z) { pos.z = z; }
};

