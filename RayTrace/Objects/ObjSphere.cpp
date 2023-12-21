#include "ObjSphere.h"
#include <cmath>

ObjSphere::ObjSphere()
{

}

ObjSphere::~ObjSphere()
{
}

bool ObjSphere::Intersects(const Ray& castRay, Vec<double>& intPoint, Vec<double>& localNormal, Vec<double>& localColor)
{
	Vec<double> vhat = castRay.m_lab;
	vhat.Normalize();

	double b = 2.0 * Vec<double>::dot(castRay.m_point1, vhat);

	double c = Vec<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

	double intTest = (b * b) - 4.0 * c;

	if (intTest > 0.0)
		return true;

	return false;
}
