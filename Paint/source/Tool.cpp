#include</Programming/Paint/Paint/headers/Tool.h>
#include</Programming/Paint/Paint/headers/Canvas.h>
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


	prevX = x;
	prevY = y;
}