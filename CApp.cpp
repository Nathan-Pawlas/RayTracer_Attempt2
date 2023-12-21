#include "CApp.h"
#include "RayTrace/Math/Vec.h"

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

	if (pWindow == NULL)
		return false;

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	m_Image.Init(1280, 720, pRenderer);

	//Set Background Color
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	m_Scene.Render(m_Image);

	m_Image.Display();

	SDL_RenderPresent(pRenderer); 

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

	return 0;
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
	////Set BackGround Color
	//SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(pRenderer);

	////Render Scene
	//m_Scene.Render(m_Image);

	////Display Image
	//m_Image.Display();

	////Display Result
	//SDL_RenderPresent(pRenderer);
}

//Deallocate Everything
void CAPP::OnExit()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}

void CAPP::PrintVec(const Vec<double>& vec)
{
	int nRows = vec.GetNumDims();
	for (int x = 0; x < nRows; x++)
	{
		std::cout << std::fixed << std::setprecision(3) << vec.GetElement(x) << std::endl;
	}
}


