#include "stdafx.h"
#include "Linear.h"

Linear::Linear(vector3 start, vector3 end)
{
	if ((start.x - end.x) == 0)
	{
		a = 9999;
	}
	else
	{
		a = (start.z - end.z) / (start.x - end.x);	// x기울기 (x변화량에 대한 y변화량)
		b = start.z - (start.x*a);					// y 절편
	}


	vStart = start;								// 시작 점
	vEnd = end;									// 끝 점
}

LINEAR_TYPE Linear::getType(float x, float y)
{
	return LINEAR_TYPE();
}

Linear Linear::linearFromPoints(vector3 start, vector3 end)
{
	Linear linear;

	linear.vStart = start;
	linear.vEnd = end;

	float differY(start.z - end.z);
	float differX(start.x - end.x);

	if (differX == 0 && differY != 0)
	{
		linear.a = INT_MAX;
		linear.b = start.x;
	}
	else
	{
		linear.a = differY / differX;
		linear.b = start.z - (start.x*linear.a);
	}
	return linear;
}

// this가 플레이어, lB가 오브젝트
bool Linear::segmentIntersect(Linear lB, vector3* vP)
{
	float AtoB = (this->vStart.CounterClockWise(this->vEnd, lB.vStart)) * (this->vStart.CounterClockWise(this->vEnd, lB.vEnd));
	float BtoA = lB.vStart.CounterClockWise(lB.vEnd, this->vStart) * lB.vStart.CounterClockWise(lB.vEnd, this->vEnd);


	// 서로 같은 기울기를 가지는데 겹칠 때(한 점 겹침 또는 한 선분이 다른 선분을 일부 포함)
	if (AtoB == 0 && BtoA == 0)
	{
		vector3 tmpS = this->vStart;
		vector3 tmpE = this->vEnd;
		vector3 tmpBS = lB.vStart;
		vector3 tmpBE = lB.vEnd;

		if (tmpE < tmpS) swap(tmpS, tmpE);
		if (tmpBE < tmpBS) swap(tmpBS, tmpBE);

		if (!(tmpE < tmpBS || tmpBE < tmpS))
		{
			if (tmpS <= tmpBS) *vP = tmpBS;
			else *vP = tmpBE;
			return true;
		}
		return false;
	}

	if (AtoB <= 0 && BtoA <= 0)
	{
		if (this->a == 9999)
		{
			vP->x = this->getStart().x;
			vP->z = lB.getY(vP->x);
			vP->y = this->getStart().y;
		}
		else
		{
			vP->x = (lB.b - this->b) / (this->a - lB.a);
			vP->z = (this->a * lB.b - this->b * lB.a) / (this->a - lB.a);
			vP->y = this->getStart().y;
			
		}
		return true;
	}
	return false;
}

void Linear::LinearRender(HDC hdc)
{
	POINT temp[2];
	temp[0] = PointMake(vStart.x, vStart.z);
	temp[1] = PointMake(vEnd.x, vEnd.z);
	Polyline(hdc, temp, 2);

}

