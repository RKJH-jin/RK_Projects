#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init()
{
	/*====================================================================
		배경과 카메라의 맵 사이즈를 설정한다.
	====================================================================*/
	_background = IMG_M->findImage("load_background");
	CAMERA_M->SetMap(*this, _background);


	/*====================================================================
		UI 로딩 바를 호출한다.
	====================================================================*/
	_max = 10;
	_count = 0;

	UI_M->setIsActive(true);
	UI_M->addBar("loadingBar", IMG_M->findImage("bossHPFront"), IMG_M->findImage("bossHPBack"), vector3(200, 600, 0), &_count, &_max);
	UI_M->findUI("loadingBar")->setActive(true);

	/*====================================================================
		스프라이트 이미지와 애니메이션을 설정한다.
	====================================================================*/
	_sprite = IMG_M->findImage("loading_sprite");
	ani = new animation;
	ani->init(_sprite->getWidth(), _sprite->getHeight(), _sprite->getFrameWidth(), _sprite->getFrameHeight());
	ani->setDefPlayFrame(false, true);
	ani->setFPS(1);
	ani->start();

	/*====================================================================
		싱글 쓰레드를 사용한다.
	====================================================================*/
	CreateThread(
		NULL,				//스레드의 보안속성(자식윈도우가 존재할때)
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드 크기와 동일)
		threadFunction,		//스레드 사용할 함수 명
		this,				//스레드 매개변수(this로 두면 본 클래스)
		NULL,				//스레드의 특성(기다릴지, 바로 실행(NULL이면 요게 해당))
		NULL				//스레드 생성 후 스레드의 ID 넘겨줌 보통은 NULL로 둔다
	);
	
	return S_OK;
}

void LoadingScene::release()
{
}

void LoadingScene::update()
{
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	ani->frameUpdate(0.1f);

	//로딩이 다 되면
	if (_count == _max)
	{
		UI_M->findUI("loadingBar")->setActive(false);
		SCENE_M->changeScene("game");
	}
}

void LoadingScene::render()
{
	_background->render(getMapDC());
	_sprite->aniRender(getMapDC(), WINSIZEX - 150, WINSIZEY - 220, ani);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	LoadingScene* helper = (LoadingScene*)lpParameter;

	while (helper->_count!=helper->_max)
	{
		Sleep(1);
		++helper->_count;
	}

	return 0;
}
