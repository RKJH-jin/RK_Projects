#include "stdafx.h"
#include "enemyLadderTransition.h"
#include "Enemy.h"

void enemyLadderTransition::EnterState()
{
	_thisEn->SetImage();
}

void enemyLadderTransition::UpdateState()
{
	//_thisEn->setDest(DIRECTION::NONE);
}

void enemyLadderTransition::ExitState()
{
}
