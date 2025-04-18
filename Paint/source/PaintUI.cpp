#include</Programming/Paint/Paint/headers/PaintUI.h>
#include</Programming/Paint/Paint/headers/Application.h>

PaintUI::PaintUI()
{
	LoadFont();
	SetFontColor();
	InitializeMenuList();
	LoadSDLCursor();
	InitializeCursor();
	LoadColorPointerArrow();
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
	menulist[1] = "Magic Brush:     W";
	menulist[2] = "Erasing Tool:     E";
	menulist[3] = "Fill Colour:   R";
	menulist[4] = "Save Canvas:   T";
	menulist[5] = "Colour Pallete:   ";
	menulist[6] = "Close Paint:  esc   ";

}
void PaintUI::RenderMenuList()
{
	int yOffset = 20;
	for (int i = 0; i < 7; i++)
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
	SDL_SetCursor(m_cursor);
}
void PaintUI::SetFontColor()
{
	m_fontColor = { 120,120,120 };
}

void PaintUI::LoadFont()
{
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handjet/Handjet-Regular.ttf", 20);
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handwritten/PWSimpleHandwriting.ttf", 20);
	m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handwritten/gabiie_s handwritting.ttf", 16);
	if (m_font == nullptr)
	{
		std::cout << "font is not initialized" << std::endl;
	}
}
void PaintUI::LoadSDLCursor()
{
	m_arrowSurface = SDL_LoadBMP("C:/Programming/Paint/Paint/images/pencilwithshadow.bmp");
	if (m_arrowSurface == nullptr)
	{
		std::cout << "failed to get the pencil arrow image in loadSDlCursor" << std::endl;
	}
}
void PaintUI::InitializeCursor()
{
	m_cursor = SDL_CreateColorCursor(m_arrowSurface, 16, 16);
	if (m_cursor == nullptr)
	{
		std::cout << "failed to create the cursor" << std::endl;
	}
}
void PaintUI::ShowColourPallete(SDL_Renderer* renderer,std::map<std::string,SDL_Color>*colorPalette)
{
	int boxSize = 20; 
	int x = 0; 
	int y = 640;
	
	for (const auto& pair : *colorPalette)
	{
		SDL_Color color = pair.second;
		SDL_Rect box = { x,y,40,80 };
		
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &box);
		x += 30;
	}
	
}
SDL_Color PaintUI::PickColorFromPaletteUI(int mPosX , int mPosY, std::map<std::string, SDL_Color>* colorPalette,SDL_Color &color)
{
	int x = 0;
	int y = 640;
	ShowColorPointerArrow(x, y);

	/*std::cout << "mPosX in PickColor" << mPosX << std::endl;
	std::cout << "mPosY in PickColor" << mPosY << std::endl;*/

	
	for (const auto& pair : *colorPalette)
	{
		SDL_Rect box = { x,y,40,80 };
		if (mPosX >= box.x && mPosX<= box.x + box.w && mPosY >= box.y && mPosY <= box.y + box.h)
		{
			std::cout << "Current Selected Color" << pair.first << std::endl;
			color = pair.second;
			return pair.second;
		}
		x += 30;
	}
	return { 0, 0, 0, 255 };
}
void PaintUI::LoadColorPointerArrow()
{
	colorPointerArrow = SDL_LoadBMP("C:/Programming/Paint/Paint/images/handdrawnarrowpalette1.bmp");
	if (colorPointerArrow == nullptr)
	{
		std::cout << "color pointer arrow is null in loadcolorPOInterarrow" << std::endl;
	}
}
void PaintUI :: ShowColorPointerArrow(int x, int y)
{

}
