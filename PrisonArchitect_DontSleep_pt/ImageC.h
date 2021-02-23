#pragma once
#include "DrawC.h"
class ImageC : public DrawC
{
private:
	Image* _img;
	Vector2 _frame;
public:

	virtual void Awake() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetImage(Image* img);
	void SetFrame(Vector2 frame) { _frame = frame; }
	void SetReverese(bool x, bool y) { _img->SetReverseX(x), _img->SetReverseX(y); }

	Image* GetImage() { return _img; }
};

