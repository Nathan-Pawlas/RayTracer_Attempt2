#include "Scene.h"
#include <chrono>

Scene::Scene()
{
	//Configure Cam
	m_cam.SetPosition(Vec<double>{std::vector<double> { 0.0, -10.0, -1.0}});
	m_cam.SetLookAt(Vec<double>{std::vector<double>{0.0, 0.0, 0.0}});
	m_cam.SetUp(Vec<double>{std::vector<double>{0.0, 0.0, 1.0}});
	m_cam.SetHorizontalSize(0.25);
	m_cam.SetAspect(16.0 / 9.0);
	m_cam.UpdateCameraGeometry();

	//Construct a Test Sphere
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));

	//Construct Test Plane
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));
	m_objectList.at(3)->m_baseColor = Vec<double>{ std::vector<double>{0.5, 0.5, 0.5} };

	//Modify Plane
	GTform planeMat;
	planeMat.SetTransform( Vec<double> {std::vector<double>{0.0, 0.0, 0.75}},
			Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
			Vec<double>{std::vector<double>{4.0, 2.0, 1.0}} );
	m_objectList.at(3)->SetTransformMatrix(planeMat);

	//Modify Spheres
	GTform mat1, mat2, mat3;
	mat1.SetTransform(Vec<double>{std::vector<double>{-1.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.75}});
	mat2.SetTransform(Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.75, 0.75, 0.75}});
	mat3.SetTransform(Vec<double>{std::vector<double>{1.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.75, 0.5}});

	m_objectList.at(0)->SetTransformMatrix(mat1);
	m_objectList.at(1)->SetTransformMatrix(mat2);
	m_objectList.at(2)->SetTransformMatrix(mat3);

	m_objectList.at(0)->m_baseColor = Vec<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	m_objectList.at(1)->m_baseColor = Vec<double>{ std::vector<double>{1, 0.5, 0.0} };
	m_objectList.at(2)->m_baseColor = Vec<double>{ std::vector<double>{1, 0.8, 0.0} };

	//Construct a Test Light
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0)->m_location = Vec<double>{ std::vector<double>{5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_color = Vec<double>{ std::vector<double>{1.0, 1.0, 1.0} };
}

bool Scene::Render(Image& outputImage)
{
	//Set Dimensions
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	Ray camRay;
	Vec<double> intPoint {3};
	Vec<double> localNormal {3};
	Vec<double> localColor {3};
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);

	auto start = std::chrono::high_resolution_clock::now();

	//Iterate Through Pixels
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			//Normalize X and Y coords
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			//Generate Ray For Pixel
			m_cam.GenerateRay(normX, normY, camRay);

			std::shared_ptr<ObjectBase> closestObj;
			Vec<double> closestIntPoint{ 3 };
			Vec<double> closestLocalNormal{ 3 };
			Vec<double> closestLocalColor{ 3 };
			double minDist = 1e6;
			bool intersectionFound = false;

			//Check For Intersections
			for (auto currObj : m_objectList) 
			{
				bool validInt = currObj.get()->Intersects(camRay, intPoint, localNormal, localColor);
				
				if (validInt) 
				{
					intersectionFound = true;

					//Compute dist to POI
					double dist = (intPoint - camRay.m_point1).norm();
					//Set Values for closest Object (for Object Culling)
					if (dist < minDist)
					{
						minDist = dist;
						closestObj = currObj;
						closestIntPoint = intPoint;
						closestLocalNormal = localNormal;
						closestLocalColor = localColor;
					}
				}
			}
			if (intersectionFound)
			{
				//Calculate Illumination
				double intensity;
				Vec<double> color{ 3 };
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool validIllum = false;
				bool illumFound = false;
				for (auto currLight : m_lightList)
				{
					validIllum = currLight->ComputeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObj, color, intensity);

					if (validIllum)
					{
						illumFound = true;
						red += color.GetElement(0) * intensity;
						green += color.GetElement(1) * intensity;
						blue += color.GetElement(2) * intensity;
					}
				}

				if (illumFound)
				{
					red *= closestLocalColor.GetElement(0);
					green *= closestLocalColor.GetElement(1);
					blue *= closestLocalColor.GetElement(2);
					outputImage.SetPixel(x, y, red, green, blue);
				}
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Render Time: " << time.count() << "ms" << std::endl;

	return true;
}
