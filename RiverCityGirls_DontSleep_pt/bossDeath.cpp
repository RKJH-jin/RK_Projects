#include "stdafx.h"
#include "bossDeath.h"
#include "Boss.h"

void bossDeath::EnterState()
{	
	_thisBs->ChangeImg("Bs_death");
	SOUND_M->playSFX("bdeath");
	LookatPlayer();
	ResetFrame();	
	_enterTime = TIME_M->getWorldTime();

	_event = false;
}

void bossDeath::UpdateState()
{
	if ( _thisBs->getObj()->imgIndex.x == _thisBs->getObj()->img->getMaxFrameX() && _thisBs->getInfo().dest == DIRECTION::RIGHT)
	{			
		_thisBs->getObj()->imgIndex.x = 9;			
	}

	if (_thisBs->getObj()->imgIndex.x == 0 && _thisBs->getInfo().dest == DIRECTION::LEFT)
	{		
		_thisBs->getObj()->imgIndex.x = 3;		
	}

	if (!_event)
	{
		EVENT_M->addEvent(new dialogue(DIALOGLIST::BOSS_END), false);
		//EVENT_M->addEvent(new waitForSec(3.5f), false);
		_event = true;
	}

	if(!EVENT_M->getIsEvent() && !_UI)
	{
		SOUND_M->playMusic("endingBG");
		UI_M->addEndingUI("endingUI");
		UI_M->findUI("endingUI")->setActive(true);
		_UI = true;
	}

	if (_UI && ( KEY_M->isOnceKeyDown(VK_SPACE) || KEY_M->isOnceKeyDown(VK_RETURN)))
	{
		UI_M->deleteAll();
		SCENE_M->setInitScene("title");
	}
}

void bossDeath::ExitState()
{
}
