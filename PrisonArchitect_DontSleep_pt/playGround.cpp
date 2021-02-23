#include "stdafx.h"
#include "playGround.h"
#include "TitleScene.h"
playGround::playGround()
{
}

playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	// ============================ 디버그 용 ============================
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	using namespace std;
	// ==================================================================
	
	//소스 추가
	AddSource();

	//csv를 읽어 온다.
	_csv.read();

	//메인 카메라
	CAMERAMANAGER->CreateCamera(FloatRect(0, 0, WINSIZEX, WINSIZEY));

	//타이틀 씬 추가
	SCENEMANAGER->PushScene(new TitleScene);

	return S_OK;
}

//메모리 해제
void playGround::release()
{

}

//연산
void playGround::update()
{
	gameNode::update();
	
	//씬 업데이트
	SCENEMANAGER->Update();
}

//그리기 전용
void playGround::render()
{	
	//백버퍼 랜더를 시작한다.
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);

	//씬을 렌더한다.
	SCENEMANAGER->Render();

	//백버퍼 렌더를 끝낸다.
	D2DRenderer::GetInstance()->EndRender();
}
