#include "stdafx.h"
#include "enemyLadder.h"
#include "Enemy.h"

void enemyLadder::EnterState()
{
	_thisEn->SetImage();
}

void enemyLadder::UpdateState()
{
	/*
	_thisEn->setDest(DIRECTION::NONE);
	*/
}

void enemyLadder::ExitState()
{
}
