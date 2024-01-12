#include "Scene.h"
#include "Materials/SimpleMaterial.h"
#include <chrono>

Scene::Scene()
{
	//Create Test Materials
	auto testMat = std::make_shared<SimpleMaterial>(SimpleMaterial());
	testMat->m_baseColor = Vec<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	testMat->m_reflectivity = 0.5;
	testMat->m_shininess = 10.0;

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
	planeMat.SetTransform(Vec<double> {std::vector<double>{0.0, 0.0, 0.75}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{4.0, 2.0, 1.0}});
	m_objectList.at(3)->SetTransformMatrix(planeMat);

	//Modify Spheres Geometries
	GTform mat1, mat2, mat3;
	mat1.SetTransform(Vec<double>{std::vector<double>{-1.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});
	mat2.SetTransform(Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});
	mat3.SetTransform(Vec<double>{std::vector<double>{1.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});

	m_objectList.at(0)->SetTransformMatrix(mat1);
	m_objectList.at(1)->SetTransformMatrix(mat2);
	m_objectList.at(2)->SetTransformMatrix(mat3);
	
	//Set Object Colors
	m_objectList.at(0)->m_baseColor = Vec<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	m_objectList.at(1)->m_baseColor = Vec<double>{ std::vector<double>{1, 0.5, 0.0} };
	m_objectList.at(2)->m_baseColor = Vec<double>{ std::vector<double>{1, 0.8, 0.0} };

	//Assign Materials
	m_objectList.at(0)->AssignMaterial(testMat);

	//Construct a Test Light
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0)->m_location = Vec<double>{ std::vector<double>{5.25, -10.0, -5.0} };
	m_lightList.at(0)->m_color = Vec<double>{ std::vector<double>{0.0, 0.0, 1.0} };

	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(1)->m_location = Vec<double>{ std::vector<double>{0.0, -10.0, -5.0} };
	m_lightList.at(1)->m_color = Vec<double>{ std::vector<double>{0.0, 1.0, 0.0} };

	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(2)->m_location = Vec<double>{ std::vector<double>{-5.25, -10.0, -5.0} };
	m_lightList.at(2)->m_color = Vec<double>{ std::vector<double>{1.0, 0.0, 0.0} };
}

bool Scene::Render(Image& outputImage)
{
	//Set Dimensions
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	Ray camRay;
	Vec<double> intPoint{ 3 };
	Vec<double> localNormal{ 3 };
	Vec<double> localColor{ 3 };
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
			
			bool intersectionFound = CastRay(camRay, closestObj, closestIntPoint, closestLocalNormal, closestLocalColor);
			
			if (intersectionFound)
			{
				//Check For Material
				if (closestObj->m_hasMaterial)
				{
					//Use Material to Compute Color
					Vec<double> color = closestObj->m_pMaterial->ComputeColor(m_objectList, m_lightList, 
																	closestObj, closestIntPoint, closestLocalNormal, camRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					//Compute Basic Color (Diffuse)
					Vec<double> matColor = MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList, 
						closestObj, closestIntPoint, closestLocalNormal, closestObj->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Render Time: " << time.count() << "s" << std::endl;

	return true;
}

bool Scene::CastRay(Ray& castRay, std::shared_ptr<ObjectBase>& closestObj, Vec<double>& closestIntPoint, Vec<double>& closestLocalNormal, Vec<double>& closestLocalColor)
{
	Vec<double> intPoint{ 3 };
	Vec<double> localNormal{ 3 };
	Vec<double> localColor{ 3 };
	double minDist = 1e6;
	bool intersectionFound = false;

	//Check For Intersections
	for (auto currObj : m_objectList)
	{
		bool validInt = currObj.get()->Intersects(castRay, intPoint, localNormal, localColor);

		if (validInt)
		{
			intersectionFound = true;

			//Compute dist to POI
			double dist = (intPoint - castRay.m_point1).norm();
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
	return intersectionFound;
}
