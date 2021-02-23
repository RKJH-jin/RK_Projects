#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	/*====================================================================
		타이틀 씬에서 인트로 등의 연출을 진행합니다. 음악과 인트로 영상을 재생합니다.
	====================================================================*/
	SOUND_M->playMusic("openingBG");
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::GAME_INTRO));

	/*====================================================================
		맵의 사이즈를 지정하고, 타이틀은 UI로 취급하며, 배경은 루프시킵니다.
	====================================================================*/
	_background = IMG_M->findImage("start_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		두 캐릭터 이미지를 선형 보간으로 이동시킵니다.
	====================================================================*/
	_kyoko = IMG_M->findImage("start_kyoko");
	_misako = IMG_M->findImage("start_misako");

	_kyokoPos = vector3(700.0f, WINSIZEY / 2 + 200.0f, 0.0f);
	_misakoPos = vector3(1000.0f, WINSIZEY / 2 + 200.0f, 0.0f);

	_kyokoInter = new Interpolation;
	_misakoInter = new Interpolation;

	/*====================================================================
		UI에 타이틀 이미지를 추가하고, UI 이동을 실행시킵니다.
	====================================================================*/
	UI_M->setIsActive(true);
	UI_M->addImage("title", IMG_M->findImage("start_title"), vector3(WINSIZEX / 2 - 500, WINSIZEY / 2 - 100, 0));
	UI_M->findUI("title")->setActive(true);
	_titleInter = new Interpolation;

	/*====================================================================
		카메라 움직임과 대기 이벤트를 실행합니다.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(1.5f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(1.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.05, 0.005f));
	EVENT_M->addEvent(new waitForSec(1.5f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));

	return S_OK;
}

void TitleScene::release()
{

}

void TitleScene::update()
{
	/*====================================================================
		카메라는 중앙에 고정시킵니다.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================
		배경을 x+1, y+1 대각선 방향으로 루프 시키고,
		캐릭터를 선형 보간을 통해 이동시킵니다.
	====================================================================*/
	loop.x++; loop.y++;

	_kyokoInter->moveTo(&_kyokoPos, 1050.0f, WINSIZEY / 2 + 200.0f, 0.7f);
	_misakoInter->moveTo(&_misakoPos, 800.0f, WINSIZEY / 2 + 200.0f, 0.7f);
	_titleInter->moveTo(UI_M->findUI("title")->_pos, WINSIZEX / 2 - 500, WINSIZEY / 2 - 200, 1.0f);

	_kyokoInter->update();
	_misakoInter->update();
	_titleInter->update();

	/*====================================================================
		엔터를 치면 타이틀 UI를 빼고 다음 씬으로 넘깁니다.
	====================================================================*/
	if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)) && !EVENT_M->getIsEvent())
	{
		UI_M->findUI("title")->setActive(false);	//title UI 비활성화
		UI_M->popUI("title");						//title UI 아예 삭제
		SCENE_M->changeScene("select");				//선택 씬으로 변경
	}
}

void TitleScene::render()
{
	/*====================================================================
		배경을 loop 값에 따라 루프 렌더하고, 캐릭터 이미지를 띄워 줍니다
	====================================================================*/
	_background->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f, 720 / 900.0f);
	_kyoko->render(getMapDC(), _kyokoPos.x, _kyokoPos.y ,0.8f, 0.8f);
	_misako->render(getMapDC(), _misakoPos.x , _misakoPos.y, 0.8f, 0.8f);

	//폰트에 대해 설정한다.
	SetBkMode(getMapDC(), TRANSPARENT);
	SetTextColor(getMapDC(), RGB(255, 255, 255));
	HFONT font, oldFont;

	//메뉴얼
	font = CreateFont(60, 0, 70, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(getMapDC(), font);
	TextOut(getMapDC(), 120, 600, "PRESS ENTER TO START!", strlen("PRESS ENTER TO START!"));

	//폰트를 삭제한다.
	DeleteObject(font);
}
