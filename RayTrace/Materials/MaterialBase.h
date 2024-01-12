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

	Vec<double> ComputeReflectionColor(const std::vector<std::shared_ptr<ObjectBase>>& objList, const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currObj,
		const Vec<double>& intPoint, const Vec<double>& localNormal, const Ray& incidentRay);

	bool CastRay(const Ray& castRay, const std::vector<std::shared_ptr<ObjectBase>>& objList, 
		const std::shared_ptr<ObjectBase>& thisObj, std::shared_ptr<ObjectBase>& closestObj, 
		Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal, Vec<double>& closestLocalColor);

public:
	//Counter For Rays Used For Reflections (inline static b/c we only want 1 instance of this variable used across all objects)
	inline static int m_maxReflectionRays;
	inline static int m_relfectionRayCount;
};


#endif // !MATERIALBASE_H
