#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../Math/Vec.h"
#include "../Ray.h"
#include "../gtfm.h"
#include <memory>

class MaterialBase;

class ObjectBase
{
public:
	ObjectBase();
	virtual  ~ObjectBase();


	//Determines if a Ray intersects with the object
	virtual bool Intersects(const Ray& castRay, Vec<double>& intPoint, 
		Vec<double>& localNormal, Vec<double>& localColor);

	//Set The Transform Matrix
	void SetTransformMatrix(const GTform& transformMatrix);

	//Determines if two floating-point numbers are close to equal
	bool FloatEqual(const double f1, const double f2);

	bool AssignMaterial(const std::shared_ptr<MaterialBase>& objMaterial);

public:
	//Object Base Color
	Vec<double> m_baseColor {3};

	//Geometric Transform Applied to the Object
	GTform m_transformMat;

	//Objects Assigned Material
	std::shared_ptr<MaterialBase> m_pMaterial;

	//Flag indicating existence of material
	bool m_hasMaterial = false;
};

#endif // !OBJECTBASE_H

