#include "stdafx.h"
#include "Select.h"

Button::Button(image* none, image * down, image * up, vector3 pos, CALLBACKFUCN fp, int param)
{
	funcp = fp;
	_param = param;
	_none = none; _down = down; _up = up;
	_pos = pos;

	init();
}

Button::Button(image * down, image * up, vector3 pos, CALLBACKFUCN fp, int param)
{
	funcp = fp;
	_param = param;
	_none = _down = down; _up = up;
	_pos = pos;
	init();
}

HRESULT Button::init()
{
	_rc = RectMakeCenter(_pos.x, _pos.y, _down->getFrameWidth()*0.8, _down->getFrameHeight()*0.8);
	_state = BUTTONSTATE::NONE;
	_isSelect = false;
	_inter = new Interpolation;
	

	return S_OK;
}

void Button::release()
{

}

void Button::update()
{
}

void Button::render(HDC hdc)
{
	switch (_state)
	{
	case BUTTONSTATE::NONE:
		_none->render(hdc, _pos.x, _pos.y);
		break;
	case BUTTONSTATE::DOWN:
		_down->render(hdc, _pos.x, _pos.y);
	case BUTTONSTATE::UP:
		_up->render(hdc, _pos.x, _pos.y);
		break;
	default:
		break;
	}
}


void Select::release()
{
	if (_vButton.empty()) return;
	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i]->release();
		SAFE_DELETE(_vButton[i]);
	}
	delete this;
}

bool Select::update()
{
	/*====================================================================
		벡터가 비었을 경우 리턴하며, index에 해당하는 버튼을 DOWN 상태로 둔다.
	====================================================================*/
	if (_vButton.empty()) return false;

	for (int i = 0; i < _vButton.size(); i++)
	{
		if (i == _index)
		{
			if(_vButton[i]->_state != BUTTONSTATE::UP)
			_vButton[i]->_state = BUTTONSTATE::DOWN;
		}
		else _vButton[i]->_state = BUTTONSTATE::NONE;
	}

	/*====================================================================
					키보드 조작 (마우스 조작이 아닐 시에만 작동)
	====================================================================*/
	for (int i = 0; i < _vButton.size(); i++)
	{
		if (KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE))
		{
			SOUND_M->playSFX("menu_confirm");

			_vButton[_index]->_state = BUTTONSTATE::UP;
			_selectTime = TIME_M->getWorldTime();
			_vButton[_index]->_isSelect = true;
			//if (_vButton[_index]->funcp) _vButton[_index]->funcp(_vButton[_index]->_param);
			if (_vButton[_index]->funcp) _vButton[_index]->funcp();
		}

		if (!PtInRect(&_vButton[i]->_rc, _ptMouse))
		{
			if (KEY_M->isOnceKeyDown(VK_DOWN) || KEY_M->isOnceKeyDown(VK_RIGHT))
			{
				SOUND_M->playSFX("menu_cursor");

				_index++;
				if (_index >= _vButton.size()) _index = 0;
			}
			if (KEY_M->isOnceKeyDown(VK_UP) || KEY_M->isOnceKeyDown(VK_LEFT))
			{
				SOUND_M->playSFX("menu_cursor");

				_index--;
				if (_index < 0) _index = _vButton.size() - 1;
			}
		}
	}

	/*====================================================================
					마우스 조작 (마우스 롤오버와 클릭으로 작동)
	====================================================================*/
	for (int i = 0; i < _vButton.size(); i++)
	{
		if (PtInRect(&_vButton[i]->_rc, _ptMouse))
		{
			_index = i;
			_vButton[i]->_state = BUTTONSTATE::DOWN;

			if (KEY_M->isOnceKeyUp(VK_LBUTTON))
			{
				SOUND_M->playSFX("menu_confirm");
				_vButton[i]->_state = BUTTONSTATE::UP;
				_vButton[i]->_isSelect = true;
				_selectTime = TIME_M->getWorldTime();
				if (_vButton[i]->funcp) _vButton[i]->funcp();
			}
		}
	}
	/*====================================================================
							버튼 선택 모션과 메모리 해제
	====================================================================*/
	for (int i = 0; i < _vButton.size(); i++)
	{
		if (_vButton[i]->_isSelect)
		{
			_vButton[i]->_inter->moveTo(&_vButton[i]->_pos, _vButton[i]->_pos.x - 10, _vButton[i]->_pos.y, 0.15f);
			_vButton[i]->_inter->update();
			_vButton[i]->_inter->moveTo(&_vButton[i]->_pos, _vButton[i]->_pos.x + 40, _vButton[i]->_pos.y, 0.2f);
			_vButton[i]->_inter->update();

			if (TIME_M->getWorldTime() - _selectTime > 0.4f)
			{
				this->release();
				return true;
			}
		}
	}
	return false;
}

/*====================================================================
			버튼을 그리고, TAB 토글 시 디버깅 용 렉트를 그린다.
====================================================================*/
void Select::render(HDC hdc)
{
	if (_vButton.empty()) return;

	for (int i = 0; i < _vButton.size(); i++)
	{
		if (KEY_M->isToggleKey(VK_SHIFT)) Rectangle(hdc, _vButton[i]->_rc);
		_vButton[i]->render(hdc);
	}
}

/*====================================================================
						SELECT에 버튼을 추가한다.
====================================================================*/
void Select::addButton(Button button)
{
	Button* _button = new Button(button);
	_vButton.push_back(_button);
}
