#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _pixelBuffer = IMAGEMANAGER->addImage("pixelBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	

public:
	gameNode();
	virtual ~gameNode();

	//HRESULT는 마소 전용 디버깅 반환자 임
	//S_OK, E_FAIL, SUCCEDED 등으로 return값을 가짐
	//제대로 초기화 됐는지 안됐는지 호출해줌

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit, int width, int height);	//초기화 전용 함수				
	virtual void release();									//메모리 해제 함수
	virtual void update();									//연산 전용
	virtual void render();							//그리기 전용

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getPixelMemDC() { return _pixelBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

