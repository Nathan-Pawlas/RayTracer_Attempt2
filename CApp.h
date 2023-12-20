#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "RayTrace/Image.h"
#include "RayTrace/Scene.h"

class CAPP
{
public:
	CAPP();

	bool OnInit();
	int OnExecute();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	Image m_Image;
	Scene m_Scene;

	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
};
#endif // !CAPP_H