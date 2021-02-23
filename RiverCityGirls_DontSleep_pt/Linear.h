#pragma once

/*====================================================================
							1차 선분 유틸
====================================================================*/
enum class LINEAR_TYPE
{
	ON,		//선분에 붙어 있음
	UP,		//선분의 위에 있음
	DOWN,	//선분의 아래에 있음
	RIGHT,	//선분의 왼쪽에 있음
	LEFT,	//선분의 오른쪽에 있음
};

//1차 함수, 선분을 기준으로 어디에 위치하는지 판단
class Linear
{
	float a;	//x 기울기
	float b;	//y 절편

	vector3 vStart;
	vector3 vEnd;

public:
	Linear() {}
	Linear(float a, float b, vector3 start, vector3 end) :a(a), b(b), vStart(start), vEnd(end) {} // 기울기, 절편, 시작점, 끝점을 모두 가지고 선분 만들기
	Linear(vector3 start, vector3 end);
	
/*====================================================================
								GETTER
====================================================================*/
	//getter
	LINEAR_TYPE getType(float x, float y);
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }
	vector3 getStart() { return vStart; }
	vector3 getEnd() { return vEnd; }
	float geta() { return a; }
	float getb() { return b; }

/*====================================================================
								FUNCTION
====================================================================*/
	// 선분을 구하는 방정식
	Linear linearFromPoints(vector3 start, vector3 end);

	// 선분의 교차를 확인하고 교차점을 *vP에 담아준다*
	// 캐릭터 기준으로 호출, lB에는 오브젝트의 선분을 넣어준다. (순서를 꼭 지켜야 한다!)
	bool segmentIntersect(Linear lB, vector3* vP);

	//선분 그리기
	void LinearRender(HDC hdc);

};

