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

	//menu list 
	//std::map<SDL_KeyCode, std::string> toolMap;
	std::string menulist[3];

public:
	void InitializeMenuList();
	void LoadFont();
	void SetFontColor();
	void RenderMenuList();
	void ShowNotificationPanel(std::string notification);
	void ShowColourPallete();
	void CleanResources();
};