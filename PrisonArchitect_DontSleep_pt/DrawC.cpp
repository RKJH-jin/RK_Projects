#include "stdafx.h"
#include "DrawC.h"

void DrawC::Awake()
{
	_alpha = 1.0f;
	this->_transform = _object->GetTransform();
}

