#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>		//timeGetTime을 쓰기위해 헤더를 건다

#pragma comment(lib, "winmm.lib")

timer::timer()
{
}

timer::~timer()
{
}

HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		_timeScale = 1.0f / _periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{

	//CPU 에게 신호를 주어 다시 되돌아오는 시간을 센다
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	//총 경과시간
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//요부분이 프레임 스키핑
	if (lockFPS > 0.0f)
	{
		//초당 프레임 산정
		while (_timeElapsed < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
