#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "Math/Vec.h"
#include "Ray.h"

class ObjectBase
{
public:
	ObjectBase();
	virtual  ~ObjectBase();


	//Determines if a Ray intersects with the object
	virtual bool Intersects(const Ray& castRay, Vec<double>& intPoint, 
		Vec<double>& localNormal, Vec<double>& localColor);
	//Determines if two floating-point numbers are close to equal
	bool FloatEqual(const double f1, const double f2);

public:
	//Object Base Color
	Vec<double> m_baseColor {3};
};

#endif // !OBJECTBASE_H

