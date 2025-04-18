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
	m_canvas = new Canvas(m_renderer);
	m_paintUI = new PaintUI();
	m_canvas->Fill();
	
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
			if (event.type == SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
			{
				int mPosX;
				int mPosY;

				
				SDL_GetMouseState(&mPosX, &mPosY);
				
				//m_canvas->m_currentSelectedColor = m_paintUI->PickColorFromPaletteUI(mPosX, mPosY, m_canvas->m_paletteColors);

				//std::cout << m_canvas->m_currentSelectedColor.r;
				//to pick color

				

				////m_canvas->HandleMouseClick(mPosX, mPosY);
				//if (m_canvas->currentActiveTool == ToolType::PENCIL)
				//{
				//	m_canvas->Draw(mPosX, mPosY);
				//}
				//else if(m_canvas->currentActiveTool == ToolType::ERASER)
				//{
				//	m_canvas->Erase(mPosX,mPosY);
				//}
				
				//m_canvas->m_currentSelectedColor = m_paintUI->PickColorFromPaletteUI(mPosX, mPosY, m_canvas->m_paletteColors);
				//m_canvas->SetCurrentSelectedColor(m_paintUI->PickColorFromPaletteUI(mPosX, mPosY, m_canvas->m_paletteColors));

				m_paintUI->PickColorFromPaletteUI(mPosX, mPosY, m_canvas->m_paletteColors, m_canvas->m_currentSelectedColor);

				//newer impl
				m_canvas->HandleDrawingTool(mPosX,mPosY);
				
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				m_canvas->SaveCanvas("sketch.bmp",1200,700);
			}
			if (event.key.keysym.sym == SDLK_q)
			{
				m_canvas->currentActiveTool = ToolType::PENCIL;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				m_canvas->currentActiveTool = ToolType::ERASER;
				if (m_canvas->currentActiveTool == ToolType::ERASER)
				{
					std::cout << "current selected tool is : eraser" << std::endl;
				}
			}
			
		}
		//SDL_RenderClear(m_renderer);
		//SDL_SetRenderDrawColor(m_renderer, 100, 220, 220, 255);
		m_canvas->Render();
		m_paintUI->RenderMenuList();
		m_paintUI->ShowColourPallete(m_renderer,m_canvas->m_paletteColors);
		SDL_RenderPresent(m_renderer);
		
	}

}
void Application::Clean()
{

}

