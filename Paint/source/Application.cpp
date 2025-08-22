#include</Programming/Paint/Paint/headers/Application.h>
#include<iostream>

Application* Application::m_instance = nullptr;
Application::Application(){}

Application* Application::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Application;
	}
	return m_instance;
}
SDL_Window* Application::GetWindow() const
{
	return m_window;
}
SDL_Renderer* Application::GetRenderer() const
{
	return m_renderer;
}
void Application::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Error: SDL_Init failed: " << SDL_GetError() << std::endl;
		return;
	}
	if (TTF_Init() != 0)
	{
		std::cerr << "Error: TTF failed: " << TTF_GetError() << std::endl;
	}
	//window and renderer creation 
	m_window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (!m_window || !m_renderer)
	{
		std::cerr << "Error: Unable to create window or renderer"<< SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}
	//Canvas and UI crewation

	m_canvas = new Canvas();
	m_paintUI = new PaintUI();
	
}

void Application::Run()
{
	bool running = true;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.button.button ==  SDL_BUTTON_LEFT)
			{
				
				int mPosX;
				int mPosY;
				SDL_GetMouseState(&mPosX, &mPosY);
				//std::cout << "you clicked :" << mPosX <<" "<< mPosY << std::endl;
				//m_canvas->m_currentSelectedColor = m_paintUI->PickColorFromPaletteUI(mPosX, mPosY ,m_canvas->m_paletteColors);
			}
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
			{
				m_canvas->ResetPointerPosition();
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				m_canvas->SaveCanvasState();
			}
			if (event.type == SDL_KEYDOWN && (SDL_GetModState() & KMOD_CTRL) && event.key.keysym.sym == SDLK_z)
			{
				//if (event.type == SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) return;
				std::cout << "clicked z button";
				m_canvas->RevertLastAction();
				m_canvas->Render();
			}
			if (event.type == SDL_KEYDOWN && (SDL_GetModState() & KMOD_CTRL) && event.key.keysym.sym == SDLK_y)
			{
				std::cout << "clicked x button";
				m_canvas->RestoreLastAction();
				m_canvas->Render();
			}
			if (event.type == SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
			{
				int mPosX;
				int mPosY;

				
				SDL_GetMouseState(&mPosX, &mPosY);

				m_paintUI->PickColorFromPaletteUI(mPosX, mPosY, m_canvas->m_paletteColors, m_canvas->m_currentSelectedColor);

				//newer impl
				if (m_paintUI->isMenuVisible == true) continue;
				m_canvas->HandleDrawingTool(mPosX,mPosY);
				
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			{
				m_canvas->SaveCanvasFile("sketch.bmp",SCREEN_WIDTH,SCREEN_HEIGHT);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
			{
				m_paintUI->isMenuVisible = !m_paintUI->isMenuVisible;
				if (m_paintUI->isMenuVisible)
				{
					m_paintUI->RenderMenuList();
				}
				else
				{
					m_paintUI->ClearMenuArea();
					
					m_canvas->Render();          // Re-render canvas to restore drawing
					SDL_SetRenderTarget(Application::GetInstance()->GetRenderer(), m_canvas->m_texture);
					SDL_RenderPresent(Application::GetInstance()->GetRenderer()); // Refresh screen

				}
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1)
			{
				m_canvas->currentActiveTool = ToolType::PENCIL;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_2)
			{
				m_canvas->currentActiveTool = ToolType::ERASER;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_3)
			{
				m_canvas->currentActiveTool = ToolType::BRUSH;
			}
			/*if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			{
				Application::GetInstance()->GetCanvas()->Fill();
			}*/
		}
		//m_canvas->Render();
		m_paintUI->ShowColourPallete(m_renderer,m_canvas->m_paletteColors);
		SDL_RenderPresent(m_renderer);
		SDL_SetCursor(m_paintUI->m_cursor);
		
	}

}
void Application::Clean()
{
	if (m_canvas)
	{
		delete m_canvas;
		m_canvas == nullptr;
	}
	if (m_paintUI)
	{
		delete m_paintUI;
		m_paintUI == nullptr;
	}
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	//Quit SDL
	SDL_Quit();
}
Canvas* Application::GetCanvas()
{
	return m_canvas;
}

