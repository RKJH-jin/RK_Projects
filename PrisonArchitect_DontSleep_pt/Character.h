#pragma once
#include "ToolObject.h"

//중점으로부터 위치잡기위한 보정수치
#define HEADOFFSET 10
#define HANDOFFSETY -10
#define HANDOFFSETX 20

//사람기본정보
struct tagCharacterInfo
{
public:
	int role;					//역할
    int frameX[4];		        //프레임 번호
    float moveSpeed;	        //이동 속도 
    float actSpeed;		        //행동 속도
    bool isSleep;		        //취침 여부
	bool isSweep;               //청소 여부
	bool isStart;               //처음에 사람이 생성됐을때
	bool isDumping;             //쓰레기장으로 목표 설정이 됐는지
    ToolObject* toolObject;     //도구
	CHARACTERTYPE type;			//타입
	GOALSTATE goalState;		//골 상태
	BTSTATE btState;			//행동 상태
	float countTime;				//행동 실행시간

	GameObject* rightHand;
	GameObject* leftHand;
};

//사람
class Character : public GameObject
{
protected:
	//신체 파츠
	GameObject* _torso;
	//정보
	tagCharacterInfo _info;
   
public:
	Character();
	~Character() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	//★렌더함수들 다 없앨지도 모름 일단 안쓰는데 만약을 위해 있음
	virtual void render();

	virtual Character* MouseEnter();
	virtual Character* MouseStay();
	virtual Character* MouseExit();

	//게터
	tagCharacterInfo& GetInfo() { return _info; }
    TransformC* GetTransform() { return _transform; }

	//손생성
	virtual void CreateHands();
	//손위치초기화
	virtual void initHands();
	//옷상태변경
	virtual void SetNaked(bool isNaked) {  }

	void SetPrisonerRandomName();
	void SetPeopleRandomName();

	bool GetIsInArea(string name);

};