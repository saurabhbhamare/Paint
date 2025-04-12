#pragma once
#include</Programming/Paint/Paint/headers/Canvas.h>
#include</Programming/Paint/Paint/headers/PaintUI.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>

class Application
{
private: 
	static Application* m_instance;
	Application();
public: 
	Application(const Application&) = delete;
	static Application* GetInstance();

	//SDL_Window* GetWindow();

private: 
	/*int prevX = -1;
	int prevY = -1;*/
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 700;

	SDL_Window* m_window; 
	SDL_Renderer* m_renderer;
	Canvas* m_canvas;
	PaintUI* m_paintUI;
	
	/*std::unique_ptr<Canvas> m_canvas;*/

public: 
	SDL_Window* GetWindow() const;
	Canvas* GetCanvas() const;
	PaintUI* GetPaintUI() const;
	SDL_Renderer* GetRenderer() const;
	//void ResetXandY();
	void Init();
	void Run();
	void Clean();
};