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
			bool validInt = m_testSphere.Intersects(camRay, intPoint, localNormal, localColor);

			if (validInt) {
				double dist = (intPoint - camRay.m_point1).norm();
				if (dist > maxDist) {
					maxDist = dist;
				}
				if (dist < minDist) {
					minDist = dist;
				}
				outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
			}
			else {
				outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}
	}

	std::cout << "Min Dist: " << minDist << std::endl;
	std::cout << "Max Dist: " << maxDist << std::endl;

	return true;
}
