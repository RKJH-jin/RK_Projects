#include "stdafx.h"
#include "BTCreateStuff.h"
#include "Character.h"
#include "StuffObject.h"
#include "MapToolScene.h"
#include "Character.h"
HRESULT BTCreateStuff::init(Character * character)
{
	_character = character;
	return S_OK;
}

void BTCreateStuff::setStuff(STUFFTTYPE stuff)
{
	_stuffType = stuff;

}

STATE BTCreateStuff::invoke()
{
	{
		StuffObject* tempS = new StuffObject(_stuffType);
		tempS->GetTransform()->SetPosition(_character->GetTransform()->GetPosition());
		DATAMANAGER->GetMapToolScene()->GetMapM()->GetVStuffObj().push_back(tempS);

	}


	return STATE::SUCCESS;
}
