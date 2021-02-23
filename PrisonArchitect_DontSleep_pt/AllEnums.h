#pragma once
#define TILESIZE 64
#define TILECOUNTX 60
#define TILECOUNTY 50

//지역
enum class TILEAREA
{
	JAIL,			//감옥
	KITCHEN,		//부엌
	FOODCOURT,		//식당
	SHOWERROOM,		//샤워실
	STORAGE,		//창고
	DUMP,			//쓰레기장
	FIELD,			//운동장
	MEDICAL,		//의무실
	LOUNGE,			//휴게실
	OFFICE,
	STUDYROOM,
	WARDENROOM,
	END,			//없음
};

//마우스 상태
enum class MOUSESTATE
{
	BUILD,
	DESTROY,	//파괴
	DELETECHAR,	//캐릭터 삭제
	SELECT,

};

//골상태
enum class GOALSTATE
{
	NONE,
	GOALSET,
	GOALRUNNING,
	GOALREACH,
};

//행동상태
enum class BTSTATE
{
	NONE,
	COOKING,
    SERVING,
    EAT,
	END
};
//마우스 드래그
enum class MOUSEDRAG
{
	POINT,		//점
	LINE,		//선
	RECT,		//렉트
	END,		//없음
};

//오브젝트 타입
enum class TILEATTRIBUTE
{
	TERRAIN,	//지형
	WALL,		//벽
	OBJECT,		//물건
	AREA,		//지역
	END,		//없음
};

//짐 타입
enum class STUFFTTYPE
{
	COOKBACON,
	FOODBACON,
	BACONS,
	BOX,			//상자
	GRAYBRICKS,		//회벽돌
	REDBRICKS,		//적벽돌
	CABBAGES,
	REBARS,
	SOUPGREENS,
	SOUPS,
	TRAYS,
	TRAYDIRTYS,
	WOODCUTS,
	CAR,
	TRASH,			//쓰레기
	POTATOS,
	END,

};

//도구타입
enum class TOOLTYPE
{
	NONE,           //빈 손
	BACON,			//베이컨
	BOX,			//상자
	GRAYBRICK,		//회벽돌
	REDBRICK,		//적벽돌
	CABBAGE,
	DOCUMENT,
	DRIVER,
	MOP,
	POTATO,
	REBAR,
	SOUP,
	SOUPGREEN,
	SPATULA,
	SYRIGNE,
	TRAY,
	TRAYDIRTY,
	WOODCUT,
	TRASH,			//쓰레기
	END,

};

enum class DIRECTION
{
	FRONT,		//앞
	LEFT,		//왼
	BACK,		//뒤
	RIGHT,		//오
};

enum class ANCHORPIVOT
{
	LeftTop,
	LeftCenter,
	LeftBottom,
	CenterTop,
	Center,
	CenterBottom,
	RightTop,
	RightCenter,
	RightBottom,
};
enum class TILETERRAIN
{
	GRASS1,
	GRASS2,
	GRASS3,
	GROUND,
	CONCRETE1,
	CONCRETE2,
	CONCRETE3,
	FLOOR,
	ROAD,
	ASPHALT,
	MUD,
	BRICK,
	ROCK,
	MOON,
	FLOOR2,
	FLOWER,
	CRACK,
	TILE,
	CARPET,
	MONO,
	END,
};

enum class TILEWALL
{
	WALL0,	 WALL1, WALL2,	WALL3,	WALL4,
	WALL5,	WALL6,	WALL7,	WALL8,	WALL9,
	WALL10, WALL11, WALL12, WALL13, WALL14,
	WALL15, WALL16, WALL17, WALL18, WALL19,
	WALL20, WALL21, WALL22, WALL23, WALL24,
	WALL25, WALL26, WALL27, WALL28, WALL29,
	END,
};

enum class TILEOBJECT
{
	가스레인지,
	배식대,
	벤치,
	변기,
	사무실책상,
	샤워기,
	서류보관함,
	쇼파,
	식탁,
	싱크대,
	의자,
	이중철창문,
	자판기,
	직원문,
	철창문,
	침대,
	END,
};

//스탭 역할
enum class STAFFROLE
{
	ACCOUNTANT,
	CLEANER,
	COOKER,
	DOCTER,
	WORKER,
	WARDER,
	TEACHER,
	WARDEN,
	END,
};

//캐릭터종류
enum class CHARACTERTYPE
{
	PEOPLE,
	PRISONER,
	STAFF,
	END
};

//사람역할
enum class PEOPLEROLE
{
	BITALIA,
	BOSS,
	NICO,
	END,
};

// test용
enum class LOCATION : int
{
    STORAGE,
    NON_STORAGE,
};

enum class SITUATION : int
{
    ORDINARY,
    RIOT,

};

enum class SEARCHDIRECTION : int
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UPPERLEFT,
    UPPERRIGHT,
    LOWERLEFT,
    LOWERRIGHT,
};

//시간표
enum class TIMESCHEDULE : int
{
	SLEEP,		//취침
	MEAL,		//식사
	WASH,		//샤워
	GROUND,		//운동
	REST,		//휴식
	IMPRISON,	//감금
};