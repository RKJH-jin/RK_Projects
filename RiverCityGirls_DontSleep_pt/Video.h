#pragma once
#include "gameNode.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

/*====================================================================
	비디오 클래스입니다. 파일 경로를 입력하면 해당 영상을 재생합니다.
====================================================================*/

class Video : public gameNode
{
private:

	HWND _video;			//영상
	char _file[30];			//파일 경로
	bool _isPlaying;		//재생 여부

public:

	virtual HRESULT init(const char* videoFile);

	void play();	//재생
	void stop();	//멈춤

	bool getIsPlaying() { return _isPlaying; }
	HWND getVideo() { return _video; }
};