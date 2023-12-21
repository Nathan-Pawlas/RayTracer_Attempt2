#include "Scene.h"

Scene::Scene()
{
}

bool Scene::Render(Image& outputImage)
{
	//Set Dimensions
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			double r = (static_cast<double>(x) / static_cast<double>(xSize)) * 255.0;
			double g = (static_cast<double>(y) / static_cast<double>(ySize)) * 255.0;
			outputImage.SetPixel(x, y, r, g, g+r);
		}
	}

	return true;
}
