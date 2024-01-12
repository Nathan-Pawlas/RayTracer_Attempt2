#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../Objects/ObjectBase.h"
#include "../Lights/LightBase.h"
#include "../Math/Vec.h"
#include "../Ray.h"

class MaterialBase
{
public:
	MaterialBase();
	virtual ~MaterialBase();

	virtual Vec<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj,
		const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& camRay);

	static Vec<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj,
		const Vec<double>& intPoint, const Vec<double>& localNormal, const Vec<double>& baseColor);

	bool CastRay(const Ray& castRay, const std::vector<std::shared_ptr<ObjectBase>>& objList, 
		const std::shared_ptr<ObjectBase>& thisObj, std::shared_ptr<ObjectBase>& closestObj, 
		Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal, Vec<double>& closestLocalColor);

public:

};


#endif // !MATERIALBASE_H
