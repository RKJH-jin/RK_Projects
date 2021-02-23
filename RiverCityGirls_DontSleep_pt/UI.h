#pragma once

class Player;
enum class UITYPE;
/*====================================================================
						단일 이미지 UI
====================================================================*/
class UI
{
public:
	UITYPE _type;
	image* _img;

	vector3* _pos;
	vector3 _goal;
	float _speed;
	RECT _rc;
	Player* _player;

	bool _isActive;
	bool _isMove;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setActive(bool active) { _isActive = active; }
	void setPos(vector3* pos) { _pos = pos; }
	void setLinkPlayer(Player* player) { _player = player; }


};

/*====================================================================
						Progress Bar UI
====================================================================*/
class Bar : public UI
{
private:
	image* _back;
	image* _front;
	float _ratio;
	int* _current, *_max;

public:
	Bar(image* front, image* back, int* current, int* max);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

/*====================================================================
						C A L L   P H O N E
====================================================================*/
class CallPhone : public UI
{
	image* _itemImg;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void render(HDC hdc);

};

/*====================================================================
					L O C A T I O N		L O C K
====================================================================*/
class LocationLock : public UI
{
	struct tagChain
	{
		float speed;
		image* img;
		vector3 pos;
	};
private:
	bool isLockingStart;
	bool isLockingEnd;
	bool isUnlockingStart;
	bool isUnlockingEnd;
	float _chainTimer;
	float _lockTimer;
	float _lockCoolTime;

	tagChain _chainLeft;
	tagChain _chainRight;
	tagChain _chainBottom;
	tagChain _chainTop;

	image* _Lock;
	int _imgFrameX;
public:
	LocationLock();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void render(HDC hdc);

	void startLock();
	void resetFrameIdx();
	void changeLockImg1();
	void changeLockImg2();
	void startUnlock();
	void resetUI();
	bool isUnlockEnd() { return isUnlockingEnd; }
	bool isUnlockStart() { return isUnlockingStart; }
	void setUnlockEnd(bool End) {isUnlockingEnd = End;}
	bool getIsLockingEnd() { return isLockingEnd; }

};

/*====================================================================
						E N D I N G   U I
====================================================================*/
class EndingUI : public UI
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void render(HDC hdc);

};
