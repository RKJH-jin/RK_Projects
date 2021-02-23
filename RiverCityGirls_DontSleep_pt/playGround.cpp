#include "stdafx.h"
#include "playGround.h"

#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "ShopScene.h"

// ============================ 디버그 용 ============================
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
// ==================================================================

/*====================================================================

	플래이그라운드 초기화입니다. 이곳에서 이미지와 씬을 설정합니다.
	setScene 후 changeScene을 통해 시작 씬을 설정합니다.
	title이 기본이며, 테스트하고 싶은 씬이 있다면 init에서 해당 씬으로 change 해주세요.

====================================================================*/
HRESULT playGround::init()
{
	gameNode::init(true);
	addSource();						//소스 추가
	addScene();							//씬 세팅
	SCENE_M->changeScene("title");		//첫 시작씬 (title)

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

/*====================================================================

	플래이그라운드 업데이트입니다. 기본적으로 항상 현재 씬을 업데이트 하지만,
	영상 재생 중에는 렌더와 업데이트가 멈춰야 하므로 이벤트 매니저가
	영상을 재생 중이라고 하면 씬에 대한 업데이트를 하지 않고 return합니다.

====================================================================*/
void playGround::update()
{
	gameNode::update();						//게임 노드에서 매니저들을 업데이트한다.

	if (EVENT_M->getIsMovie()) return;		//영상 재생 중에는 업데이트 하지 않는다.
	EFFECT_M->update();						//이팩트매니저 업데이트
	CAMERA_M->update();						//카메라를 업데이트 한다.
	UI_M->update();							//UI 업데이트
	SCENE_M->update();						//씬 업데이트
	SOUND_M->update();

	//================= 디버깅 용 =================
	if (KEY_M->isOnceKeyDown(VK_F12)) DATA_M->checkData();
	if (KEY_M->isOnceKeyDown(VK_F7))
	{
		DATA_M->saveStageData();
		DATA_M->addData();
		DATA_M->saveIniData(DATA_M->getFileNum());
	}
	if (KEY_M->isOnceKeyDown(VK_F8))
	{
		if (DATA_M->loadIniData(DATA_M->getFileNum())) DATA_M->loadStageData();
	}
}

/*====================================================================

	플래이 그라운드에서 렌더를 하며, 기본적으로 BackDC에 하얀 배경을 깔고,
	영상 재생 중엔 이중버퍼링을 하지 말아야 하기 때문에 return합니다.

	이벤트 매니저가 영상 재생 중이 아닐 경우,
	씬이 mapDC에 렌더하고, 카메라가 map과 UI를 backDC에 렌더합니다.
	TAB을 토글할 경우 fps 등 디버깅용 렌더가 실행되며,
	마지막으로 HDC에 backDC를 이중 버퍼링합니다.

====================================================================*/
void playGround::render()
{
	PatBlt(getBackDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);	//하얀 배경
	
	//================ 렌더 시작 =================
	if (EVENT_M->getIsMovie()) return;	//영상 재생 중에는 렌더하지 않는다.
	SCENE_M->render();								//씬 렌더
	
	CAMERA_M->render(getBackDC(),_mapBuffer);		//카메라 렌더
	EVENT_M->render(getBackDC());					//이벤트 렌더

	//================= 디버깅 용 =================
	//FPS 확인
	if (KEY_M->isToggleKey(VK_TAB)) TIME_M->render(getBackDC());
	
	//================= 이중 버퍼링 =================
	_backBuffer->render(getHDC());
}

/*====================================================================

	씬을 세팅합니다. 타이틀, 게임, 상점, 엔딩 네가지가 있습니다.
	씬끼리는 프로시져 자체를 막아 데이터 이동이 불가능합니다.

====================================================================*/
void playGround::addScene()
{
	SCENE_M->addScene("title", new TitleScene);			//타이틀 씬 추가
	SCENE_M->addScene("select", new SelectScene);		//선택 씬 추가
	SCENE_M->addScene("loading", new LoadingScene);		//로딩 씬 추가
	SCENE_M->addScene("game", new GameScene);			//게임 씬 추가
	SCENE_M->addScene("shop", new ShopScene);			//상점 씬 추가
}
