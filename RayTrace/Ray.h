#ifndef RAY_H
#define RAY_H

#include "Math/Vec.h"
class Ray
{
public:
	Ray();
	Ray(const Vec<double>& point1, const Vec<double>& point2);

	Vec<double> GetPoint1() const;
	Vec<double> GetPoint2() const;

public:
	Vec<double> m_point1{3};
	Vec<double> m_point2{3};
	//Vector which makes line from vec A to vec B
	Vec<double> m_lab	{3};
};

#endif
