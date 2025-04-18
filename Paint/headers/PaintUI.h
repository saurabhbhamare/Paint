#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<map>
//#include<string>
class PaintUI
{
public: 
	PaintUI();
private: 
	TTF_Font* m_font;
	SDL_Color m_fontColor;
public:

	//Cursor
	SDL_Surface* m_arrowSurface;
	SDL_Surface* colorPointerArrow;
	SDL_Cursor* m_cursor;

	//menu list 
	//std::map<SDL_KeyCode, std::string> toolMap;
	std::string menulist[10];
	

	//Color Palette 
	bool isPalleteVisible;
	SDL_Color currentSelectedColor;

public:
	void ShowColorPointerArrow(int x, int y);
	void LoadSDLCursor();
	void LoadColorPointerArrow();
	void InitializeCursor();
	void InitializeMenuList();
	void LoadFont();
	void SetFontColor();
	void RenderMenuList();
	void ShowNotificationPanel(std::string notification);
	void ShowColourPallete(SDL_Renderer* renderer, std::map<std::string, SDL_Color>* colorPalette);
	void CleanResources();
	SDL_Color PickColorFromPaletteUI(int x, int y, std::map<std::string, SDL_Color>* colorPalette,SDL_Color &color);
};