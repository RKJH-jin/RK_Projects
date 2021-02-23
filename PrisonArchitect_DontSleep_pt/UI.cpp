#include "stdafx.h"
#include "UI.h"
#include "Button.h"
#include "AllComponents.h"

UI::UI()
{
}

UI::~UI()
{

}

void UI::update()
{

}

void UI::release()
{
}

void UI::render()
{

}

/*=======================================================

						Window UI

=======================================================*/

WindowUI::WindowUI(Vector2 pos, Vector2 size, float scale) : UI()
{
	_pos = pos;
	_size = size;
	_scale = scale;
	_rc = FloatRect(_pos, _size, Pivot::Center);

	isActive = false;
	isRender = false;
}

WindowUI::~WindowUI()
{

}

void WindowUI::release()
{
	for (int i = 0; i < _vButton.size(); ++i)
	{
		SAFE_DELETE(_vButton[i]);
	}
}

void WindowUI::update()
{
}

void WindowUI::render()
{
	if (isRender)
	{
		D2DRenderer::GetInstance()->FillRectangle(_rc, D2D1::ColorF::Gray, 0.8f);
		D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 2.0f);
		for (int i = 0; i < _vButton.size(); ++i)
		{
			_vButton[i]->render();
		}
	}
}

void WindowUI::addObjectButtonUI(string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame)
{
	Button* bt = new Button(strName, key, pos, rcSize, imgSize, img, frame);
	_vButton.push_back(bt);
}


/*=======================================================

					Bar Button UI

=======================================================*/
BarButtonUI::BarButtonUI(string strName, Vector2 pos, float scale, Image* img)
{
    _button = new Button(strName, pos, scale, img);

    isActive = false;
    isRender = false;
}

BarButtonUI::BarButtonUI(string strName, Vector2 pos, float scale, Image* img, int frameX, int frameY) : UI()
{
	_button = new Button(strName, pos, scale, img, frameX, frameY);
	
	SetName(strName);
	SetDescription(strName + "버튼입니다.");

	isActive = false;
	isRender = false;
}

BarButtonUI::~BarButtonUI()
{
}

void BarButtonUI::release()
{
	SAFE_DELETE(_button);
}

void BarButtonUI::update()
{
	if (isActive) _windowUI->setIsRender(true);
	else _windowUI->setIsRender(false);
}

void BarButtonUI::render()
{
	if (isRender) _button->render();
}

/*=======================================================

                        Clock UI

=======================================================*/
ClockUI::ClockUI(Vector2 pos, float scale, Vector2 backSize)
{
    _pos = pos;
    _scale = scale;
    _backGroundSize = backSize;

    _rc = FloatRect(_pos, _backGroundSize, Pivot::Center);
	
    _clockImg = IMAGEMANAGER->FindImage("clock");
    _hourHand = IMAGEMANAGER->FindImage("clockHands");
    _minHand = IMAGEMANAGER->FindImage("clockHands");

	GetComponent<TransformC>()->SetPosition(pos);
	GetComponent<TransformC>()->SetSize(_clockImg->GetFrameSize());
	GetComponent<TransformC>()->SetRect();
	
	_name = "시계";
}

ClockUI::~ClockUI()
{
}

void ClockUI::release()
{
}

void ClockUI::update()
{
	_description = ("시간 : "+ to_string(DATAMANAGER->GetInfo().time.hour) + "시 " + to_string(DATAMANAGER->GetInfo().time.minute) + "분 " + to_string(DATAMANAGER->GetInfo().time.second) + "초");

}

void ClockUI::render()
{
    D2DRenderer::GetInstance()->FillRectangle(_rc, D2D1::ColorF::Gray, 0.6f);
    _clockImg->SetScale(_scale);
    _clockImg->Render(_pos);

    _hourHand->SetScale(_scale);
    _hourAngle = ((float)360 / (float)12) * (float)DATAMANAGER->GetInfo().time.hour + ((float)360 / (float)720) * (float)DATAMANAGER->GetInfo().time.minute;
    _hourHand->SetAngle(_hourAngle);
    _hourHand->FrameRender(_pos, 1, 0);

    _minHand->SetScale(_scale);
    _minAngle = ((float)360 / (float)60) * (float)DATAMANAGER->GetInfo().time.minute + ((float)360 / (float)3600) * (float)DATAMANAGER->GetInfo().time.second;
    _minHand->SetAngle(_minAngle);
    _minHand->FrameRender(_pos, 0, 0);
}

/*=======================================================

                     PlayButton UI

=======================================================*/
PlayButtonUI::PlayButtonUI(string strName, Vector2 pos, Vector2 size, float scale, Image* img)
{
   _button = new Button(strName, pos, size, scale, img);
}

PlayButtonUI::~PlayButtonUI()
{
}

void PlayButtonUI::release()
{
}

void PlayButtonUI::update()
{
}

void PlayButtonUI::render()
{
    _button->render();
}

void DescriptionUI::release()
{
}

void DescriptionUI::update()
{
}

void DescriptionUI::render()
{
	if (!_object) return;

	FloatRect areaRc = FloatRect(_ptMouse, Vector2(300, 100), Pivot::LeftTop);
	_D2DRenderer->FillRectangle(areaRc, D2D1::ColorF::DeepSkyBlue, 0.5f);

	_D2DRenderer->RenderText(_ptMouse.x, _ptMouse.y, TextC::ConvertStringToWstring(_object->GetName()), 20, D2DRenderer::DefaultBrush::Yellow, DWRITE_TEXT_ALIGNMENT_LEADING);
	_D2DRenderer->RenderText(_ptMouse.x, _ptMouse.y + 30, TextC::ConvertStringToWstring(_object->GetDescription()), 12, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING);
}

InfoUI::InfoUI()
{
	_transform = AddComponent<TransformC>();
	_transform->SetPosition(Vector2(WINSIZEX-200, WINSIZEY/2));
	AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("letterBlank"));

	/*_closeButton = new Button;
	_closeButton->SetParent(this);
	_closeButton->GetTransform()->SetPosition(Vector2(WINSIZEX - 100, 100));
	_closeButton->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("time_play0"));
	_closeButton->GetTransform()->SetRect();*/
}

void InfoUI::release()
{
}

void InfoUI::update()
{
}
void InfoUI::render()
{
	if (!GetActive()) return;

	GetComponent<ImageC>()->GetImage()->SetScale(0.8f);
	GameObject::Render();
	if (_ui) _ui->render();
	
	//_D2DRenderer->FillRectangle(_closeButton->GetTransform()->GetFloatRect(), D2D1::ColorF::Yellow, 0.7f);

}

void InfoUI::MouseEnter()
{
}

void InfoUI::MouseStay()
{
}

void InfoUI::MouseExit()
{
}

void InfoUI::SetUI(UI * go)
{
	_ui = go;
	_ui->SetParent(this);
	AddChild(go);
}

PrisonInfoUI::PrisonInfoUI(GameObject * prisoner)
{
	_prisoner = prisoner;
	SetName(prisoner->GetName());
}

void PrisonInfoUI::release()
{
}

void PrisonInfoUI::update()
{
}

void PrisonInfoUI::render()
{
	if (GetParent())
	{
		_D2DRenderer->RenderText(GetParent()->GetTransform()->GetPosition().x - 200, GetParent()->GetTransform()->GetPosition().y - 200, TextC::ConvertStringToWstring(_prisoner->GetName()), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING);
		_D2DRenderer->RenderText(GetParent()->GetTransform()->GetPosition().x - 200, GetParent()->GetTransform()->GetPosition().y, TextC::ConvertStringToWstring(_prisoner->GetDescription()), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING);
	}
}
