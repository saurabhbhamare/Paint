#include</Programming/Paint/Paint/headers/Tool.h>
#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/Application.h>
#include<iostream>

//Parent Class
Tool::Tool()
{
	
}

//Subclass -> Pencil

void Pencil::Draw(SDL_Renderer* renderer,SDL_Texture* texture,int&  prevX, int& prevY, int x, int y,SDL_Color currentSelectedColor)
{
	//std::cout << "In Pencil Draw Function" << std::endl;
	
	if (prevX == -1 || prevY == -1)
	{
		// Set the starting point if the previous point is invalid
		prevX = x;
		prevY = y;
		return;
	}

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, currentSelectedColor.r, currentSelectedColor.g, currentSelectedColor.b, 255);
	SDL_RenderDrawLine(renderer, prevX, prevY, x, y);
	SDL_SetRenderTarget(renderer, NULL);
	Application::GetInstance()->GetCanvas()->Render();


	prevX = x;
	prevY = y;
}

//Subclass ->Eraser

void Eraser::Erase(SDL_Renderer* renderer, SDL_Texture * texture, int& prevX, int& prevY, int x, int y,SDL_Color defaultBackgroundColor)
{
	if (prevX == -1 || prevY == -1)
	{
		prevX = x; 
		prevY = y;
		return;
	}
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, defaultBackgroundColor.r, defaultBackgroundColor.g, defaultBackgroundColor.b, 255);
	SDL_RenderDrawLine(renderer, prevX, prevY, x, y);
	SDL_SetRenderTarget(renderer, NULL);

	prevX = x; 
	prevY = y;
}
void Brush::Draw(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color currentSelectedColor)
{
	if (texture == nullptr)
	{
		std::cout << "texture in brush draw is null" << std::endl;
	}
	if (prevX == -1 || prevY == -1)
	{
		prevX = x;
		prevY = y;
		return;
	}
	int currPrevX = prevX;
	int currPrevY = prevY;

	int currX = x;
	int currY = y;
	   
		for (int i = 0; i < 6; i++)
		{
			
			currX++;
			currY++;
			currPrevX++;
			currPrevY++;
			 
			SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), texture);
			SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), currentSelectedColor.r, currentSelectedColor.g, currentSelectedColor.b, 255);
			SDL_RenderDrawLine(Application::GetInstance()->GetRenderer(), currPrevX, currPrevY, currX, currY);
			//SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL);
		}
	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL);
	prevX = x;
	prevY = y;
}