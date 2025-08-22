#include</Programming/Paint/Paint/headers/Tool.h>
#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/Application.h>
#include<iostream>

//Parent Class
Tool::Tool()
{
	
}

//Subclass -> Pencil

void Pencil::Draw(SDL_Texture* texture,int&  prevX, int& prevY, int x, int y,SDL_Color currentSelectedColor)
{
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();

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

//void Eraser::Erase(SDL_Renderer* renderer, SDL_Texture * texture, int& prevX, int& prevY, int x, int y,SDL_Color defaultBackgroundColor)
//{
//	if (prevX == -1 || prevY == -1)
//	{
//		prevX = x; 
//		prevY = y;
//		return;
//	}
//	SDL_SetRenderTarget(renderer, texture);
//	SDL_SetRenderDrawColor(renderer, defaultBackgroundColor.r, defaultBackgroundColor.g, defaultBackgroundColor.b, 255);
//	for (int i = -3; i < 3; i++)
//	{
//		SDL_RenderDrawLine(renderer, prevX+i, prevY+i, x+i, y+i);
//		//SDL_RenderDrawLine(renderer, prevX-i, prevY+-i, x-i, y-i);
//	}
//	//SDL_RenderDrawLine(renderer, prevX, prevY, x, y);
//	SDL_SetRenderTarget(renderer, NULL);
//	Application::GetInstance()->GetCanvas()->Render();
//
//	prevX = x; 
//	prevY = y;
//}

void Eraser::Erase(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color defaultBackgroundColor)
{
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();
	if (prevX == -1 || prevY == -1)
	{
		prevX = x;
		prevY = y;
		return;
	}
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, defaultBackgroundColor.r, defaultBackgroundColor.g, defaultBackgroundColor.b, 255);

	SDL_Rect eraserRect; 
	eraserRect.h = 10; 
	eraserRect.w = 10; 

	for (int i = -3; i < 3; i++)
	{
		eraserRect.x = x - eraserRect.w / 2 + i;
		eraserRect.y = y - eraserRect.h / 2 + i;
		SDL_RenderFillRect(renderer, &eraserRect);
	}
	SDL_SetRenderTarget(renderer, NULL);
	Application::GetInstance()->GetCanvas()->Render();

	prevX = x;
	prevY = y;
}

void Brush::Draw(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color currentSelectedColor)
{
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();
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
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, currentSelectedColor.r, currentSelectedColor.g, currentSelectedColor.b, 255);

	for (int i = 0; i < 1; i++)
	{
		int offsetX = rand() % 4 - 2; // Randomized slight offset
		int offsetY = rand() % 4 - 2;
		DrawCrayonStroke(renderer, x, y,50, currentSelectedColor);
	}

	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL);
	Application::GetInstance()->GetCanvas()->Render();
	prevX = x;
	prevY = y;
}
//void Brush::Draw(SDL_Renderer* renderer, SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color currentSelectedColor)
//{
//
//	if (texture == nullptr)
//	{
//		std::cout << "texture in brush draw is null" << std::endl;
//	}
//	if (prevX == -1 || prevY == -1)
//	{
//		prevX = x;
//		prevY = y;
//		return;
//	}
//	SDL_SetRenderTarget(renderer, texture);
//	SDL_SetRenderDrawColor(renderer, currentSelectedColor.r, currentSelectedColor.g, currentSelectedColor.b, 255);
//
//	int steps = 1;
//	for (int i = 0; i <= steps; i++)
//	{
//		int interpX = prevX + (x - prevX) * i / steps;	
//		int interpY = prevY + (y - prevY) * i / steps;	
//
//		int brushRadius = 5;
//		float noiseScale = 0.1f;
//		float noiseThreshold = 0.1f;
//		DrawNoiseBrush(renderer, interpX, interpY, brushRadius, noiseScale, noiseThreshold);
//	}
//
//	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL);
//	Application::GetInstance()->GetCanvas()->Render();
//	prevX = x;
//	prevY = y;
//}


float Brush::GetSimpleNoise(float x, float y)
{ 
	return(std::sin(x) * cos(y) + 1.0f) / 2.0f;
}
void Brush::DrawNoiseBrush(SDL_Renderer* renderer, int centreX, int centreY, int radius, float noiseScale, float threshold)
{
	for (int dy = -radius; dy <= radius; ++dy)
	{
		for (int dx = -radius; dx <= radius; ++dx)
		{
			float noiseValue = GetSimpleNoise((centreX + dx) * noiseScale, (centreY + dy) * noiseScale);
			if (noiseValue < threshold)
			{
				SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
			}
		}
	}
}
//void Brush::DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius)
//{
//	int offsetX = 0;
//	int offsetY = radius;
//	int d = 1 - radius;
//
//	while (offsetY >= offsetX)
//	{
//		// Draw points for each octant
//		SDL_RenderDrawPoint(renderer, centreX + offsetX, centreY + offsetY);
//		SDL_RenderDrawPoint(renderer, centreX + offsetY, centreY + offsetX);
//		SDL_RenderDrawPoint(renderer, centreX - offsetX, centreY + offsetY);
//		SDL_RenderDrawPoint(renderer, centreX - offsetY, centreY + offsetX);
//		SDL_RenderDrawPoint(renderer, centreX + offsetX, centreY - offsetY);
//		SDL_RenderDrawPoint(renderer, centreX + offsetY, centreY - offsetX);
//		SDL_RenderDrawPoint(renderer, centreX - offsetX, centreY - offsetY);
//		SDL_RenderDrawPoint(renderer, centreX - offsetY, centreY - offsetX);
//
//		if (d < 0)
//		{
//			d += 2 * offsetX + 3;
//		}
//		else
//		{
//			d += 2 * (offsetX - offsetY) + 5;
//			offsetY--;
//		}
//		offsetX++;
//	}
//}

void Brush::DrawCrayonStroke(SDL_Renderer* renderer, int centreX, int centreY, int radius, SDL_Color color)
{
	
	int density = 100;  // Increase this number for a more filled effect

	for (int i = 0; i < density; i++)
	{
		// Generate a random offset for the point relative to the center.
		int dx = rand() % (2 * radius + 1) - radius;
		int dy = rand() % (2 * radius + 1) - radius;

		// Optionally constrain the random points to a circular region, so points lie only within a circle.
		if (dx * dx + dy * dy <= radius * radius)
		{
			
			Uint8 alpha = 150 + rand() % 106; // 150 to 255

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
			SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
		}
	}
}
