#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL.h>
#include "Image.h"
#include "Camera.h"
#include "Objects/ObjSphere.h"

class Scene
{
public:
	Scene();

	bool Render(Image& outputImage);

private:

private:
	Camera m_cam;

	//Unit Sphere on Origin
	ObjSphere m_testSphere;
};


#endif // !SCENE_H