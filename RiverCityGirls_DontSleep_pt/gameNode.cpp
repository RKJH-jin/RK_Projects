#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		KEY_M->init();
		IMG_M->init();
		TIME_M->init();
		EFFECT_M->init();
		SCENE_M->init();
		SOUND_M->init();
		TXTDATA->init();
		CAMERA_M->init();
		EVENT_M->init();
		DATA_M->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		CAMERA_M->release();
		CAMERA_M->releaseSingleton();

		EFFECT_M->release();
		EFFECT_M->releaseSingleton();

		IMG_M->release();
		IMG_M->releaseSingleton();

		KEY_M->release();
		KEY_M->releaseSingleton();

		SCENE_M->release();
		SCENE_M->releaseSingleton();

		TIME_M->release();
		TIME_M->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		EVENT_M->release();
		EVENT_M->releaseSingleton();

		SOUND_M->release();
		SOUND_M->releaseSingleton();

		DATA_M->release();
		DATA_M->releaseSingleton();

		ZORDER_M->release();
		ZORDER_M->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	EVENT_M->update();

}

void gameNode::render()
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;


		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
