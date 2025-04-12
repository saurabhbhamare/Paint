//
//// Trying to make Fake Paint 
//
//#include <iostream>
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <map>
//#include <stack>
//
//enum Tool
//{
//	PENCIL,
//	ERASER
//};
//enum Colour
//{
//	RED,
//	BLUE,
//	GREEN
//};
//
//static int prevX = -1;
//static int prevY = -1;
//
//static Tool selectedTool = Tool::ERASER;
//
//static std::map<SDL_Surface*, std::string> drawingTools;
//
//
//void SaveFileToTheDirectory(SDL_Surface* surface)
//{
//
//}
//void ShowMenuList()
//{
//
//}
//void ShowColourSelectionPalette()
//{
//
//}
//void SetDrawingToolsCursors()
//{
//	//	drawingTools.insert()
//}
//void SwitchDrawingTool(SDL_Cursor* cursor, Tool currentSelectedTool)
//{
//	if (currentSelectedTool == Tool::PENCIL)
//	{
//
//	}
//}
//void FillColour(SDL_Surface* surface, SDL_Colour* colour)
//{
//
//}
//
//void UpdatePixelValue(SDL_Surface* surface, int x, int y)
//{
//
//	SDL_LockSurface(surface);
//
//	uint8_t* pixelArray = (uint8_t*)surface->pixels;
//	pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 0] = 244;
//	pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = 244;
//	pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = 244;
//
//	SDL_UnlockSurface(surface);
//}
//
//void DrawLineBetweenTwoPoints(SDL_Surface* surface, int x1, int y1, int x2, int y2)
//{
//	SDL_LockSurface(surface);
//
//	uint8_t* pixelArray = (uint8_t*)surface->pixels;
//	//uint16_t* pixelArray = (uint16_t*)surface->pixels;
//	int dx = abs(x2 - x1);
//	int dy = abs(y2 - y1);
//	int sx = (x1 < x2) ? 1 : -1;
//	int sy = (y1 < y2) ? 1 : -1;
//	int err = dx - dy;
//
//	while (true)
//	{
//		if (x1 >= 0 && x1 < surface->w && y1 >= 0 && y1 < surface->h)
//		{
//			uint8_t* pixel = (uint8_t*)pixelArray + (y1 * surface->pitch) + (x1 * surface->format->BytesPerPixel);
//			//uint16_t* pixel = (uint16_t*) pixelArray+(y1* surface->pitch) + (x1 * surface->format->BytesPerPixel);
//			pixel[0] = 80;
//			pixel[1] = 60;
//			pixel[2] = 200;
//		}
//		if (x1 == x2 && y1 == y2) break;
//		int e2 = 2 * err;
//		if (e2 > -dy) { err -= dy; x1 += sx; }
//		if (e2 < dx) { err += dx; y1 += sy; }
//	}
//	SDL_UnlockSurface(surface);
//}
//
//void Erase(SDL_Surface* surface, int x1, int y1, int x2, int y2, int size)
//{
//	SDL_LockSurface(surface);
//
//	uint8_t* pixelArray = (uint8_t*)surface->pixels;
//	//uint16_t* pixelArray = (uint16_t*)surface->pixels;
//	int dx = abs(x2 - x1);
//	int dy = abs(y2 - y1);
//	int sx = (x1 < x2) ? 1 : -1;
//	int sy = (y1 < y2) ? 1 : -1;
//	int err = dx - dy;
//
//	while (true)
//	{
//		if (x1 >= 0 && x1 < surface->w && y1 >= 0 && y1 < surface->h)
//		{
//			uint8_t* pixel = (uint8_t*)pixelArray + (y1 * surface->pitch) + (x1 * surface->format->BytesPerPixel);
//			//uint16_t* pixel = (uint16_t*) pixelArray+(y1* surface->pitch) + (x1 * surface->format->BytesPerPixel);
//			pixel[0] = 220;
//			pixel[1] = 220;
//			pixel[2] = 220;
//		}
//		if (x1 == x2 && y1 == y2) break;
//		int e2 = 2 * err;
//		if (e2 > -dy) { err -= dy; x1 += sx; }
//		if (e2 < dx) { err += dx; y1 += sy; }
//	}
//	SDL_UnlockSurface(surface);
//
//}
//
//int main(int argc, char* argv[])
//{
//	// Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) != 0)
//	{
//		std::cerr << "Error: SDL_Init failed: " << SDL_GetError() << std::endl;
//		return -1;
//	}
//
//	//SDL_TTF and Font Input
//
//
//	if (TTF_Init() != 0)
//	{
//		std::cout << "SDL TTF is not initialized" << std::endl;
//	}
//
//	//
//	
//
//	
//
//	// Create SDL window
//	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 700, SDL_WINDOW_SHOWN);
//	if (!window)
//	{
//		std::cerr << "Error: SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		return -1;
//	}
//
//	SDL_Surface* pencilCursor = SDL_LoadBMP("C:/Programming/Paint/Paint/images/pencil40.bmp");
//	SDL_Surface* eraserCursor = SDL_LoadBMP("C:/Programming/Paint/Paint/images/Eraser2.bmp");
//
//	if (pencilCursor == nullptr)
//	{
//		std::cout << "cursor is nullptr" << std::endl;
//	}
//
//	SDL_Cursor* cursor1 = SDL_CreateColorCursor(pencilCursor, 16, 16);
//	SDL_Cursor* cursor2 = SDL_CreateColorCursor(eraserCursor, 16, 16);
//
//	if (cursor1 == nullptr)
//	{
//		std::cout << "failed to load the cursor" << std::endl;
//	}
//	if (cursor2 == nullptr)
//	{
//		std::cout << "failed to load the cursor" << std::endl;
//	}
//	SDL_SetCursor(cursor1);
//
//
//
//	//Font Input
//
//	TTF_Font* font1 = TTF_OpenFont("C:/Programming/Paint/Paint/fonts/handjet/Handjet-Regular.ttf", 16);
//
//	SDL_Colour fontColour = { 0,0,0 };
//
//
//	if (font1 == nullptr)
//	{
//		std::cout << "failed to get the handjet font" << std::endl;
//	}
//
//	SDL_Surface* fontSurface1 = TTF_RenderText_Solid(font1, " Drawing Pencil:  Q <-", fontColour);
//	SDL_Surface* fontSurface2 = TTF_RenderText_Solid(font1, " Erasing Tool:     W", fontColour);
//	SDL_Surface* fontSurface3 = TTF_RenderText_Solid(font1, " Curvy Shapes:   E", fontColour);
//	SDL_Surface* fontSurface4 = TTF_RenderText_Solid(font1, " Page Rotation:   R", fontColour);
//	if (fontSurface1 != 0)
//	{
//		std::cout << "font surface is null" << std::endl;
//	}
//	
//
//	// Create SDL renderer
//	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (!renderer)
//	{
//		std::cerr << "Error: SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
//		SDL_DestroyWindow(window);
//		SDL_Quit();
//		return -1;
//	}
//	SDL_Surface* screen = SDL_GetWindowSurface(window);
//
//	Uint32 whiteColour = SDL_MapRGB(screen->format, 220, 220, 220);
//
//	SDL_FillRect(screen, NULL, whiteColour);
//	SDL_UpdateWindowSurface(window);
//
//	if (screen == nullptr)
//	{
//		std::cout << "screen pointer is null";
//	}
//	SDL_Rect* rect1 = new SDL_Rect{ 40,40,4,124 };
//	SDL_Rect* rect2 = new SDL_Rect{ 40,60,4,124 };
//	SDL_Rect* rect3 = new SDL_Rect{ 40,80,4,124 };
//	SDL_Rect* rect4 = new SDL_Rect{ 40,100,4,124 };
//
//	SDL_BlitSurface(fontSurface1, NULL, screen,rect1);
//	SDL_BlitSurface(fontSurface2, NULL, screen,rect2);
//	SDL_BlitSurface(fontSurface3, NULL, screen,rect3);
//	SDL_BlitSurface(fontSurface4, NULL, screen,rect4);
//	//SDL_BlitSurface(fontSurface4,, screen,);
//	SDL_UpdateWindowSurface(window);
//
//	// Main loop
//	bool running = true;
//	SDL_Event event;
//	while (running)
//	{
//		// Handle events
//
//		if (selectedTool == Tool::PENCIL)
//		{
//			SDL_SetCursor(cursor1);
//		}
//		else if (selectedTool == Tool::ERASER)
//		{
//			SDL_SetCursor(cursor2);
//		}
//		//SDL_SetCursor(cursor1);
//		while (SDL_PollEvent(&event))
//		{
//
//			//check for tool switch
//
//
//			if (event.type == SDL_KEYDOWN)
//			{
//				if (event.key.keysym.sym == SDLK_1)
//				{
//					selectedTool = Tool::PENCIL;
//				}
//				if (event.key.keysym.sym == SDLK_2)
//				{
//					selectedTool = Tool::ERASER;
//				}
//			}
//
//			//ImGui_ImplSDL2_ProcessEvent(&event);
//
//			int x, y;
//			SDL_GetMouseState(&x, &y);
//			/*std::cout << "X " << x << std::endl;
//			std::cout << "Y " << y << std::endl;*/
//
//			if (event.type == SDL_QUIT)
//			{
//				running = false;
//			}
//			if (event.type == SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
//			{
//				if (prevX != -1 && prevY != -1)
//				{
//					if (selectedTool == Tool::PENCIL)
//					{
//						DrawLineBetweenTwoPoints(screen, prevX, prevY, x, y);
//					}
//					else if (selectedTool == Tool::ERASER)
//					{
//						Erase(screen, prevX, prevY, x, y, 10);
//					}
//
//
//					//UpdatePixelValue(screen, x, y);
//				}
//			}
//
//			prevX = x;
//			prevY = y;
//			SDL_UpdateWindowSurface(window);
//		}
//	
//	}
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////PREV IMPLEMENTATION
//
