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
	//Copy Ray and apply BCK Transform (World Coords 'back to' local coords)
	Ray bckRay = m_transformMat.Apply(castRay, BCKTFORM);

	//Formula for finding the distance to an intersection of a sphere (centered on origin)
	//(bx^2+by^2+bz^2)t^2 + (2axbx + 2ayby + 2azbz)t + (ax^2 + ay^2 + az^2 - r^2) = 0
	//a = ray origin (don't need to worry about it since we're working in local coords with Unit Vector so always 1)
	//b = ray direction
	//r = circle radius
	//t = dist to hit (from a)

	Vec<double> vhat = bckRay.m_lab;
	vhat.Normalize();

	double b = 2.0 * Vec<double>::dot(bckRay.m_point1, vhat);

	double c = Vec<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;

	double discriminant = (b * b) - 4.0 * c; //Quadratic Discriminant

	Vec<double> poi; //Point of Intersection

	if (discriminant > 0.0)
	{
		//completing the Quadratic Formula:
		//(-b +- sqrt(dircriminant)) / (2.0f * a)
		double numSQRT = sqrtf(discriminant);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		if (t1 < 0.0 || t2 < 0.0)
		{
			return false;
		}
		else
		{
			if (t1 < t2) 
			{
				poi = bckRay.m_point1 + (vhat * t1);
			}
			else //It's always gonna takes this condition because b is subtracted in t2 and it's not divided by a neg a b/c a is always 1 so it must be that t2 < t1
			{
				poi = bckRay.m_point1 + (vhat * t2);
			}

			//Transform Intersection Point back Into World Coordinates
			intPoint = m_transformMat.Apply(poi, FWDTFORM);

			//Get Local Normal
			Vec<double> objOrigin = Vec<double>{ std::vector<double>{ 0.0,0.0,0.0 } };
			Vec<double> newOrigin = m_transformMat.Apply(objOrigin, FWDTFORM);
			localNormal = intPoint - newOrigin;
			localNormal.Normalize();

			localColor = m_baseColor;
		}
		return true;
	}

	return false;
}
