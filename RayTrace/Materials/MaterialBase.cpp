#include "MaterialBase.h"

MaterialBase::MaterialBase()
{
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
	Vec<double> diffuseColor{3};
	double intensity;
	Vec<double> color{3};
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currLight : lightList)
	{
		validIllum = currLight->ComputeIllumination(intPoint, localNormal, objList, currObj, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			r += color.GetElement(0) * intensity;
			g += color.GetElement(1) * intensity;
			b += color.GetElement(2) * intensity;
		}
	}
	
	if (illumFound)
	{
		diffuseColor.SetElement(0, r * baseColor.GetElement(0));
		diffuseColor.SetElement(1, g * baseColor.GetElement(1));
		diffuseColor.SetElement(2, b * baseColor.GetElement(2));
	}

	return diffuseColor;
}

bool MaterialBase::CastRay(const Ray& castRay, const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::shared_ptr<ObjectBase>& thisObj, std::shared_ptr<ObjectBase>& closestObj, Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal, Vec<double>& closestLocalColor)
{
	return false;
}

