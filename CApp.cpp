#include "CApp.h"

//Constructor
CAPP::CAPP()
{
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
}

//Initialize Window and Renderer
bool CAPP::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	pWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		1280, 720, SDL_WINDOW_SHOWN);

	if (pWindow != NULL)
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	else
		return false;

	m_Image.Init(1280, 720, pRenderer);

	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			double red = (static_cast<double>(x) / 1280.0) * 255;
			double green = (static_cast<double>(y) / 1280.0) * 255;
			m_Image.SetPixel(x, y, red, green, 0.0);
		}
	}

	return true;

}

int CAPP::OnExecute()
{
	SDL_Event event;

	if (!OnInit())
		return -1;

	//Main Render Loop
	while (isRunning) 
	{
		while (SDL_PollEvent(&event) != 0)
			OnEvent(&event);
		OnLoop();
		OnRender();
	}
}

void CAPP::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		isRunning = false;
}

void CAPP::OnLoop()
{
}

void CAPP::OnRender()
{
	//Set BackGround Color
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	//Display Image
	m_Image.Display();

	//Display Result
	SDL_RenderPresent(pRenderer);
}

//Deallocate Everything
void CAPP::OnExit()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}


