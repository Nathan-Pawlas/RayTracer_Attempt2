#include "Scene.h"

Scene::Scene()
{
	//Configure Cam
	m_cam.SetPosition(Vec<double>{std::vector<double> { 0.0, -10.0, 0.0}});
	m_cam.SetLookAt(Vec<double>{std::vector<double>{0.0, 0.0, 0.0}});
	m_cam.SetUp(Vec<double>{std::vector<double>{0.0, 0.0, 1.0}});
	m_cam.SetHorizontalSize(0.25);
	m_cam.SetAspect(16.0 / 9.0);
	m_cam.UpdateCameraGeometry();

	//Construct a Test Sphere
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));


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

	m_objectList.at(0)->m_baseColor = Vec<double>{ std::vector<double>{255.0, 155.0, 0.0} };
	m_objectList.at(1)->m_baseColor = Vec<double>{ std::vector<double>{100.0, 150.0, 255.0} };
	m_objectList.at(2)->m_baseColor = Vec<double>{ std::vector<double>{0.0, 155.0, 155.0} };

	//Construct a Test Light
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0)->m_location = Vec<double>{ std::vector<double>{5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_color = Vec<double>{ std::vector<double>{255, 255.0, 255.0} };
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
	double minDist = 1e6;
	double maxDist = 0.0;

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

			//Check For Intersections
			for (auto currObj : m_objectList) {
				bool validInt = currObj.get()->Intersects(camRay, intPoint, localNormal, localColor);
				
				if (validInt) {
					//Compute Light Intensity
					double intensity;
					Vec<double> color {3};
					bool validIllum = false;
					for (auto currLight : m_lightList)
					{
						validIllum = currLight->ComputeIllumination(intPoint, localNormal, m_objectList, currObj, color, intensity);
					}

					//Compute Distance From Cam
					double dist = (intPoint - camRay.m_point1).norm();
					if (dist > maxDist) {
						maxDist = dist;
					}
					if (dist < minDist) {
						minDist = dist;
					}

					if (validIllum)
					{
						outputImage.SetPixel(x, y, localColor.GetElement(0) * intensity, localColor.GetElement(1) * intensity, localColor.GetElement(2) * intensity);
					}
					else 
					{
						//outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
				else {
					//outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
				}
			}
		}
	}

	std::cout << "Min Dist: " << minDist << std::endl;
	std::cout << "Max Dist: " << maxDist << std::endl;

	return true;
}
