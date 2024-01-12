#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATER_H

#include "MaterialBase.h"

class SimpleMaterial : public MaterialBase
{
public:
	SimpleMaterial();
	virtual ~SimpleMaterial() override;

	virtual Vec<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj,
		const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay) override;

	Vec<double> ComputeSpecular(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList,
		const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay);

public:
	Vec<double> m_baseColor{ std::vector<double>{1.0, 0.0, 1.0} };
	double m_shininess = 0.0;
	double m_reflectivity = 0.0;
};

#endif // !SIMPLEMATERIAL_H
