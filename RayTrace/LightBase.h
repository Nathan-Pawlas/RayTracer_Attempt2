#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "Math/Vec.h"
#include "Ray.h"
#include "ObjectBase.h"

class LightBase
{
public:
	LightBase();
	virtual ~LightBase();

	virtual bool ComputeIllumination(const Vec<double>& intPoint, const Vec<double>& localNormal,
		const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currObj,
		Vec<double>& color, double& intensity);

public:
	Vec<double> m_color{ 3 };
	Vec<double> m_location{ 3 };
	double m_intensity;
};
#endif // !LIGHTBASE_H

