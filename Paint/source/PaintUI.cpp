#include</Programming/Paint/Paint/headers/PaintUI.h>
#include</Programming/Paint/Paint/headers/Application.h>

PaintUI::PaintUI()
{
	LoadFont();
	SetFontColor();
	InitializeMenuList();
	LoadSDLCursor();
	InitializeCursor();
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
void PaintUI::ShowColourPallete(SDL_Renderer* renderer)
{
	SDL_Color colours[40] = {
	   {255, 0, 0, 255},    // Red
	   {0, 255, 0, 255},    // Green
	   {0, 0, 255, 255},    // Blue
	   {255, 255, 0, 255},  // Yellow
	   {0, 255, 255, 255},  // Cyan
	   {255, 0, 255, 255},  // Magenta
	   {255, 165, 0, 255},  // Orange
	   {128, 0, 128, 255},  // Purple
	   {255, 192, 203, 255},// Pink
	   {139, 69, 19, 255},  // Brown
	   {128, 128, 128, 255},// Gray
	   {255, 255, 255, 255},// White
	   {0, 0, 0, 255},      // Black
	   {173, 216, 230, 255},// Light Blue
	   {0, 100, 0, 255},    // Dark Green
	   {245, 245, 220, 255},// Beige
	   {64, 224, 208, 255}, // Turquoise
	   {230, 230, 250, 255},// Lavender
	   {255, 215, 0, 255},  // Gold
	   {192, 192, 192, 255},// Silver
	   {128, 0, 0, 255},    // Maroon
	   {0, 128, 0, 255},    // Forest Green
	   {0, 0, 128, 255},    // Navy Blue
	   {128, 128, 0, 255},  // Olive
	   {0, 128, 128, 255},  // Teal
	   {128, 0, 128, 255},  // Indigo
	   {255, 99, 71, 255},  // Tomato
	   {255, 69, 0, 255},   // Red Orange
	   {240, 230, 140, 255},// Khaki
	   {210, 180, 140, 255},// Tan
	   {75, 0, 130, 255},   // Dark Indigo
	   {255, 250, 250, 255},// Snow White
	   {222, 184, 135, 255},// Burlywood
	   {72, 61, 139, 255},  // Dark Slate Blue
	   {123, 104, 238, 255},// Medium Slate Blue
	   {255, 239, 213, 255},// Peach Puff
	   {250, 128, 114, 255},// Salmon
	   {102, 205, 170, 255},// Medium Aquamarine
	   {240, 128, 128, 255},// Light Coral
	   {189, 183, 107, 255} // Dark Khaki
	};


	int boxSize = 20; 
	int x = 0; 
	int y = 630;

	for (int i = 0; i < 40; i++)
	{
		SDL_Rect box = { x,y,40,80 };
		SDL_SetRenderDrawColor(renderer, colours[i].r, colours[i].g, colours[i].b, colours[i].a);
		SDL_RenderFillRect(renderer, &box);
		x += 30;
	}
}