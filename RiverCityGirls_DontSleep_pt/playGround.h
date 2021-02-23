#pragma once
#include "gameNode.h"

/*====================================================================
====================================================================*/

/*====================================================================

	(위의 두 줄은 기본 주석 스타일입니다.)
	전체적인 게임의 베이스가 되는 playGround입니다.
	map에 그려져야 하는 것들은 기본적으로 mapDC에 그려주세요.

====================================================================*/

class playGround : public gameNode
{
private:

public:
	playGround() {}
	~playGround() {}

	virtual HRESULT init();		//초기화 전용 함수
	virtual void release();		//메모리 해제 함수
	virtual void update();		//연산 전용
	virtual void render();		//그리기 전용

	void addScene();	//게임 내 모든 씬 추가

	void addSource();	//게임 내 모든 소스 추가
	void addImage();	//게임 내 모든 이미지 추가
	void addSound();	//게임 내 모든 소리 추가

};

