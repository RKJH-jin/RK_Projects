#include "stdafx.h"

#include "Boss.h"
#include "bossMeteor.h"
#include "bossAttacked.h"
#include "bossBlock.h"
#include "bossDashAttack.h"
#include "bossDeath.h"
#include "bossDown.h"
#include "bossElbowAttack.h"
#include "bossGroggy.h"
#include "bossHowling.h"
#include "bossIdle.h"
#include "bossWait.h"
#include "bossMove.h"
#include "bossPhase2.h"
#include "bossSlapAttack.h"
#include "bossSmashAttack.h"
#include "bossStandAttack.h"
#include "IBossState.h"

#include "CollisionManager.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

HRESULT Boss::init()
{
	_player = _stageM->getPlayer();
	_objectM = _stageM->getStage()->getObjectM();

	_obj.init(OBJECT_GROUP::BOSS, IMG_M->findImage("Bs_idle"), _obj.pos);	
	_obj.imgIndex = { 0,0 };
	
	_frameTimer = TIME_M->getWorldTime();
	
	_info.dest = DIRECTION::LEFT;		//방향
	_info.gravity = 0;					//중력
	_info.jumpPower = 0;				//점프력
	_info.baseSpeed = _info.speed = 3;	//속도
	_info.frameTimer = 0;				//프레임시간 타이머

	_info.hp = _info.maxHp = 1000;		//체력
	_info.attack = 10;					//공격력
	_groggyCount = 0;
	_phaseCount = 0;

	_info.isAttack = _info.isSky = _info.isDead = _info.isFriend = false;
	_info.hasWeapon = false;			//무기들었니	

	//상태패턴 등록
	_idle = new bossIdle;
	_wait = new bossWait;
	_move = new bossMove;

	_block = new bossBlock;
	_attacked = new bossAttacked;
	_groggy = new bossGroggy;
	_down = new bossDown;
	_death = new bossDeath;
	_phase = new bossPhase2;

	_howling = new bossHowling;
	_meteor = new bossMeteor;
	_dash = new bossDashAttack;
	_elbow = new bossElbowAttack;
	_slap = new bossSlapAttack;
	_smash = new bossSmashAttack;
	_standattack = new bossStandAttack;
	
	_info.isAttack = false;	
	_isPhase = false;

	_BState = NULL;

	SetState(BS_STATE::IDLE);


	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;
	_BState->UpdateState();	
	_obj.update();
	_obj.shadowUpdate();
	frameUpdate();		
	_stageM->getColM()->bossDestructObject(this);

	//cout << _player->getInfo().hp << endl;
}

void Boss::render()
{		
	if (KEY_M->isToggleKey(VK_SHIFT) && _info.isAttack) Rectangle(getMapDC(), _info.rcAttack);	
}

void Boss::SetState(BS_STATE state)
{
	if (_BState != NULL && _state == state) return; //같은 상태면 변경하지 않는다.
	_state = state;

	//상태를 빠져나온다
	if (_BState != NULL)_BState->ExitState();

	//상태를 변경한다
	switch (_state)
	{
		//기본동작
	case BS_STATE::IDLE:	    _BState = _idle;		 break;
	case BS_STATE::WAIT:	    _BState = _wait;		 break;
	case BS_STATE::MOVE:	    _BState = _move;		 break;
	
		//가드 및 상태변화
	case BS_STATE::BLOCK:       _BState = _block;		 break;
	case BS_STATE::ATTACKED:    _BState = _attacked;	 break;
	case BS_STATE::GROGGY:      _BState = _groggy;		 break;	
	case BS_STATE::DOWN:	    _BState = _down;		 break;
	case BS_STATE::DEATH:	    _BState = _death;		 break;
	case BS_STATE::PHASE:		_BState = _phase;	     break;

		// 공격
	case BS_STATE::HOWLING:		_BState = _howling;		 break;
	case BS_STATE::METEOR:		_BState = _meteor;		 break;
	case BS_STATE::DASH:		_BState = _dash;		 break;
	case BS_STATE::ELBOW:		_BState = _elbow;		 break;
	case BS_STATE::SLAP:		_BState = _slap;		 break;
	case BS_STATE::SMASH:		_BState = _smash;		 break;
	case BS_STATE::STANDATTACK: _BState = _standattack;  break;
	default: break;
	}

	//상태 링크
	_BState->LinkBSAddress(this);
	_BState->EnterState();
}

void Boss::SetDest(DIRECTION dest)
{
	if (_info.dest == dest)return; //같은 상태면 변경하지 않는다.
	_info.dest = dest;
}

void Boss::frameUpdate()
{
	if (TIME_M->getWorldTime() - _frameTimer > 0.1f)
	{
		_frameTimer = TIME_M->getWorldTime();

		switch (_state)
		{
		case BS_STATE::IDLE:		
		case BS_STATE::DEATH:
		case BS_STATE::MOVE:
		case BS_STATE::WAIT:
		case BS_STATE::GROGGY:	
		case BS_STATE::DOWN:
		case BS_STATE::METEORDOWN:
		playFrame(0);
		break;

		case BS_STATE::METEOR:						
		playFrame(1);
		break;

		case BS_STATE::DASH:
		case BS_STATE::BLOCK:
		case BS_STATE::SMASH:
		case BS_STATE::SLAP:
		case BS_STATE::ELBOW:
		case BS_STATE::PHASE:
		case BS_STATE::HOWLING:
		case BS_STATE::ATTACKED:
		case BS_STATE::STANDATTACK:		
		playFrame(-1);
		break;

		default:
		break;
		}
	}
}

void Boss::playFrame(int count)
{
	switch (count)
	{
	case -1:	//한 번 재생 후 기본				
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = 0;
			SetState(BS_STATE::IDLE);			
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
			SetState(BS_STATE::IDLE);			
		}
		break;

	case 1:		//한 번만 재생
	
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX()) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0) _obj.imgIndex.x = 0;
		break;

	case 0:		//무한 재생
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX()) _obj.imgIndex.x = 0;
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		break;
	}
	
	switch (_info.dest)
	{
	case DIRECTION::LEFT: 
		_obj.imgIndex.x--;
		_obj.imgIndex.y = 0;
		break;
		
	case DIRECTION::RIGHT: 
		++_obj.imgIndex.x;
		_obj.imgIndex.y = 1;
		break;
	}
}

void Boss::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);	
}

