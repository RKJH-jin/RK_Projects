#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <shlwapi.h>


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"

#include "utils.h"
#include "txtData.h"
#include "vector3.h"
#include "Interpolation.h"


#include "imageManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "zOrderManager.h"
#include "EventManager.h"
#include "UIManager.h"
#include "soundManager.h"
#include "DataManager.h"
#include "Enums.h"

#pragma comment(lib, "shlwapi.lib")
using namespace std;
using namespace TFIVE_UTIL;

//==================================
// ## 디파인 문 ## 20.11.12 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("River City Girls"))
#define WINSTARTX 50		//윈도우 시작좌표 X지점
#define WINSTARTY 50		//윈도우 시작좌표 Y지점
#define WINSIZEX 1280		//윈도우 가로크기
#define WINSIZEY 720		//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEY_M keyManager::getSingleton()
#define IMG_M imageManager::getSingleton()
#define CAMERA_M cameraManager::getSingleton()
#define SCENE_M SceneManager::getSingleton()
#define TIME_M timeManager::getSingleton()
#define EFFECT_M effectManager::getSingleton()
#define ZORDER_M zOrderManager::getSingleton()
#define EVENT_M EventManager::getSingleton()
#define UI_M UIManager::getSingleton()
#define SOUND_M soundManager::getSingleton()
#define DATA_M DataManager::getSingleton()
#define TXTDATA txtData::getSingleton()

#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//==================================
// ## extern ## 20.11.16 ##
//==================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;