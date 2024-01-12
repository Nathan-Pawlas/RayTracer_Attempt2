#include "MaterialBase.h"

MaterialBase::MaterialBase()
{
	m_maxReflectionRays = 3;
	m_relfectionRayCount = 0;
}

MaterialBase::~MaterialBase()
{
}

Vec<double> MaterialBase::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj, const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay)
{
	Vec<double> matColor{3};
	return matColor;
}

Vec<double> MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj, const Vec<double>& intPoint, const Vec<double>& localNormal, const Vec<double>& baseColor)
{
	// Compute the color due to diffuse illumination.
	Vec<double> diffuseColor	{3};
	double intensity;
	Vec<double> color {3};
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight->ComputeIllumination(intPoint, localNormal, objList, currObj, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}
	
	if (illumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
	}

	// Return the material color.
	return diffuseColor;

}

Vec<double> MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj, const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& incidentRay)
{
	Vec<double> refColor{3};

	//Reflection Vector
	Vec<double> d = incidentRay.m_lab;
	Vec<double> refVector = d - (2 * Vec<double>::dot(d, localNormal) * localNormal);

	//Reflection Ray
	Ray refRay (intPoint, intPoint + refVector);

	//Cast Ray, Find Closest Intersected Object
	std::shared_ptr<ObjectBase> closestObj;
	Vec<double> closestIntPoint{3};
	Vec<double> closestLocalNormal{3};
	Vec<double> closestLocalColor{3};

	bool intFound = CastRay(refRay, objList, currObj, closestObj, closestIntPoint, closestLocalNormal, closestLocalColor);

	//Comput Illumination For Closest Obj
	if (intFound && m_relfectionRayCount < m_maxReflectionRays)
	{
		//Increment Ray Count b/c we will call this function recursively
		m_relfectionRayCount += 1;

		if (closestObj->m_hasMaterial)
		{
			//This will enter a recurrsive call as ComputeColor will often use ComputeReflectionColor, this gives higher fidelity reflections when max rays is increased
			refColor = closestObj->m_pMaterial->ComputeColor(objList, lightList, closestObj, closestIntPoint, closestLocalNormal, refRay);
		}
		else
			refColor = MaterialBase::ComputeDiffuseColor(objList, lightList, closestObj, closestIntPoint, closestLocalNormal, closestObj->m_baseColor);
	}

	return refColor;
}

bool MaterialBase::CastRay(const Ray& castRay, const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::shared_ptr<ObjectBase>& thisObj, std::shared_ptr<ObjectBase>& closestObj, Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal, Vec<double>& closestLocalColor)
{
	Vec<double> intPoint{3};
	Vec<double> localNormal{3};
	Vec<double> localColor{3};
	double minDist = 1e6;
	bool intFound = false;

	for (auto curObj : objList)
	{
		if (curObj != thisObj)
		{
			bool validInt = curObj->Intersects(castRay, intPoint, localNormal, localColor);

			if (validInt)
			{
				intFound = true;

				double dist = (intPoint - castRay.m_point1).norm();

				if (dist < minDist)
				{
					minDist = dist;
					closestObj = curObj;
					closestIntPoint = intPoint;
					closestLocalNormal = localNormal;
					closestLocalColor = localColor;
				}
			}
		}
	}

	return intFound;
}

