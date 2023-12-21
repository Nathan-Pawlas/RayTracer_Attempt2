#include "LightBase.h"

LightBase::LightBase()
{
}

LightBase::~LightBase()
{
}

bool LightBase::ComputeIllumination(const Vec<double>& intPoint, const Vec<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currObj, Vec<double>& color, double& intensity)
{
	return false;
}
