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
	m_paletteColors = new std::map<std::string,SDL_Color>;
	SetColorPalleteColors();
}
void Canvas::InitializeDrawingTools()
{
	pencil = new Pencil();
	eraser = new Eraser();

	currentTool = pencil;
}

void Canvas::SaveCanvas(const char* filename,int width , int height)
{
	//std::cout << "in save canvas" << std::endl;
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
		std::cout << "error while saving canvas" << std::endl;
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
void Canvas::HandleMouseClick(int mouseX, int mouseY)
{
	std::cout << "Pointer X : " << mouseX << std::endl;
	std::cout << "Pointer Y : " << mouseY << std::endl;
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
void Canvas::SetColorPalleteColors()
{
	m_paletteColors->insert({ "Red",            {255, 0, 0, 255} });
	m_paletteColors->insert({ "Yellow",         {255, 255, 0, 255} });
	m_paletteColors->insert({ "Green",          {0, 255, 0, 255} });
	m_paletteColors->insert({ "1Blue",           {0, 0, 255, 255} });
	m_paletteColors->insert({ "Cyan",           {0, 255, 255, 255} });
	m_paletteColors->insert({ "Magenta",        {255, 0, 255, 255} });
	m_paletteColors->insert({ "Orange",         {255, 165, 0, 255} });
	m_paletteColors->insert({ "Purple",         {128, 0, 128, 255} });
	m_paletteColors->insert({ "Pink",           {255, 192, 203, 255} });
	m_paletteColors->insert({ "Brown",          {139, 69, 19, 255} });
	m_paletteColors->insert({ "Gray",           {128, 128, 128, 255} });
	m_paletteColors->insert({ "3White",          {255, 255, 255, 255} });
	m_paletteColors->insert({ "2Black",          {0, 0, 0, 255} });
	m_paletteColors->insert({ "Light Blue",     {173, 216, 230, 255} });
	m_paletteColors->insert({ "Dark Green",     {0, 100, 0, 255} });
	m_paletteColors->insert({ "Cream",          {245, 245, 220, 255} });
	m_paletteColors->insert({ "Turquoise",      {64, 224, 208, 255} });
	m_paletteColors->insert({ "Lavender",       {230, 230, 250, 255} });
	m_paletteColors->insert({ "Gold",           {255, 215, 0, 255} });
	m_paletteColors->insert({ "Silver",         {192, 192, 192, 255} });
	m_paletteColors->insert({ "Maroon",         {128, 0, 0, 255} });
	m_paletteColors->insert({ "Forest Green",   {0, 128, 0, 255} });
	m_paletteColors->insert({ "Navy Blue",      {0, 0, 128, 255} });
	m_paletteColors->insert({ "Olive",          {128, 128, 0, 255} });
	m_paletteColors->insert({ "Teal",           {0, 128, 128, 255} });
	m_paletteColors->insert({ "Indigo",         {128, 0, 128, 255} });
	m_paletteColors->insert({ "Tomato",         {255, 99, 71, 255} });
	m_paletteColors->insert({ "Red Orange",     {255, 69, 0, 255} });
	m_paletteColors->insert({ "Khaki",          {240, 230, 140, 255} });
	m_paletteColors->insert({ "Dark Indigo",    {75, 0, 130, 255} });
	m_paletteColors->insert({ "Snow White",     {255, 250, 250, 255} });
	m_paletteColors->insert({ "Tan",            {210, 180, 140, 255} });
	m_paletteColors->insert({ "Burlywood",      {222, 184, 135, 255} });
	m_paletteColors->insert({ "Dark Slate Blue",{72, 61, 139, 255} });
	m_paletteColors->insert({ "Medium Slate Blue",{123, 104, 238, 255} });
	m_paletteColors->insert({ "Peach Puff",     {255, 239, 213, 255} });
	m_paletteColors->insert({ "Salmon",         {250, 128, 114, 255} });
	m_paletteColors->insert({ "Medium Aquamarine",{102, 205, 170, 255} });
	m_paletteColors->insert({ "Light Coral",    {240, 128, 128, 255} });
	m_paletteColors->insert({ "Dark Khaki",     {189, 183, 107, 255} });
}

void Canvas::SetCurrentSelectedColor(SDL_Color color)
{
	m_currentSelectedColor = color;
}