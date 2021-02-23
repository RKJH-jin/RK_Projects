#include "stdafx.h"
#include "SelectScene.h"
#include <string>

HRESULT SelectScene::init()
{
	/*====================================================================
		선택 씬에서 세이브 파일을 로딩할 수 있게 합니다.
		세이브 파일, 캐릭터 선택, 옵션, 메뉴얼 창 등 게임 시작 전의 모든 선택을 합니다.
	====================================================================*/

	/*====================================================================
		맵의 사이즈를 지정하고, 타이틀은 UI로 취급하며, 배경은 루프시킵니다.
	====================================================================*/
	_background = IMG_M->findImage("select_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);
	_background2 = IMG_M->findImage("select_background2");

	/*====================================================================
		두 캐릭터 이미지를 선형 보간으로 이동시킵니다.
	====================================================================*/
	_illust = IMG_M->findImage("select_illust");
	_illustPos = vector3(350.0f, WINSIZEY / 2 + 360.0f, 0.0f);
	_illustInter = new Interpolation;
	_illustInter->moveTo(&_illustPos, 450, WINSIZEY / 2 + 360, 0.5f);
	_ratioOffset = 0.001f;

	/*====================================================================
		UI에 선택 이미지를 추가하고, 선택할 수 있도록 합니다.
	====================================================================*/
	int _loadNum[4];

	for (int i = 0; i < 4; i++)
	{
		_loadNum[i] = DATA_M->getStage(i);
	}

	//로드 파일 선택 버튼
	_loadSelect = new Select;

	string txt1;
	string txt2;


	txt1 = "save_load_close" + to_string(_loadNum[0] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[0] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 1, 0), std::bind(&SelectScene::load0, this), 0));

	txt1 = "save_load_close" + to_string(_loadNum[1] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[1] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 2, 0), std::bind(&SelectScene::load1, this), 1));

	txt1 = "save_load_close" + to_string(_loadNum[2] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[2] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 3, 0), std::bind(&SelectScene::load2, this), 2));

	txt1 = "save_load_close" + to_string(_loadNum[3] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[3] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 4, 0), std::bind(&SelectScene::load3, this), 3));


	//캐릭터 선택 버튼과 이미지
	_charSelect = new Select;
	_charSelect->addButton(Button(IMG_M->findImage("select_kyoko2"), IMG_M->findImage("select_kyoko"), vector3(WINSIZEX/2 + 100, WINSIZEY / 2, 0), std::bind(&SelectScene::character0, this), 0));
	_charSelect->addButton(Button(IMG_M->findImage("select_misako2"), IMG_M->findImage("select_misako"), vector3(WINSIZEX/2 + 450, WINSIZEY / 2, 0), std::bind(&SelectScene::character1, this), 1));
	_kyokoSelect = false;

	//옵션 UI와 버튼


	//메뉴얼 UI와 버튼


	/*====================================================================
		첫 상태를 로드로 설정합니다. LOAD - OPTION - MANUAL 후에 로딩씬으로 이어집니다.
	====================================================================*/
	setState(SELECTTYPE::LOAD);

	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	/*====================================================================
		캐릭터 일러스트의 이동과 확대 축소 효과를 진행하고
		배경을 x+1, y+1 대각선 방향으로 루프 시킵니다.
	====================================================================*/
	loop.x++; loop.y++;

	_illustInter->update();
	_ratioOffset = (TIME_M->getWorldTime() - _ratioTime) * 0.04f;
	if (TIME_M->getWorldTime() - _ratioTime > 0.35f) _ratioTime = TIME_M->getWorldTime();

	/*====================================================================
		카메라는 중앙에 고정시키고, 엔터를 치면 다음 씬으로 넘깁니다.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================

	====================================================================*/
	switch (_state)
	{
		/*====================================================================
			버튼을 선택하고, 선택이 된 후에는 캐릭터 선택으로 넘어갑니다.
		====================================================================*/
		case SELECTTYPE::LOAD:
		if (_loadSelect->update()) setState(SELECTTYPE::CHARACTER);
		break;

		/*====================================================================
			캐릭터를 선택하고, 옵션창으로 넘어갑니다.
		====================================================================*/
		case SELECTTYPE::CHARACTER:
		_charSelect->update();
		if(_kyokoSelect) setState(SELECTTYPE::MANUAL);
		break;
		/*====================================================================
			메뉴얼 UI를 띄우고, 씬을 로딩씬으로 변경합니다.
		====================================================================*/
		case SELECTTYPE::MANUAL:
		if (!EVENT_M->getIsEvent())
		{
			if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)))
			{
				SCENE_M->changeScene("loading");			//로딩 씬으로 변경
			}
		}
		break;
		default:
		break;
	}
}

void SelectScene::render()
{
	/*====================================================================
		배경을 loop 값에 따라 루프 렌더하고, 캐릭터 이미지를 띄워 줍니다.
	====================================================================*/
	
	switch (_state)
	{
	case SELECTTYPE::LOAD: case SELECTTYPE::CHARACTER:
		_background->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
		_background2->render(getMapDC());
		IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f, 720 / 900.0f);
		_illust->render(getMapDC(), _illustPos.x - _illustPos.x*_ratioOffset, _illustPos.y - _illustPos.y *_ratioOffset, 0.7f + _ratioOffset, 0.7f + _ratioOffset);

		break;
	case SELECTTYPE::MANUAL:
		IMG_M->findImage("SelectScene_manual")->render(getMapDC());

		break;
	default:
		break;
	}

	/*====================================================================
		UI 및 텍스트를 출력합니다.
	====================================================================*/
	switch (_state)
	{
		case SELECTTYPE::LOAD:
		{
			_loadSelect->render(getMapDC());

		}
		break;
		case SELECTTYPE::CHARACTER:
			IMG_M->findImage("select_kyoko_background")->render(getMapDC(), WINSIZEX / 2 + 100, WINSIZEY / 2);
			IMG_M->findImage("select_misako_background")->render(getMapDC(), WINSIZEX / 2 + 450, WINSIZEY / 2);
			_charSelect->render(getMapDC());
		break;
		case SELECTTYPE::MANUAL:
		{
			//폰트에 대해 설정한다.
			SetBkMode(getMapDC(), TRANSPARENT);
			SetTextColor(getMapDC(), RGB(0, 0, 0));
			HFONT font, oldFont;
			RECT rcText = RectMake(WINSIZEX/2, 120, 400, 720);
			font = CreateFont(50, 0, 0, 0, 0, false, false, false,
				DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
				PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
			oldFont = (HFONT)SelectObject(getMapDC(), font);

			string _txt = "이동: 방향키 / 점프: A \n약공: S / 강공: D \n커맨드공격: → + ↓ + D \n가드: F / 회피:W \n줍기:E / 동료:Q \n인벤: V / 맵 이동 : M \n선택 : SPACEBAR or ENTER / 종료 : ESC \n디버깅 : SHIFT or TAB" ;
			
			//텍스트를 출력한다.
			DrawText(getMapDC(), TEXT(_txt.c_str()), strlen(_txt.c_str()), &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
			//폰트를 삭제한다.
			DeleteObject(font);
		}
		break;
		default:
		break;
	}
}

/*====================================================================
	버튼 선택에 따라 세이브 파일을 로드합니다.
====================================================================*/
void SelectScene::load(int n)
{
	DATA_M->setFileNum(n);
	DATA_M->loadIniData(n);
}
void SelectScene::load0()
{
	load(0);
}
void SelectScene::load1()
{
	load(1);
}
void SelectScene::load2()
{
	load(2);
}
void SelectScene::load3()
{
	load(3);
}

/*====================================================================
	버튼 선택에 따라 캐릭터를 로드합니다.
====================================================================*/
void SelectScene::character0()
{
	_kyokoSelect = true;
}

void SelectScene::character1()
{
	_kyokoSelect = false;
	_charSelect = new Select;
	_charSelect->addButton(Button(IMG_M->findImage("select_kyoko2"), IMG_M->findImage("select_kyoko"), vector3(WINSIZEX / 2 + 100, WINSIZEY / 2, 0), std::bind(&SelectScene::character0, this), 0));
	_charSelect->addButton(Button(IMG_M->findImage("select_misako2"), IMG_M->findImage("select_misako"), vector3(WINSIZEX / 2 + 450, WINSIZEY / 2, 0), std::bind(&SelectScene::character1, this), 1));
	_charSelect->_index = 1;
}

/*====================================================================
	선택 씬의 상태를 설정합니다.
====================================================================*/
void SelectScene::setState(SELECTTYPE type)
{
	_state = type;

	switch (_state)
	{
		case SELECTTYPE::LOAD:
		break;
		case SELECTTYPE::CHARACTER:
		break;
		case SELECTTYPE::MANUAL:
		break;
		default:
		break;
	}
	/*====================================================================
		화면 상태가 바뀔 때마다 카메라 움직임과 대기 이벤트를 실행합니다.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.05, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
}
