#include "stdafx.h"
#include "PrisonerSleep.h"

HRESULT PrisonerSleep::init(Character * character)
{
    _character = character;
    return S_OK;
}

STATE PrisonerSleep::invoke()
{

    return STATE::SUCCESS;
}
