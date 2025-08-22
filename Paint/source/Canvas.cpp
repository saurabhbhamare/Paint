#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/Application.h>
#include<SDL.h>

Canvas::Canvas()
{
	m_prevX = -1;
	m_prevY = -1;

	InitializeDrawingTools();
	CreateCanvasTexture();
	currentActiveTool = ToolType::PENCIL;
	//CreateBackgroundTexture();
	Fill();
	m_currentSelectedColor = { 0,0,0,255 };
	m_defaultCanvasColour = { 220,220,220,255 };
	m_paletteColors = new std::map<std::string, SDL_Color>;
	SetColorPalleteColors();
}
void Canvas::InitializeDrawingTools()
{
	pencil = new Pencil();
	eraser = new Eraser();
	brush = new Brush();

	currentTool = pencil;
}
void Canvas::SaveCanvasState()
{
	int width = Application::GetInstance()->SCREEN_WIDTH;
	int height = Application::GetInstance()->SCREEN_HEIGHT;
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();
	SDL_Texture* snapshot = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetRenderTarget(renderer, snapshot);
	SDL_RenderCopy(renderer, m_texture, NULL, NULL);
	canvasStateUndoStack.push(snapshot);
	std::cout << "Size of undostack is :" << canvasStateUndoStack.size() << std::endl;
}
void Canvas::RevertLastAction()
{
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();
	int width = Application::GetInstance()->SCREEN_WIDTH;
	int height = Application::GetInstance()->SCREEN_HEIGHT;
	
	if (!canvasStateUndoStack.empty()) 
	{
		SDL_Texture* lastState = canvasStateUndoStack.top();
		canvasStateUndoStack.pop();

		SDL_Texture* currentState = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

		SDL_SetRenderTarget(renderer, currentState);
		SDL_RenderCopy(renderer, m_texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);

		canvasStateRedoStack.push(currentState);
		

		SDL_SetRenderTarget(renderer, m_texture);
		SDL_RenderCopy(renderer, lastState, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_DestroyTexture(lastState);
		SDL_RenderPresent(renderer);
	}
	
}
void Canvas::RestoreLastAction()
{
	SDL_Renderer* renderer = Application::GetInstance()->GetRenderer();
	int width = Application::GetInstance()->SCREEN_WIDTH;
	int height = Application::GetInstance()->SCREEN_HEIGHT;

	if (!canvasStateRedoStack.empty())
	{
		SDL_Texture* nextState = canvasStateRedoStack.top();
		canvasStateRedoStack.pop();

		SDL_Texture* redoCopy = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

		SDL_SetRenderTarget(renderer, redoCopy);
		SDL_RenderCopy(renderer, m_texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);

		canvasStateUndoStack.push(redoCopy);

		SDL_SetRenderTarget(renderer, m_texture);
		SDL_RenderCopy(renderer, nextState, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_DestroyTexture(nextState);
		SDL_RenderPresent(renderer);
	}
}

void Canvas::CreateBackgroundTexture()
{
	SDL_Surface* backgroundSurface = SDL_LoadBMP("C:/Programming/Paint/Paint/images/PaperTexture.bmp");
	m_texture = SDL_CreateTextureFromSurface(Application::GetInstance()->GetRenderer(), backgroundSurface);
	SDL_FreeSurface(backgroundSurface);
	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), m_texture);
	SDL_RenderClear(Application::GetInstance()->GetRenderer());
	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL);
	SDL_RenderCopy(Application::GetInstance()->GetRenderer(), m_texture, NULL, NULL);
}
void Canvas::SaveCanvasFile(const char* filename,int width , int height)
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
	int width = Application::GetInstance()->SCREEN_WIDTH;
	int height = Application::GetInstance()->SCREEN_HEIGHT;

	m_texture = SDL_CreateTexture(Application::GetInstance()->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (m_texture == nullptr)
	{
		std::cout << "mtexture is null" << std::endl;
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
		pencil->Draw(m_texture, m_prevX, m_prevY, x, y,m_currentSelectedColor);
		break;
	case ToolType::ERASER: 
		eraser->Erase(m_texture, m_prevX, m_prevY, x, y, m_defaultCanvasColour);
		break;
	case ToolType::BRUSH:
		brush->Draw(m_texture, m_prevX, m_prevY, x, y, m_currentSelectedColor);
		break;
	}
}
void Canvas::ResizeDrawingTool()
{
	
}
void Canvas::Render()
{
	SDL_RenderCopy(Application::GetInstance()->GetRenderer(), m_texture, NULL, NULL);
}
void Canvas::DrawLineBetweenTwoPoints(int x, int y)
{
	int dx = abs(x - m_prevX); 
	int dy = abs(y - m_prevY);

	int sx = (m_prevX > x) ? 1 : -1;
	int sy = (m_prevY > y) ? 1 : -1;
	int err = dx - dy;
	SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), m_currentSelectedColor.r, m_currentSelectedColor.g, m_currentSelectedColor.b, m_currentSelectedColor.a);
	
	while (true)
	{
		SDL_RenderDrawPoint(Application::GetInstance()->GetRenderer(), x, y);
		if (x == m_prevX && y == m_prevY) break;
		
		int e2 = err * 2;
		if (e2 > -dy) { err -= dy; x+= sx; }
		if (e2 > -dx) { err -= dx; y+= sy; }
	}
	m_prevX = x; 
	m_prevY = y;
}
void Canvas::Fill()
{
	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), m_texture);
	SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), 220, 220, 220, 255);
	SDL_RenderClear(Application::GetInstance()->GetRenderer());
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