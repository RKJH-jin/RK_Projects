#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <map>
#include <functional>
#include <list>
#include <queue>
#include <stack>

//boost
#include <fstream>
#include "boost\archive\binary_oarchive.hpp"
#include "boost\archive\binary_iarchive.hpp"
#include "boost\archive\text_oarchive.hpp"
#include "boost\archive\text_iarchive.hpp"
#include "boost\serialization\serialization.hpp"
#include "boost\serialization\string.hpp"
#include "boost\serialization\vector.hpp"
#include "boost\serialization\map.hpp"
#include "boost\serialization\array.hpp"
#include "boost\serialization\collections_save_imp.hpp"
#include "boost\serialization\collections_load_imp.hpp"
#include "boost\serialization\split_free.hpp"
#include "boost\serialization\utility.hpp"
#include "boost\serialization\export.hpp"
using namespace std;


enum class Pivot : int
{
	LeftTop,Center,Bottom
};

namespace Direction
{
	enum Enum : int
	{
		Left = 1,
		Top = 2,
		Right = 4,
		Bottom = 8,
		LeftTop = Left | Top,
		LeftBottom = Left | Bottom,
		RightTop = Right | Top,
		RightBottom = Right | Bottom,
		End = 0
	};
}

#include "AllEnums.h"

#include "LibraryHeader.h"

#include "Vector2.h"
#include "Math.h"
#include "FloatRect.h"
#include "Figure.h"

using namespace Figure;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "D2DRenderer.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "DataManager.h"
#include "image.h"

#include "JumpPointSearch.h"

#include "GameObject.h"
#include "AllComponents.h"

#include "TileMap.h"


//MS VS버전이 올라가면서 기존의 문자열 함수의 안정성을 올리기위해
//_s를 붙인 함수를 사용하게끔 경고하는 메시지를 무시해준다


// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("Don't Sleep - Prison Arichtect"))
#define WINSTARTX	360
#define WINSTARTY	50
#define WINSIZEX	1280		
#define WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER ImageManager::GetInstance()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define CAMERAMANAGER CameraManager::GetInstance()
#define UIMANAGER UIManager::getSingleton()
#define JPSMANAGER JumpPointSearch::GetInstance()

#define DATAMANAGER DataManager::GetInstance()

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}
#define NEW_SAFE_RELEASE(p) {if(p){p->Release(); (p) = NULL;}}

#define Synthesize(ValueType,ValueName,FuncName) \
protected: ValueType ValueName;\
public: inline ValueType Get##FuncName(void) const{return ValueName;}\
public: inline void Set##FuncName(ValueType value){ValueName = value;}

//====================================
// ## 20.05.29 ## Extern ##
//====================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern Vector2		_ptMouse;
extern HDC			_hdc;
extern int			_wheelMouse;