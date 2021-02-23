#include "stdafx.h"
#include "VolumeUI.h"
#include "Button.h"

VolumeUI::VolumeUI()
{
	_maxWidth = 300;
	_startPosX = 120;
	_barHeight = 25;

	_transform->SetPosition(Vector2(250, 550));
	_transform->SetSize(Vector2(400, 200));
	_transform->SetRect();

	AddComponent<RectC>()->SetAlpha(0.5f);
	GetComponent<RectC>()->SetColor(D2D1::ColorF::Aquamarine);

	//MASTER
	_masterRc = RectMakePivot(Vector2(_startPosX, 520.0f), Vector2(_maxWidth, _barHeight), Pivot::LeftTop);
	_masterBar = RectMakePivot(Vector2(_startPosX, 520.0f), Vector2(SOUNDMANAGER->GetMasterVolume()*_maxWidth, _barHeight), Pivot::LeftTop);

	//BGM
	_bgmRc = RectMakePivot(Vector2(_startPosX, 560.0f), Vector2(_maxWidth, _barHeight), Pivot::LeftTop);
	_bgmBar = RectMakePivot(Vector2(_startPosX, 560.0f), Vector2(SOUNDMANAGER->GetBGMVolume()*_maxWidth, _barHeight), Pivot::LeftTop);

	//SFX
	_sfxRc = RectMakePivot(Vector2(_startPosX, 600.0f), Vector2(_maxWidth, _barHeight), Pivot::LeftTop);
	_sfxBar = RectMakePivot(Vector2(_startPosX, 600.0f), Vector2(SOUNDMANAGER->GETSFXVolume()*_maxWidth, _barHeight), Pivot::LeftTop);

}

void VolumeUI::update()
{
	GameObject::Update();

	if (_masterRc.PtInRect(_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->SetMasterVolume((_ptMouse.x - _startPosX) / _maxWidth);
	}

	if (_bgmRc.PtInRect(_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->SetBGMVolume((_ptMouse.x - _startPosX) / _maxWidth);
	}

	if (_sfxRc.PtInRect(_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->SetSFXVolume((_ptMouse.x - _startPosX) / _maxWidth);
	}
}

void VolumeUI::render()
{
	GameObject::Render();

	_masterBar = RectMakePivot(Vector2(_startPosX, 520.0f), Vector2(SOUNDMANAGER->GetMasterVolume() * _maxWidth, _barHeight), Pivot::LeftTop);
	_D2DRenderer->FillRectangle(_masterBar, D2D1::ColorF::MidnightBlue, 1.0f);

	_bgmBar = RectMakePivot(Vector2(_startPosX, 560.0f), Vector2(SOUNDMANAGER->GetBGMVolume() * _maxWidth, _barHeight), Pivot::LeftTop);
	_D2DRenderer->FillRectangle(_bgmBar, D2D1::ColorF::Tomato, 1.0f);

	_sfxBar = RectMakePivot(Vector2(_startPosX, 600.0f), Vector2(SOUNDMANAGER->GETSFXVolume() * _maxWidth, _barHeight), Pivot::LeftTop);
	_D2DRenderer->FillRectangle(_sfxBar, D2D1::ColorF::Tomato, 1.0f);

	_D2DRenderer->RenderText(180, 470, L"옵션", 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);
	_D2DRenderer->RenderText(65, 520, L"마스터", 15, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);
	_D2DRenderer->RenderText(65, 560, L"배경음", 15, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);
	_D2DRenderer->RenderText(65, 600, L"효과음", 15, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);

}



