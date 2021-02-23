#pragma once
#include "DrawC.h"
class TextC : public DrawC
{
private:
	string _strText;

	wstring _text;
	wstring _fontName;

	float _fontSize = 10;
	D2DRenderer::DefaultBrush _fontColor = D2DRenderer::DefaultBrush::White;

	ANCHORPIVOT _pivot;
	ID2D1SolidColorBrush* _color;
	IDWriteTextLayout* _layout;

public:
	virtual void Awake() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


	void SetText(float fontSize, D2DRenderer::DefaultBrush color = D2DRenderer::DefaultBrush::White, wstring fontName = L"¸¼Àº°íµñ");

	void ChangeText(string text);

	void SetAnchorPoint(ANCHORPIVOT _pivot);


	static wstring ConvertStringToWstring(const string &str);
};

