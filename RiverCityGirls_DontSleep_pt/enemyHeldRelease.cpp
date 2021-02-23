#include "stdafx.h"
#include "enemyHeldRelease.h"
#include "Enemy.h"

void enemyHeldRelease::EnterState()
{
	_thisEn->SetImage();
}

void enemyHeldRelease::UpdateState()
{
}

void enemyHeldRelease::ExitState()
{
}
