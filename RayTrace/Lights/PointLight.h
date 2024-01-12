#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightBase.h"

class PointLight : public LightBase
{
public:
	PointLight();
	virtual ~PointLight() override;

	virtual bool ComputeIllumination(const Vec<double>& intPoint, const Vec<double>& localNormal,
		const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currObj,
		Vec<double>& color, double& intensity) override;

	void SetColor(const Vec<double> color);
};
#endif // !POINTLIGHT_H
