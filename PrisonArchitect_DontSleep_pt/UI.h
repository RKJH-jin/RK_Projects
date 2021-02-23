#pragma once
class Button;
#include "GameObject.h"

class UI : public GameObject
{
protected:

	typedef vector<Button*>				vButton;
	typedef vector<Button*>::iterator	viButton;

	vButton		_vButton;
	viButton	_viButton;


	bool isActive;
	bool isRender;

public:
	UI();
	~UI();

	virtual void release();
	virtual void update();
	virtual void render();

	vButton GetvButton() { return _vButton; }


	bool getIsActive() { return isActive; }
	bool getIsRender() { return isRender; }

	// SETTER
	void setIsActive(bool active) { isActive = active; }
	void setIsRender(bool render) { isRender = render; }
};



/*=======================================================

						Window UI

=======================================================*/
class WindowUI : public UI
{
private:
	Vector2 _pos;
	Vector2 _size;

	float _alpha;
	float _scale;
	FloatRect _rc;

public:
	WindowUI(Vector2 pos, Vector2 size, float scale);
	~WindowUI();

	virtual void release();
	virtual void update();
	virtual void render();

	void addObjectButtonUI(string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame);

    // GETTER
	vector<Button*> getVButton() { return _vButton; }
    FloatRect* getRect() { return &_rc; }
};

/*=======================================================

					Bar Button UI

=======================================================*/
class BarButtonUI : public UI
{
private:
	Button* _button;
	WindowUI* _windowUI;
public:
    BarButtonUI(string strName, Vector2 pos, float scale, Image* img);
	BarButtonUI(string strName, Vector2 pos, float scale, Image * img, int frameX, int frameY);
	~BarButtonUI();

	virtual void release();
	virtual void update();
	virtual void render();

	
    // GETTER
    Button* getButton() { return _button; }
    bool getIsActive() { return isActive; }
    WindowUI* getWindowUI() { return _windowUI; }

	void setLinkWindowUI(WindowUI* window) { _windowUI = window; }
};

/*=======================================================

                        Clock UI

=======================================================*/
class ClockUI : public UI
{
private:
    Vector2 _pos;
    float _scale;
    Vector2 _backGroundSize;
    
    FloatRect _rc;

    Image* _clockImg;
    Image* _hourHand;
    Image* _minHand;

    float _hourAngle;
    float _minAngle;

public:
    ClockUI(Vector2 pos, float scale, Vector2 backSize);
    ~ClockUI();

    virtual void release();
    virtual void update();
    virtual void render();

    //GETTER
    FloatRect& GetRect() { return _rc; }

    //SETTER
    void SetPosition(Vector2 pos) { _pos = pos; }

};
/*=======================================================

                     PlayButton UI

=======================================================*/
class PlayButtonUI : public UI
{
private:
    Button* _button;

public:
    PlayButtonUI(string strName, Vector2 pos, Vector2 size, float scale, Image* img);
    ~PlayButtonUI();

    virtual void release();
    virtual void update();
    virtual void render();

    // GETTER
    Button* GetButton() { return _button; }

};

/*=======================================================

					Info UI

=======================================================*/
class InfoUI : public UI
{
private:
	UI* _ui;

public:
	InfoUI();
	~InfoUI() {};

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void MouseEnter();
	virtual void MouseStay();
	virtual void MouseExit();

	void SetUI(UI* ui);
};


enum class PRISONINFOUIPAGE
{
	약력, 성격, 경험, 등급, END
};

class PrisonInfoUI : public UI
{
private:
	map<string, Button*> _mbutton;
	PRISONINFOUIPAGE _page;
	GameObject* _prisoner;
		
public:
	PrisonInfoUI(GameObject* prisoner);
	~PrisonInfoUI() {};

	virtual void release();
	virtual void update();
	virtual void render();

	// GETTER
};



/*=======================================================

					 Description UI

=======================================================*/

class DescriptionUI : public UI
{
private:
	GameObject* _object;

public:

	virtual void release();
	virtual void update();
	virtual void render();

	void SetGameObject(GameObject* go) { _object = go; }
	GameObject* GetGameObject() { return _object; }
};


