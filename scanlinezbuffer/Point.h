#pragma once
#include "Vector.h"
class Point
{
public:
	Point();
	Point(const float xx, const float yy, const float zz);
	~Point();
	Vector operator-(const Point &p) const;
	bool operator<(const Point &p)const;
public:
	float x, y, z;
};