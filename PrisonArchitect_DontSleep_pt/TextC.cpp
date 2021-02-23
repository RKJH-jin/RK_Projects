#include "stdafx.h"
#include "TextC.h"
#include "TransformC.h"
void TextC::Awake()
{
	DrawC::Awake();
}

void TextC::Init()
{
}

void TextC::Update()
{
}

void TextC::Render()
{
	if (_camera)
	{
		_D2DRenderer->RenderText(_transform->GetFloatRect().left + _fontSize, _transform->GetFloatRect().top, _text, _fontSize * _camera->_zoom, _fontColor, DWRITE_TEXT_ALIGNMENT_LEADING);
	}
	else
	{
		_D2DRenderer->RenderText(_transform->GetFloatRect().left + _fontSize, _transform->GetFloatRect().top, _text, _fontSize , _fontColor, DWRITE_TEXT_ALIGNMENT_LEADING);
	}
}

void TextC::SetText(float fontSize, D2DRenderer::DefaultBrush color, wstring fontName)
{
	//_D2DRenderer->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &_color);
	_fontColor = color;
	_fontSize = fontSize;
}

void TextC::ChangeText(string text)
{
	_strText = text;
	_text = ConvertStringToWstring(_strText);
}

void TextC::SetAnchorPoint(ANCHORPIVOT _pivot)
{

}

wstring TextC::ConvertStringToWstring(const string & str)
{
	if (str.empty())
	{
		return std::wstring();
	}
	int num_chars = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), NULL, 0);
	wstring wstrTo;
	if (num_chars)
	{
		wstrTo.resize(num_chars);
		if (MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), &wstrTo[0], num_chars))
		{
			return wstrTo;
		}
	}
	return wstring();
}
