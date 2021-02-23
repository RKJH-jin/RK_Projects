#pragma once
#include "DrawC.h"
class RectC : public DrawC
{
private:
	bool _isLine;
	D2D1::ColorF::Enum _color;
	float _width = 1.0f;
public:

	virtual void Awake() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetIsLine(bool line) { _isLine = line; }
	void SetColor(const  D2D1::ColorF::Enum& color) { _color = color; }
	void SetWidth(float width) { _width = width; }


};

