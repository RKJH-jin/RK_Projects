#pragma once
#include "Event.h"
#include <queue>

struct tagDialouge
{
	image* portrait;
	image* name;
	vector3 pos;
};

class DialogueManager : public Event
{
	queue<string>		_qMsg;		//메시지
	queue<tagDialouge>	_qImg;		//이미지



public:
	virtual void enter() { _isEnd = false; _isMovie = false; }
	virtual bool update();
	virtual void exit();
};

