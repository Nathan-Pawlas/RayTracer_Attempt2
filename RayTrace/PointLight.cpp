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

	//Get Angle between Normal and LightDir
	//Assumption that LocalNormal is a Unit Vector
	double angle = acos(Vec<double>::dot(localNormal, lightDir));

	//If normal points away from light, not lit
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

void PointLight::SetColor(const Vec<double> color)
{
	m_color = color;
}

