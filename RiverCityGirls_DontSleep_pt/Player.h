#pragma once
#include "gameNode.h"
#include "GameObject.h"
#include "pet.h"

#define ATTACKSIZE		480			//일반공격 사이트
#define THROWSPEED		15			//일반무기 날리는 속도


//전방선언
class StageManager;
class ObjectManager;
class EnemyManager;
class IPlayerState;
class CollisionManager;
/*====================================================================
		플래이어입니다. Stage와 링크되어 있어,
		에너미 매니저, 오브젝트 매니저와 연결됩니다.
====================================================================*/
//플레이어 상태 이넘
enum class PL_STATE : int
{
	IDLE,			//기본
	WAIT,			//대기
	WALK,			//걷기
	RUN,			//달리기
	JUMP,			//점프
	STICK,			//벽잡기
	CLIMB,			//오르기
	CLIMBTOP,		//오르기끝(사다리위)
	PICK,			//줍기

	GRAB,			//잡기
	GUARD,			//가드
	ROLL,			//구르기
	HIT,			//피격
	STUN,			//기절
	STAND,			//기상
	DOWN,			//쓰러짐
	DEAD,			//사망

	THROW,			//던지기
	STOMP,			//밟기
	COMBO1,			//콤보어택1
	COMBO2,			//콤보어택2
	COMBO3,			//콤보어택3

	SATTACK,		//강공격
	DASHATTACK,		//대쉬 공격
	DASHSATTACK,	//대쉬 강공격
	JUMPATTACK,		//점프공격
	SATTACKDOWN		//바라보는방향키 + ↓ + 강공격 (커맨드입력)
};

//무기의 골인 위치
enum class GOALPOS
{
	PLAYER,
	WINOUT,
	FLOOR
};

//프레임 실행 타입 이넘
enum class FRAMETYPE : int
{
	ONCE,
	LOOP,
	REVERSEONCE,
	REVERSELOOP
};

class Player : public gameNode
{
private:
	//정보 구조체
	struct tagInfo
	{
	public:
		GameObject* attackObj;		//공격 오브젝트 연결
		vector3 attackGoal;			//공격 오브젝트의 목표
		RECT attackRc;				//공격용 렉트

		float jumpPower;			//점프파워
		float speed;				//속도

		bool isStand;

		bool hasMember;				//맴버소유 유무
		bool hasWeapon;				//무기소유 유무
		bool isImmune;				//이뮨상태인지
		bool isAttack;				//공격 유무
		bool isHit;					//맞았는지
		bool isDead;				//사망유무
		bool isControl;				//키입력 가능 유무
		bool isConDest;				//방향전환 가능 유무
		bool isSky;					//허공 유무
		bool isClimb;				//사다리 가능 유무
		bool isRestart;				//재시작유무

		MOVE_DIRECTION moveDest;	//행동 방향
		DIRECTION dest;				//인덱스 방향
		PL_STATE state;				//플레이어 상태
		PL_STATE preState;			//플레이어 이전상태
		GOALPOS goalState;			//골 상태

		WEAPON_TYPE weaponType;		//무기종류
		int hp;					//체력
		int maxHP;				//최대 체력
		int force;				//공격력
		int coin;					//소지금
		int	   LV;					//레벨
		float  exp;					//경험치
		int hitCount;				//피격 카운트 (3번맞으면 다운됨)

		float immuneTimer;			//이뮨타이머
		float frameTimer;			//프레임시간 타이머
		RENDERTYPE rendType;		//렌더타입
	};
private:
	tagInfo	   _info;			//플레이어 정보
	GameObject _obj;			//게임 오브젝트
	GameObject _shadow;			//게임 오브젝트
	RECT _temp;					//충돌용
	pet _pet;					//펫

	StageManager* _stageM;		//스테이지 매니저 링크
	ObjectManager* _objectM;	//오브젝트 매니저 링크
	EnemyManager* _enemyM;		//에너미 매니저 링크
	CollisionManager* _colM;	//충돌 매니저 링크
	GameObject*		_platform;	//플랫폼 링크
	//★맴버로 에너미를 가질 예정(동료로)

private:
	//상태 클래스
	IPlayerState*	_IState;		//현재 상태
	IPlayerState*	_idle;			//기본
	IPlayerState*	_wait;			//대기
	IPlayerState*	_walk;			//걷기
	IPlayerState*	_run;			//달리기
	IPlayerState*	_jump;			//점프
	IPlayerState*	_stick;			//벽잡기
	IPlayerState*	_climb;			//오르기
	IPlayerState*	_climbTop;		//오르기 끝(사다리끝)
	IPlayerState*	_pick;			//줍기

	IPlayerState*	_grab;			//잡기
	IPlayerState*	_guard;			//가드
	IPlayerState*	_roll;			//구르기
	IPlayerState*	_hit;			//피격
	IPlayerState*	_stun;			//기절
	IPlayerState*	_stand;			//기상
	IPlayerState*	_down;			//쓰러짐
	IPlayerState*	_dead;			//사망

	IPlayerState*	_throw;			//던지기
	IPlayerState*	_stomp;			//밟기
	IPlayerState*	_combo1;		//콤보어택1
	IPlayerState*	_combo2;		//콤보어택2
	IPlayerState*	_combo3;		//콤보어택3

	IPlayerState*	_sAttack;		//강공격
	IPlayerState*	_dashAttack;	//대쉬공격
	IPlayerState*	_dashSAttack;   //대쉬 강공격
	IPlayerState*	_jumpAttack;    //점프공격
	IPlayerState*	_SAttackDown;   //바라보는방향키 + ↓ + 강공격 (커맨드입력)

public:
	Player() {};
	~Player() {};
	virtual HRESULT init();		//초기화
	virtual void release();		//해제
	virtual void update();		//업데이트
	virtual void render();		//렌더

	/*====================================================================
									GETTER
	====================================================================*/
	GameObject getObj() { return _obj; }
	GameObject& getRefObj() { return _obj; }
	GameObject* getPObj() { return &_obj; }

	tagInfo& getInfo() { return _info; }
	GameObject* getPlatform() { return _platform; }
	EnemyManager* getEnemyM() {  return _enemyM; }
	ObjectManager* getObjectM() {  return _objectM; }
	StageManager* getStageM() { return _stageM; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkColM(CollisionManager* colM) { _colM = colM;}

	//조작 유무
	void setIsControl(bool control) { _info.isControl = control; }
	//상태 지정
	void setState(PL_STATE state);
	
	//충돌처리에 필요한 SETTER
	void setPlatform(GameObject* platform) { _platform = platform; }
	void setJumpPower(float num) { _info.jumpPower = num;  }
	void setIsSky(bool is) { _info.isSky = is; }
	void setIsClimb(bool is) { _info.isClimb = is; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	void stageInit();

	//같은 줄 유무 범위값 설정 버전도 있음
	bool isRange(GameObject obj);
	bool isRange(GameObject obj, float value);

	//무기업데이트
	void weaponUpdate();
	//중력작용
	void gravity();
	//키 입력
	void keyInput();
	//이미지변경
	void changeImg(string imgName, bool reverse);
	//프레임 연산
	void setFrame(FRAMETYPE frameType, float frameInterval);
	//프레임 실행
	void playFrame();
	//좌표 이동
	void movePos(float x, float z, float y);
	//좌표 고정
	void setPos(float x, float z, float y);
	//아이템오브젝트와 상호작용
	void checkItem();
	//어택 오브젝트를 골까지 움직임
	bool moveAttackObj();

	//맞기
	void hit();
};
