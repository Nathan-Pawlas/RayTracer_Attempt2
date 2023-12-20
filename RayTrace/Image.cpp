#include "Image.h"

Image::Image()
{
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = NULL;
}

Image::~Image()
{
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
}

void Image::Init(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
	//Resize Image Arrays
	m_rChanel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_gChanel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_bChanel.resize(xSize, std::vector<double>(ySize, 0.0));

	//Set Dimensions
	m_xSize = xSize;
	m_ySize = ySize;

	//Set Renderer
	m_pRenderer = pRenderer;

	//Initialize Texture
	InitTexture();
}

void Image::SetPixel(const int x, const int y, const double r, const double g, const double b)
{
	m_rChanel.at(x).at(y) = r;
	m_gChanel.at(x).at(y) = g;
	m_bChanel.at(x).at(y) = b;
}

void Image::Display()
{
	//Allocate Pixel Buffer in Mem (using new keyword b/c SDL is in C so it needs to be compatable)
	Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

	//Clear Pixeel Buffer
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));


	for (int x = 0; x < m_xSize; x++)
	{
		for (int y = 0; y < m_ySize; y++)
		{
			//Convert 2D index to 1D index and set color data
			tempPixels[(y * m_xSize) + x] = ConvertColor(m_rChanel.at(x).at(y), m_gChanel.at(x).at(y), m_bChanel.at(x).at(y));
		}
	}

	//Update Texture With Pixel Buffer
	SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

	delete[] tempPixels;

	//Copy Texture to Renderer
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}


Uint32 Image::ConvertColor(const double red, const double green, const double blue)
{
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

	return pixelColor;
}

void Image::InitTexture()
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	//Delete Previous Texture
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);

	//Create New Texture to Store Image
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}
