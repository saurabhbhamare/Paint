#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/Application.h>
#include<SDL.h>

Canvas::Canvas(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_prevX = -1;
	m_prevY = -1;
	InitializeDrawingTools();
	currentActiveTool = ToolType::PENCIL;
	Fill();
	m_currentSelectedColor = { 0,0,0,255 };
}
void Canvas::InitializeDrawingTools()
{
	pencil = new Pencil();
	eraser = new Eraser();

	currentTool = pencil;
}

void Canvas::SaveCanvas(const char* filename,int width , int height)
{
	std::cout << "in save canvas" << std::endl;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (surface == nullptr)
	{
		std::cout << "Surface created in SaveCanvas is null" << std::endl;
		return;
	}
	if (SDL_RenderReadPixels(Application::GetInstance()->GetRenderer(), NULL, surface->format->format,surface->pixels, surface->pitch))
	{
		std::cout << "failed to read pixel data in SaveCanvas" << std::endl;
		SDL_FreeSurface(surface);
		return;
	}
	if (SDL_SaveBMP(surface, filename) != 0)
	{
		std::cout << "error while saving canvas " << std::endl;
	}
	else
	{
		std::cout << "file saved successfully" << std::endl;
	}
}
void Canvas::ResetPointerPosition()
{
	m_prevX = -1;
	m_prevY = -1;	
}
void Canvas::CreateCanvasTexture()
{
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1200, 700);
	if (m_texture == nullptr)
	{
		std::cout << "mtexture is null ptr" << std::endl;
	}
}
//void Canvas::SetInitialPoint(int x , int y )
//{
//	/*m_prevX = x; 
//	m_prevY = y;*/
//}

void Canvas::HandleMouseClick(int mouseX, int mouseY)
{
	std::cout << "Pointer X : " << mouseX << std::endl;
	std::cout << "Pointer Y : " << mouseY << std::endl;
}
void Canvas::Draw(int x, int y)
{
	if (m_prevX == -1 || m_prevY == -1)
	{
		// Set the starting point if the previous point is invalid
		m_prevX = x;
		m_prevY = y;
		return;
	}
	
		SDL_SetRenderTarget(m_renderer, m_texture);
		SDL_SetRenderDrawColor(m_renderer, 10, 140, 0, 255);
		SDL_RenderDrawLine(m_renderer, m_prevX, m_prevY, x, y);
		SDL_SetRenderTarget(m_renderer, NULL);
	

	m_prevX = x;
	m_prevY = y;
}
void Canvas::HandleDrawingTool(int x, int y)
{
	switch (currentActiveTool)
	{
	case ToolType::PENCIL:
		pencil->Draw(m_renderer, m_texture, m_prevX, m_prevY, x, y,m_currentSelectedColor);
		break;
	}
}
void Canvas::Erase(int x, int y )
{ 
	if (m_prevX == -1 || m_prevY == -1)
	{
		// Set the starting point if the previous point is invalid
		m_prevX = x;
		m_prevY = y;
		return;
	}

	SDL_SetRenderTarget(m_renderer, m_texture);
	SDL_SetRenderDrawColor(m_renderer, 220, 220, 220, 255);
	SDL_RenderDrawLine(m_renderer, m_prevX, m_prevY, x, y);
	SDL_SetRenderTarget(m_renderer, NULL);


	m_prevX = x;
	m_prevY = y;
}
void Canvas::ResizeDrawingTool()
{
	
}
void Canvas::Render()
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
}

void Canvas::Fill()
{
	SDL_SetRenderTarget(m_renderer, m_texture);
	SDL_SetRenderDrawColor(m_renderer, 220, 220, 220, 255);
	SDL_RenderClear(m_renderer);
	SDL_SetRenderTarget(m_renderer, NULL);
}
