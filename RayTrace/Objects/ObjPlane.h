#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "ObjectBase.h"
#include "../gtfm.h"

class ObjPlane : public ObjectBase
{
public:
	ObjPlane();
	virtual ~ObjPlane() override;

	virtual bool Intersects(const Ray& castRay, Vec<double>& intPoint, Vec<double>& localNormal, Vec<double>& localColor) override;

private:

};

#endif // !OBJPLANE_H
