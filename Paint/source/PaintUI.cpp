#include</Programming/Paint/Paint/headers/PaintUI.h>
#include</Programming/Paint/Paint/headers/Application.h>

PaintUI::PaintUI()
{
	LoadFont();
	SetFontColor();
	InitializeMenuList();	
}
void PaintUI::InitializeMenuList()
{
	/*toolMap =
	{
		{SDLK_q,"Pencil"},
		{SDLK_w,"Eraser"},
		{SDLK_w,"Brush"}
	};*/

	menulist[0] = "Drawing Pencil:  Q <-";
	menulist[1] = "Erasing Tool:     W";
	menulist[2] = "Curvy Shapes:   E";
}
void PaintUI::RenderMenuList()
{
	int yOffset = 20;
	for (int i = 0; i < 3; i++)
	{
		SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, menulist[i].c_str(), m_fontColor);
		if (!textSurface)
		{
			std::cout << "textu surface is null" << std::endl;
			return;
		}
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Application::GetInstance()->GetRenderer(), textSurface);
		SDL_Rect textRect = {20, yOffset, textSurface->w, textSurface->h}; 
		SDL_RenderCopy(Application::GetInstance()->GetRenderer(), textTexture, NULL, &textRect);
		yOffset += 25; // Add vertical space for the next menu item
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
}
void PaintUI::SetFontColor()
{
	m_fontColor = { 120,120,120 };
}

void PaintUI::LoadFont()
{
	m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handjet/Handjet-Regular.ttf", 20);
	if (m_font == nullptr)
	{
		std::cout << "font is not initialized" << std::endl;
	}
}