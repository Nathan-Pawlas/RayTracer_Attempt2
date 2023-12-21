#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "../ObjectBase.h"

class ObjSphere : public ObjectBase
{
public:
	ObjSphere();
	virtual ~ObjSphere() override;

	virtual bool Intersects(const Ray& castRay, Vec<double>& intPoint,
		Vec<double>& localNormal, Vec<double>& localColor) override;
};

#endif // !OBJSPHERE_H

