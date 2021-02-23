#include "stdafx.h"
#include "RectC.h"
#include "TransformC.h"
void RectC::Awake()
{
	DrawC::Awake();
	_isLine = false;
	_color = D2D1::ColorF::DarkRed;
}

void RectC::Init()
{
}

void RectC::Update()
{
}

void RectC::Render()
{
	if (_transform->GetFloatRect().GetSize().x > 1 && _transform->GetFloatRect().GetSize().y > 1)
	{
		if (_isLine)
		{
			_D2DRenderer->FillRectangle(_transform->GetFloatRect(), _color, _alpha);

		}
		else
		{
			_D2DRenderer->FillRectangle(_transform->GetFloatRect(), _color, _alpha);
		}
	}

}

