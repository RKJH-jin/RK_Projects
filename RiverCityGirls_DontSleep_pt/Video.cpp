#include "stdafx.h"
#include "Video.h"

HRESULT Video::init(const char * videoFile)
{
	this->stop();
	_isPlaying = false;
	sprintf_s(_file, videoFile);
	_video = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU | MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR, _file);
	return S_OK;
}

void Video::play()
{
	MoveWindow(_video, 0, 0, WINSIZEX, WINSIZEY, NULL);
	MCIWndPlay(_video);
	_isPlaying = true;
}

void Video::stop()
{
	if (!_isPlaying) return;
	RECT _temp;
	GetWindowRect(_hWnd, &_temp);
	MCIWndDestroy(_video);
	MoveWindow(_hWnd, _temp.left, _temp.top, _temp.right - _temp.left, _temp.bottom - _temp.top, true);
	_isPlaying = false;
}

