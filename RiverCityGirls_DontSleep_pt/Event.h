#pragma once

class UI;
class LocationLock;
class Video;
enum class VIDEOTYPE;

enum class DIALOGLIST;
enum class DIRECTION;
class Player;


/*====================================================================
	이벤트 클래스입니다. 다양한 이벤트에게 상속하고 있습니다.
====================================================================*/
class Event
{
public:
	bool _isMovie;
	bool _isCameraMove;
	Player* _player;

public:
	virtual void enter(bool playerControl);
	virtual bool update() = 0;
	virtual void exit();
	virtual void render(HDC hdc) {}

	bool isMovie() { return _isMovie; }
	void setLinkPlyaer(Player* player) { _player = player; }
};

/*====================================================================
	카메라 이동과 배율 조정
====================================================================*/
class cameraMove : public Event
{
private:
	vector3 _goal;
	float _moveSpeed;
	float _mag;
	float _magSpeed;

public:
	cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed);
	~cameraMove() {}

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};


/*====================================================================
	동영상 재생
====================================================================*/
class moviePlay : public Event
{
	VIDEOTYPE _videoName;
	Video* _video;

public:
	moviePlay(VIDEOTYPE fileName);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	대화
====================================================================*/
class dialogue : public Event
{
	enum class DIALOGSTATE
	{
		ENTER,
		UPDATE,
		EXIT,
	};

	struct tagImg
	{
		image* _portrait;		//캐릭터 초상화
		image* _name;			//캐릭터 이름
		vector3 _pos;			//위치
		vector3 _goal;			//목표 위치
		DIRECTION _dest;		//방향
		Interpolation _inter;	//선형 보간
	};

private:
	DIALOGSTATE		_state;			//상태

	bool			_isRender;		//그리는지
	image*			_diaWindow;		//대사창
	vector<string>	_vScript;		//스크립트
	int				_scriptIndex;	//스크립트 인덱스
	
	string			_txt;			//텍스트
	int				_txtIndex;		//텍스트 인덱스
	tagImg			_img;			//대화 이미지

	DIALOGLIST		_list;			//대화 리스트
	
	float			_dialogTime;	//대사 시간
	bool			_autoSkip;		//자동 넘김

	float			_txtTime;		//텍스트 시간
	float			_txtInterval;	//텍스트인터벌
	int				_txtPos;		//텍스트 위치

public:

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGLIST file);
	~dialogue() {}

	void render(HDC hdc);
};


/*====================================================================
	대기
====================================================================*/
class waitForSec : public Event
{
private:
	float _endTime;

public:
	waitForSec(float sec);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	지역락
====================================================================*/
class locationLock : public Event
{
private:
	bool _isStart;
	bool _isEnd;
 

	LocationLock* _event;
public:
	locationLock();

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

};

/*====================================================================
	하트
====================================================================*/
class heart : public Event
{
	
private:
	image* _img;
	float _ratio;
	float _timer;
	bool _isReverse;

public:
	heart(bool reverse);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	void render(HDC hdc);
};