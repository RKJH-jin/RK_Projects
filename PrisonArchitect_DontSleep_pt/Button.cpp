#include "stdafx.h"
#include "Button.h"

Button::Button(string strName, Vector2 pos, Vector2 size, float scale, Image* img)
{
    _name = strName;
    _img = img;
    _scale = scale;
    _img->SetScale(_scale);
    _pos = pos;
    _rcSize = size;
    _imgSize = size;
    _rc = FloatRect(_pos, _rcSize, Pivot::Center);

	SetDescription(_name + "입니다");

    _frameX = 0;
    _frameY = 0;
}

Button::Button(string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame)
{
	_name = strName;
	_key = key;
	_img = img;
	_scale = 0.6f;
	_img->SetScale(_scale);
	_pos = pos;
    _rcSize = rcSize;
	_imgSize = imgSize;
	_rc = FloatRect(_pos, _rcSize, Pivot::Center);

	SetDescription(_name + " 생성 버튼입니다.\n클릭하고 위치를 선택하면 설치됩니다.");

	_frameX = frame.x;
	_frameY = frame.y;
}

Button::Button(string strName, Vector2 pos, float scale, Image * img)
{
	_name = strName;
	_img = img;
	_scale = scale;
	_img->SetScale(_scale);
	_pos = pos;
	_imgSize = _img->GetFrameSize();
	_rc = FloatRect(_pos, _imgSize * _scale * _scale, Pivot::Center);

	SetDescription(_name + " 버튼입니다./n클릭 시 설치 카탈로그를 확인할 수 있습니다.");

	_frameX = 0;
	_frameY = 0;
}

Button::Button(string strName, Vector2 pos, float scale, Image* img, int frameX, int frameY)
{
	_name = strName;
	_img = img;
	_scale = scale;
	_img->SetScale(_scale);
	_pos = pos;
	_imgSize = _img->GetFrameSize();
	_rc = FloatRect(_pos, _imgSize * _scale * _scale, Pivot::Center);

	SetName(_name);
	SetDescription(_name + "버튼입니다");

	_frameX = frameX;
	_frameY = frameY;
}

Button::~Button()
{
}

void Button::update()
{
	if (!_isActive) return;

	if (_rc.PtInRect(_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if(fn) invokeFunction();
		}
	}
}

void Button::render()
{
	if (!_isRender) return;

#if true // Debug

	//디버깅용 렉트 렌더
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug
	_img->SetScale(_scale);
	_img->SetSize(_imgSize);
	_img->SourceRender(_pos, _imgSize, Vector2(_frameX, _frameY));
}

Button * Button::MouseEnter()
{
	return nullptr;
}

Button * Button::MouseStay()
{
	return nullptr;
}

Button * Button::MouseExit()
{
	return nullptr;
}
