#include "ObjPlane.h"
#include <cmath>

ObjPlane::ObjPlane()
{
}

ObjPlane::~ObjPlane()
{
}

bool ObjPlane::Intersects(const Ray& castRay, Vec<double>& intPoint, Vec<double>& localNormal, Vec<double>& localColor)
{
	/* Intersection for a plane can be expressed as a = u [1,0,0] + v[0,1,0] - tk
	* which can be reduced to t = a_z / -k_z
	* Note: the third entry of the vectors are free variables in the linear combination because 
	* this object is expressed in terms of local coordinates, so we define our plane to lie on the x-y axes
	* originating from the origin. Then if we want to move/rotate it we can just use geometric transforms!
	*/

	//Copy Ray and Apply Backwards Transform (World -> Local coords)
	Ray bckRay = m_transformMat.Apply(castRay, BCKTFORM); //a

	//Find k
	Vec<double> k = bckRay.m_lab;
	k.Normalize();

	//Check for intersection (Ray is not Parallel to plane)
	if (FloatEqual(k.GetElement(2), 0.0))
		return false;

	//Find t (dist. from camera)
	double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2); 

	//If t is neg. int point behind camera, ignore it
	if (t < 0.0)
		return false;

	//Find vectors u and v (to check they're in unit plane so it's not infinite)
	double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
	double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

	//Check the vectors are in the UNIT plane (i.e 1x1 plane, to be scaled by gtform)
	if (abs(u) <= 1.0 && abs(v) <= 1.0)
	{

		//Find intersection and transform back into world coords
		Vec<double> poi = bckRay.m_point1 + t * k;
		intPoint = m_transformMat.Apply(poi, FWDTFORM);

		//Find local Normal
		Vec<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
		Vec<double> normalVec{ std::vector<double> {0.0, 0.0, -1.0} };
		Vec<double> globalOrigin = m_transformMat.Apply(localOrigin, FWDTFORM);
		localNormal = m_transformMat.Apply(normalVec, FWDTFORM) - globalOrigin;
		localNormal.Normalize();

		//Set Base Color
		localColor = m_baseColor;

		return true;
	}
	return false;
}
