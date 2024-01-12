#include "SimpleMaterial.h"

SimpleMaterial::SimpleMaterial()
{
}

SimpleMaterial::~SimpleMaterial()
{
}

Vec<double> SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj, const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay)
{
	//Define Initial Colors
	Vec<double> matColor{3};
	Vec<double> refColor{3};
	Vec<double> difColor{3};
	Vec<double> spcColor{3};

	//Compute Diffuse Color
	difColor = ComputeDiffuseColor(objList, lightList, currObj, intPoint, localNormal, m_baseColor);

	//Compute Specular Color
	if (m_shininess > 0.0)
		spcColor = ComputeSpecular(objList, lightList, intPoint, localNormal, camRay);
	
	//Add The Two Colors Into A Final Color
	matColor = difColor + spcColor;

	return matColor;
}

Vec<double> SimpleMaterial::ComputeSpecular(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay)
{
	Vec<double> spcColor{3};
	double red= 0.0;
	double green = 0.0;
	double blue = 0.0;

	//Iterate Through Lights In Scene
	for (auto curLight : lightList)
	{
		double intensity = 0.0;

		//Vector from intersection to light
		Vec<double> lightDir = (curLight->m_location - intPoint).Normalized();
		Vec<double> startPoint = intPoint + (lightDir * 0.001);

		Ray lightRay(startPoint, startPoint + lightDir);

		//Iterate Through Objects to Check For Obstructions
		Vec<double> poi{3};
		Vec<double> poiNormal{3};
		Vec<double> poiColor{3};
		bool validInt = false;

		for (auto obj : objList)
		{
			validInt = obj->Intersects(lightRay, poi, poiNormal, poiColor);
			if (validInt)
				break;
		}

		//No Intersection, Then Continue Computing Specular Color
		if (!validInt)
		{

			//Reflection Vector
			Vec<double> d = lightRay.m_lab;
			Vec<double> r = d - (2 * Vec<double>::dot(d, localNormal) * localNormal);
			r.Normalize();

			//Compute Dot Product
			Vec<double> v = camRay.m_lab;
			v.Normalize();
			double dotProd = Vec<double>::dot(r, v);

			if (dotProd > 0.0)
				intensity = m_reflectivity * std::pow(dotProd, m_shininess);
		}

		red+= curLight->m_color.GetElement(0) * intensity;
		green += curLight->m_color.GetElement(1) * intensity;
		blue += curLight->m_color.GetElement(2) * intensity;

	}

	spcColor.SetElement(0, red);
	spcColor.SetElement(1, green);
	spcColor.SetElement(2, blue);

	return spcColor;
}
