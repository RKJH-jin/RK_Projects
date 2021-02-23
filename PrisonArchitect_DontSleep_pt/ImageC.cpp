#include "stdafx.h"
#include "ImageC.h"

#include "TransformC.h"
#include "GameObject.h"

void ImageC::Awake()
{
	DrawC::Awake();
}

void ImageC::Init()
{
}

void ImageC::Update()
{
}

void ImageC::Render()
{
	if (!_img) return;

	if (_camera)
	{
		if (_img->GetIsFrameImage()) _img->FrameRender(Vector2(_transform->GetPosition().x, _transform->GetPosition().y), _frame.x, _frame.y, _camera);
		else _img->Render(Vector2(_transform->GetPosition().x, _transform->GetPosition().y), _camera);
	}
	else
	{
		if (_img->GetIsFrameImage()) _img->FrameRender(Vector2(_transform->GetPosition().x, _transform->GetPosition().y), _frame.x, _frame.y);
		else _img->Render(Vector2(_transform->GetPosition().x, _transform->GetPosition().y));
	}

}

void ImageC::SetImage(Image * img)
{
	_img = img;
	
	_transform->SetSize(Vector2(_img->GetFrameSize().x, _img->GetFrameSize().y));

}
