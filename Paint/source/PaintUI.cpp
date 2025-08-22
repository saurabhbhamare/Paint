#include</Programming/Paint/Paint/headers/PaintUI.h>
#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/Application.h>

PaintUI::PaintUI()
{
	ImportToolIconImages();
	LoadFont();
	SetFontColor();
	InitializeMenuList();
	LoadSDLCursor();
	InitializeCursor();
	LoadColorPointerArrow();
	CreateMenuTextures();
	
	RenderMenuList();
	//FreeMenuSurfaces();

}
void PaintUI::InitializeMenuList()
{
	menulist[0] = "Drawing Pencil:    Q";
	/*menulist[1] = "Press W For Erasing Tool";
	menulist[2] = "Press E For Color Filling";
	menulist[3] = "Press S For Saving Canvas";
	menulist[4] = "Press R For Color Palette";
	menulist[5] = "Press Esq For Close Paint";
	menulist[6] = "Press Y For Magic Brush";*/
	menulist[1] = "Magic Brush:      W";
	menulist[2] = "Erasing Tool:     E";
	menulist[3] = "Fill Colour:      R";
	menulist[4] = "Save Canvas:      T";
	menulist[5] = "Colour Palette:   P";
	menulist[7] = "Increase Tool:    +   ";
	menulist[8] = "Decrease Tool:    -   ";
	menulist[9] = "Close Paint:      esc";
	menulist[10] = "Import Image:  1   ";
	menulist[11] = "Spray Paint:  esc   ";
	menulist[12] = "Text Creation:  esc   ";
	menulist[13] = "Menu Toggle:  M   ";
	menulist[14] = "Line Feature:  esc   ";
	menulist[15] = "Curve Feature:  esc   ";
	menulist[16] = "Paint Size:  esc   ";
	menulist[17] = "Font Switching:  esc   ";
	menulist[18] = "Color Switching:  esc   ";
	menulist[19] = "Color Mixing:  esc   ";
} 
void PaintUI::SetFontColor()
{
	m_fontColor = { 0,0,0 };
}

void PaintUI::LoadFont()
{
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handjet/Handjet-Regular.ttf", 24);
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handwritten/PWSimpleHandwriting.ttf", 20);
	m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handwritten/gabiie_s handwritting.ttf", 18);
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/roboto/Roboto-Regular.ttf", 18);
	//m_font = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/segoeui/segoeui.ttf", 25);
	if (m_font == nullptr)
	{
		std::cout << "font is not initialized" << std::endl;
	}
}
void PaintUI::LoadSDLCursor()
{/*
	m_arrowSurface = SDL_LoadBMP("C:/Programming/Paint/Paint/images/pencilwithshadow.bmp");
	if (m_arrowSurface == nullptr)
	{
		std::cout << "failed to get the pencil arrow image in loadSDlCursor" << std::endl;
	}*/
	m_cursor = SDL_CreateColorCursor(m_pencilIcon, 40,40);

	if (m_cursor == nullptr)
	{
		std::cout << "m_cursor is null in losdsdlcurso" << std::endl;
	}
}
void PaintUI::InitializeCursor()
{
	/*m_cursor = SDL_CreateColorCursor(m_arrowSurface, 16, 16);
	if (m_cursor == nullptr)
	{
		std::cout << "failed to create the cursor" << std::endl;
	}*/
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
		
		SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(Application::GetInstance()->GetRenderer(), &box);
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
void PaintUI::ImportToolIconImages()
{
	m_pencilIcon = SDL_LoadBMP("C:/Programming/Paint/Paint/images/Square.bmp");
	if (m_pencilIcon == nullptr)
	{
		std::cout << "pencil Icon is not loaded" << std::endl;
	}
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
void PaintUI::CreateMenuTexture()
{
	m_menuTexture = SDL_CreateTexture(Application::GetInstance()->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1200, 700);
}

void PaintUI::CreateMenuTextures()
{
	for (int i = 0; i < 20; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Blended(m_font, menulist[i].c_str(), m_fontColor);
		if (menuSurfaces[i] == nullptr)
		{
			std::cout << "text surface is null " << std::endl;

		}
		menuTextures[i] = SDL_CreateTextureFromSurface(Application::GetInstance()->GetRenderer(), menuSurfaces[i]);
	}
	
}
void PaintUI::RenderMenuList()
{
	std::cout << "rendering the menulist" << std::endl;
	if (!isMenuVisible) return;
	
	RenderMenuBackground();
	SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), m_menuTexture);
	//SDL_RenderClear(Application::GetInstance()->GetRenderer());
		int yOffSet = 50;
		for (int i = 0; i < 10; i++)
		{
			if (menuTextures[i])
			{
				SDL_Rect textRect = {40,yOffSet,menuSurfaces[i]->w,19 };
				//SDL_Rect textRect = {40,yOffSet,menuSurfaces[i]->w,34 };
				
				SDL_RenderCopy(Application::GetInstance()->GetRenderer(), menuTextures[i], NULL, &textRect);
				yOffSet += 30;
			}

		}
		SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), NULL); // Reset back to default
}
void PaintUI::FreeMenuSurfaces()
{
	for (int i = 0; i < 20; i++)
	{
		SDL_FreeSurface(menuSurfaces[i]);
	}
}
void PaintUI::RenderMenuBackground()
{
	/*SDL_Rect menuRect = { 20,20,1160,600 };
	SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Application::GetInstance()->GetRenderer(), &menuRect)*/;

}
void PaintUI::ClearMenuArea()
{
	std::cout << "clear menu area called" << std::endl;
	// Set clear color to match the canvas background
	
	
	
	SDL_SetRenderDrawColor(Application::GetInstance()->GetRenderer(), 255, 255, 255, 255); // White background
	SDL_Rect menuRect = { 20, 10, 800, 600 }; // Same size as the menu background
	SDL_RenderFillRect(Application::GetInstance()->GetRenderer(), &menuRect);
	Application::GetInstance()->GetCanvas()->Render();
	SDL_RenderPresent(Application::GetInstance()->GetRenderer()); // Refresh screen
	//SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), Application::GetInstance()->GetCanvas()->m_texture);
}
void PaintUI::HideMenu()
{

}
