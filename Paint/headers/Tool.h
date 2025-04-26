#pragma once
#include<SDL.h>
#include<map>
enum ToolType
{
	PENCIL,
	ERASER,
	BRUSH,
	FILL
};

class Tool
{

public:
	Tool();
protected:


	ToolType toolType;
	//std::string m_toolName;
	int m_maxToolSize;
	int m_minToolSize;
	int m_currentToolSize;
	SDL_Cursor* m_cursor;	
protected:
	void IncreaseDrawingToolSize();
	void DecreaseDrawingToolSize();

};
class Pencil : public Tool
{
public: 
	void Draw(SDL_Renderer* renderer, SDL_Texture* texture, int& prevX, int& prevY, int x, int y,SDL_Color currentSelectedColor);
};
class Eraser : public Tool
{
public: 
	void Erase(SDL_Renderer* renderer, SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color defaultBackgroundColor);
};
class Brush : public Tool
{
public:
	void Draw(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color currentSelectedColor);
};