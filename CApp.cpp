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

	//Render Scene
	m_Scene.Render(m_Image);

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


