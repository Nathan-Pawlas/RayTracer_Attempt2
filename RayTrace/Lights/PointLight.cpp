#include "PointLight.h"
#include <math.h>

PointLight::PointLight()
{
	m_color - Vec<double>{std::vector<double>{1.0, 1.0, 1.0}};
	m_intensity = 1.0;
}

PointLight::~PointLight()
{
}

bool PointLight::ComputeIllumination(const Vec<double>& intPoint, const Vec<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currObj, Vec<double>& color, double& intensity)
{
	//Get Vector From Intersection to Light
	Vec<double> lightDir = (m_location - intPoint).Normalized();

	Vec<double> startPoint = intPoint;

	//Cast Ray from IntPoint to Light
	Ray lightRay(startPoint, startPoint + lightDir);

	Vec<double> poi{ 3 };
	Vec<double> poiNormal{ 3 };
	Vec<double> poiColor{ 3 };
	bool validInt = false;
	for (auto sceneObj : objectList)
	{
		if (sceneObj != currObj)
		{
			validInt = sceneObj->Intersects(lightRay, poi, poiNormal, poiColor);
		}
		//If there's an intersection, we can break because we are in a shadow
		if (validInt)
			break;
	}

	if (!validInt) //Not in Shadow
	{
		//Find angle between local norm and light ray
		//Assume local Norm is a unit vector
		double angle = acos(Vec<double>::dot(localNormal, lightDir));

		if (angle > 1.5708)
		{
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else //In shadow
	{
		color = m_color;
		intensity = 0.0;
		return false;
	}
	return false;
}

void PointLight::SetColor(const Vec<double> color)
{
	m_color = color;
}

