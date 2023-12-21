#include "Ray.h"

Ray::Ray(const Vec<double>& point1, const Vec<double>& point2)
{
	m_point1 = point1;
	m_point2 = point2;
	m_lab = m_point2 - m_point1;
}

Vec<double> Ray::GetPoint1() const
{
	return m_point1;
}

Vec<double> Ray::GetPoint2() const
{
	return m_point2;
}
