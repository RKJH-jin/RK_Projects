#pragma once
#include "gameNode.h"
#include "csv.h"
class playGround : public gameNode
{
public:
	csv _csv;

	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void AddSource();
	void AddImage();
	void AddSound();
};

