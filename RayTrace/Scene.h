#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "Image.h"
#include "Camera.h"
#include "Objects/ObjSphere.h"
#include "Lights/PointLight.h"
#include "Objects/ObjPlane.h"

class Scene
{
public:
	Scene();

	bool Render(Image& outputImage);

	bool CastRay(Ray& castRay, std::shared_ptr<ObjectBase>& closestObj, 
		Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal,
		Vec<double>& closestLocalColor);

private:

private:
	Camera m_cam;

	//List of Objs in Scene
	std::vector<std::shared_ptr<ObjectBase>> m_objectList;

	//List of Lights in Scene
	std::vector<std::shared_ptr<LightBase>> m_lightList;
};


#endif // !SCENE_H