#include "ObjectBase.h"
#include <math.h>

#define EPSILON 1e-21f;

ObjectBase::ObjectBase()
{
}

ObjectBase::~ObjectBase()
{
}

bool ObjectBase::Intersects(const Ray& castRay, Vec<double>& intPoint, Vec<double>& localNormal, Vec<double>& localColor)
{
	return false; //This is a virtual function, meant to be overriden
}

void ObjectBase::SetTransformMatrix(const GTform& transformMatrix)
{
	m_transformMat = transformMatrix;
}

bool ObjectBase::FloatEqual(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}

bool ObjectBase::AssignMaterial(const std::shared_ptr<MaterialBase>& objMaterial)
{
	if (objMaterial == NULL)
		return false;

	m_pMaterial = objMaterial;
	m_hasMaterial = true;
	return true;
}


