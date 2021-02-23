#pragma once
#include "Scene.h"
#include "Select.h"
#include <functional>

/*====================================================================
	선택씬입니다. 로드, 캐릭터, 메뉴얼로 구성되어 있습니다.
====================================================================*/
enum class SELECTTYPE
{
	LOAD,
	CHARACTER,
	MANUAL,
};


class SelectScene : public Scene
{
private:
	SELECTTYPE _state;			//현재 선택 씬의 상태

	Select* _loadSelect;		//로드할 파일 선택
	Select* _charSelect;		//캐릭터 선택

	vector3 loop;				//배경 루프

	image* _background2;		//배경2

	image* _illust;				//좌측 캐릭터 일러스트
	vector3 _illustPos;
	Interpolation* _illustInter;
	float _ratioOffset;
	float _ratioTime;

	bool _kyokoSelect;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load(int n);	//로드 버튼 콜백 함수
	void load0();		//로드 버튼 콜백 함수
	void load1();		//로드 버튼 콜백 함수
	void load2();		//로드 버튼 콜백 함수
	void load3();		//로드 버튼 콜백 함수

	void character0();	//캐릭터 버튼 콜백 함수
	void character1();	//캐릭터 버튼 콜백 함수




	void setState(SELECTTYPE type);
};

