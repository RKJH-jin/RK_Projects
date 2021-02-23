#pragma once
#include <vector>
//typedef void(*C_FUNCTION)(int);		//함수 포인터

#include <functional>
typedef std::function<void(void)> CALLBACKFUCN;	//펑셔널

enum class BUTTONSTATE
{
	NONE, DOWN, UP
};

/*====================================================================
						버 튼
====================================================================*/
class Button
{
public:
	const char* _name;
	BUTTONSTATE _state;

	image* _none;
	image* _down;
	image* _up;

	vector3 _pos;
	RECT _rc;

	bool _isSelect;

	CALLBACKFUCN funcp;
	int _param;
	Interpolation* _inter;

public:
	Button(image* _none, image* down, image* up, vector3 pos, CALLBACKFUCN fp, int param);
	Button(image* down, image* up, vector3 pos, CALLBACKFUCN fp, int param);
	~Button() {};

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

/*====================================================================
						선 택
====================================================================*/
class Select
{
public:
	Select() { _index = 0;}
	~Select() {}

	vector<Button*> _vButton;

	int _index;
	float _selectTime;

	void release();
	bool update();
	void render(HDC hdc);

	void addButton(Button button);
	
};

