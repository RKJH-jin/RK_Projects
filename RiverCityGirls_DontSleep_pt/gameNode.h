#pragma once
#include "image.h"


//백버퍼라는 빈 비트맵 이미지를 하나 생성 해 둔다.
static image* _backBuffer = IMG_M->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _mapBuffer = IMG_M->addImage("mapBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//매니저 초기화 할 건지 유무

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();					//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();					//메모리 해제 함수
	virtual void update();					//연산 전용
	virtual void render();					//그리기 전용

	//백버퍼 설정자
	void setBackBuffer(int _mapXSize, int _mapYSize) { _backBuffer->init(_mapXSize, _mapYSize); }
	void setMapBuffer(int _mapXSize, int _mapYSize) { _mapBuffer->init(_mapXSize, _mapYSize); }
	
	//hdc 접근자
	HDC getHDC() { return _hdc; }

	//백버퍼 접근자
	HDC getBackDC() { return _backBuffer->getMemDC(); }

	//맵버퍼 접근자
	HDC getMapDC() { return _mapBuffer->getMemDC(); }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

