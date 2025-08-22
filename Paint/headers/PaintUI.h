#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<map>

class PaintUI
{
public: 
	PaintUI();
private: 
	TTF_Font* m_font;
	SDL_Color m_fontColor;
public:

	//Cursor
	SDL_Surface* m_pencilIcon;
	SDL_Surface* m_arrowSurface;
	SDL_Surface* colorPointerArrow;
	SDL_Cursor* m_cursor;

	//menu list 
	bool isMenuVisible = false;
	const int numberOfMenus =7;
	//std::map<SDL_KeyCode, std::string> toolMap;
	SDL_Surface* menuSurfaces[20];
	SDL_Texture* menuTextures[20];
	std::string menulist[20];
	

	SDL_Texture* m_menuTexture;

	//Color Palette 
	bool isPalleteVisible;
	SDL_Color currentSelectedColor;

public:
	void CreateMenuTextures();
	void ShowColorPointerArrow(int x, int y);
	void ImportToolIconImages();
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

	//menu
	void CreateMenuTexture();
	void RenderMenuBackground();
	void ClearMenuArea();
	void HideMenu();
	SDL_Color PickColorFromPaletteUI(int x, int y, std::map<std::string, SDL_Color>* colorPalette,SDL_Color &color);


	//clearn resources
	void FreeMenuSurfaces();
};