#pragma once
#include <algorithm>
using namespace std;

//======================================
// ## 20.11.12 ## CommonMacroFunction ##
//======================================

//Line
//       선긋기함수 (뿌릴DC, 시작X, 시작Y, 끝X, 끝Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x , y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2) , y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

//Rectangle
//x,y좌표를 기준으로 크기만큼 사각형이 생성됨
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


inline vector<vector<int>> CombinationR(vector<int> vI, int r, vector<int> tV, vector<vector<int>> &aV)
{
	if (tV.size() == r)
	{
		aV.push_back(tV);
		return aV;
	}
	const int lastIndex = tV.size() == 0 ? -1 : tV[tV.size() - 1];
	for (int i = lastIndex + 1; i < vI.size(); ++i)
	{
		tV.push_back(vI[i]);
		CombinationR(vI, r, tV, aV);
		tV.pop_back();
	}
	return aV;
}

// vector<int> Combination
inline vector<vector<int>> GetCombinationInt(vector<int> vInt, int r)
{
	vector<int> tempV;
	vector<vector<int>> ansV;
	CombinationR(vInt, r, tempV, ansV);
	return ansV;
}

inline vector<int> GetDifferenceVectorInt(vector<int> allV, vector<int> vInt)
{
	vector<int> result;
	result.clear();
	result.resize(allV.size() + vInt.size());//공간확보
	auto itr = set_difference(allV.begin(), allV.end(), vInt.begin(), vInt.end(), result.begin());//차집합
	result.erase(itr, result.end());//남은공간 제거

	return result;
}

