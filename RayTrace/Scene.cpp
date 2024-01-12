#include "Scene.h"
#include "Materials/SimpleMaterial.h"
#include <chrono>

Scene::Scene()
{
	

	//Configure Cam
	m_cam.SetPosition(Vec<double>{std::vector<double> { 0.0, -15.0, -1.0}});
	m_cam.SetLookAt(Vec<double>{std::vector<double>{0.0, 0.0, 0.0}});
	m_cam.SetUp(Vec<double>{std::vector<double>{0.0, 0.0, 1.0}});
	m_cam.SetHorizontalSize(0.25);
	m_cam.SetAspect(16.0 / 9.0);
	m_cam.UpdateCameraGeometry();

	//Construct Spheres
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));

	//Modify Spheres Geometries
	GTform mat1, mat2, mat3;
	mat1.SetTransform(Vec<double>{std::vector<double>{-1.5, 0.75, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});
	mat2.SetTransform(Vec<double>{std::vector<double>{0.0, -0.75, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});
	mat3.SetTransform(Vec<double>{std::vector<double>{1.5, 0.75, 0.0}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.5, 0.5, 0.5}});

	m_objectList.at(0)->SetTransformMatrix(mat1);
	m_objectList.at(1)->SetTransformMatrix(mat2);
	m_objectList.at(2)->SetTransformMatrix(mat3);

	//Create Sphere Materials
	auto material1 = std::make_shared<SimpleMaterial>(SimpleMaterial());
	auto material2 = std::make_shared<SimpleMaterial>(SimpleMaterial());
	auto material3 = std::make_shared<SimpleMaterial>(SimpleMaterial());

	material1->m_baseColor = Vec<double>{ std::vector<double>{0.0, 0.75, 0.0} };
	material1->m_reflectivity = 0.0;
	material1->m_shininess = 0.0;

	material2->m_baseColor = Vec<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	material2->m_reflectivity = 0.8;
	material2->m_shininess = 3.0;

	material3->m_baseColor = Vec<double>{ std::vector<double>{0.75, 0.0, 0.0} };
	material3->m_reflectivity = 0.05;
	material3->m_shininess = 1.0;

	//Assign Materials
	m_objectList.at(0)->AssignMaterial(material1);
	m_objectList.at(1)->AssignMaterial(material2);
	m_objectList.at(2)->AssignMaterial(material3);


	//Construct Planes
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));

	//Modify Plane
	GTform planeMat1, planeMat2, planeMat3, planeMat4;
	planeMat1.SetTransform(Vec<double> {std::vector<double>{-2.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, -1.5, 0.0}},
		Vec<double>{std::vector<double>{5.0, 5.0, 5.0}});
	planeMat2.SetTransform(Vec<double> {std::vector<double>{0.0, 0.0, 0.75}},
		Vec<double>{std::vector<double>{0.0, 0.0, 0.0}},
		Vec<double>{std::vector<double>{5.0, 5.0, 5.0}});
	planeMat3.SetTransform(Vec<double> {std::vector<double>{2.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{0.0, 1.5, 0.0}},
		Vec<double>{std::vector<double>{5.0, 5.0, 5.0}});
	planeMat4.SetTransform(Vec<double> {std::vector<double>{0.0, 5.0, 0.0}},
		Vec<double>{std::vector<double>{-1.5, 0.0, 0.0}},
		Vec<double>{std::vector<double>{5.0, 5.0, 5.0}});

	m_objectList.at(3)->SetTransformMatrix(planeMat1);
	m_objectList.at(4)->SetTransformMatrix(planeMat2);
	m_objectList.at(5)->SetTransformMatrix(planeMat3);
	m_objectList.at(6)->SetTransformMatrix(planeMat4);

	//Create Plane Materials
	auto pMat1 = std::make_shared<SimpleMaterial>(SimpleMaterial());
	auto pMat2 = std::make_shared<SimpleMaterial>(SimpleMaterial());
	auto pMat3 = std::make_shared<SimpleMaterial>(SimpleMaterial());

	pMat1->m_baseColor = Vec<double>{ std::vector<double>{1.0, 0.25, 0.25} };
	pMat1->m_reflectivity = 0.0;
	pMat1->m_shininess = 0.0;

	pMat2->m_baseColor = Vec<double>{ std::vector<double>{0.8, 0.8, 0.7} };
	pMat2->m_reflectivity = 0.0;
	pMat2->m_shininess = 0.0;

	pMat3->m_baseColor = Vec<double>{ std::vector<double>{0.25, 1.0, 0.25} };
	pMat3->m_reflectivity = 0.0;
	pMat3->m_shininess = 0.0;

	//Assign Materials
	m_objectList.at(3)->AssignMaterial(pMat1);
	m_objectList.at(4)->AssignMaterial(pMat2);
	m_objectList.at(5)->AssignMaterial(pMat3);
	m_objectList.at(6)->AssignMaterial(pMat2);
	


	//Construct a Test Light
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0)->m_location = Vec<double>{ std::vector<double>{1.0, -8.0, -3.0} };
	m_lightList.at(0)->m_color = Vec<double>{ std::vector<double>{0.8, 0.8, 0.8} };
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
	for (int y = 0; y < ySize; y++)
	{
		std::cout << std::setprecision(3) << ((float)y / ySize) * 100 << "%" << std::endl;
		for (int x = 0; x < xSize; x++)
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
					MaterialBase::m_relfectionRayCount = 0;
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
