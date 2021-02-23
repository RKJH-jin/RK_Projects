#include "stdafx.h"
#include "vector3.h"
/*********************************************************************
	getter, point
*********************************************************************/

vector3::vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector3::vector3(int x, int y, int z)
{
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;

}

POINT vector3::getPoint()
{
	return { (LONG)x,(LONG)z };
}

/*********************************************************************
	operator
*********************************************************************/

vector3 vector3::operator+(vector3 & v)
{
	vector3 result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return vector3();
}

vector3 vector3::operator-(vector3 & v)
{
	vector3 result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

void vector3::operator+=(vector3 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void vector3::operator-=(vector3 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

vector3 vector3::operator*(float & s)
{
	vector3 result;
	result.x = this->x * s;
	result.y = this->y * s;
	result.z = this->z * s;
	return result;
}

vector3 vector3::operator/(float & s)
{
	vector3 result;
	result.x = this->x / s;
	result.y = this->y / s;
	result.z = this->z / s;
	return result;
}

bool vector3::operator==(vector3 & v)
{
	if (x == v.x && y == v.y && z == v.z) return true;
	return false;
}

bool vector3::operator!=(vector3 & v)
{
	return !((*this) == v);
}

bool vector3::operator<(vector3 & v)
{
	return this->x < v.x && this->z < v.z;
}

bool vector3::operator<=(vector3 & v)
{
	return this->x <= v.x && this->z <= v.z;
}

/*********************************************************************
	function
*********************************************************************/

//정규화
vector3 vector3::normalize(vector3 v)
{
	vector3 result = v;
	float length = vector3::length(v);
	result.x /= length;
	result.y /= length;
	return vector3();
}

//라디안으로 변환
float vector3::toRadian(vector3 v)
{
	int sign = 1;
	vector3 dir = v;
	float result = (acos(dir.x));
	if (dir.y > 0.f)
	{
		result = PI * 2.f - result;
	}
	return result;
}

//벡터 크기 (길이)
float vector3::length(vector3 v)
{
	vector3 vec = v;
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

//벡터 사이의 거리
float vector3::distance(vector3 vA, vector3 vB)
{
	return sqrt(pow(vA.x - vB.x, 2) + pow(vA.y - vB.y, 2) + pow(vA.z - vB.z, 2));
}

//벡터 내적
float vector3::innerProduct(vector3 vA, vector3 vB)
{
	return vA.x * vB.x + vA.z * vB.z;
}

//벡터 외적
float vector3::externalProduct(vector3 vA, vector3 vB)
{

	return vA.x * vB.z - vA.z * vB.x;
}

float vector3::CounterClockWise(vector3 vA, vector3 vB)
{
	return externalProduct(vA - *this, vB - *this);
}
