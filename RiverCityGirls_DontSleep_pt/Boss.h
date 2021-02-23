#pragma once
#include "Enemy.h"

class IBossState;

enum class BS_STATE : int
{
	IDLE,			//기본
	WAIT,			//대기
	MOVE,			//걷기	
	
	BLOCK,			//가드	
	ATTACKED,		//피격
	GROGGY,			//그로기		
	PHASE,			//페이즈
	DOWN,			//쓰러짐
	DEATH,			//사망

	HOWLING,		//하울링 어택
	METEOR,	
	METEORDOWN,		//메테오 어택
	DASH,			//대쉬 어택
	ELBOW,			//엘보우 어택
	SLAP,			//손바닥 어택
	SMASH,			//스매시 어택
	STANDATTACK		//기상 어택	
	
};

class Boss : public Enemy
{
private:
	//상태 클래스
	IBossState*	_BState;		//현재 상태
	IBossState*	_idle;			//기본
	IBossState*	_wait;			//대기
	IBossState*	_move;			//걷기	
	IBossState*	_block;			//막기	
	IBossState*	_attacked;		//피격
	IBossState*	_groggy;		//기절	
	IBossState* _phase;			//페이즈2
	IBossState*	_down;			//쓰러짐
	IBossState*	_death;			//사망	
	IBossState*	_howling;		//하울링 어택
	IBossState*	_meteor;		//메테오 어택
	IBossState*	_dash;			//대쉬 어택
	IBossState*	_elbow;			//엘보우 어택
	IBossState*	_slap;			//손바닥 어택
	IBossState*	_smash;			//스매시 어택
	IBossState*	_standattack;	//기상 어택
	IBossState* _meteordown;
	
	bool _isPhase;				//페이즈에 들어갔니
	int _groggyCount;			
	int _phaseCount;					

	BS_STATE _state;
	ENEMY_TYPE _ENEMY_TYPE;	
	float _frameTimer;

public:
	Boss() {};
	~Boss() {};
	virtual HRESULT init();			//초기화
	virtual void release();			//해제
	virtual void update();			//업뎃
	virtual void render();			//렌더

	//접근자===================================================
	bool getIsphase() { return _isPhase; }
	BS_STATE getState() {return _state;}
	int& getGroggyCount() { return _groggyCount; }
	int& getPhaseCount() { return _phaseCount; }
	//지정자===================================================
	void SetState(BS_STATE state);
	void SetDest(DIRECTION dest);
	void setPosition(vector3 pos) { _obj.pos = pos; }	
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setIsphase(bool isphase) { _isPhase = isphase; }

	//기능함수===================================================
	void playFrame(int count);
	void frameUpdate();	
	void ChangeImg(string imgName);						//이미지변경	
};

