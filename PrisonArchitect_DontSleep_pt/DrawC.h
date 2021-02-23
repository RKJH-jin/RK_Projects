#pragma once
#include "Component.h"

class TransformC;

class DrawC : public Component
{
protected:
	TransformC* _transform;		//트랜스폼
	Camera* _camera;			//카메라
	float _alpha;

public:
	DrawC() {}
	~DrawC() {}

	virtual void Awake() override;

	void SetCamera(Camera* camera) { _camera = camera; }

	void SetAlpha(float alpha) { _alpha = alpha; }
};

