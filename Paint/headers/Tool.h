#pragma once
#include<SDL.h>
#include<map>
#include<cmath>
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
	void Draw(SDL_Texture* texture, int& prevX, int& prevY, int x, int y,SDL_Color currentSelectedColor);
};
class Eraser : public Tool
{
public: 
	void Erase(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color defaultBackgroundColor);
};
class Brush : public Tool
{
public:
	void DrawCircle(int centreX, int centreY, int radius);
	void Draw(SDL_Texture* texture, int& prevX, int& prevY, int x, int y, SDL_Color currentSelectedColor);
	float GetSimpleNoise(float x, float y);
	void DrawNoiseBrush(SDL_Renderer* renderer, int centreX, int centreY, int radius, float noiseScale, float threshold);
	void DrawCrayonStroke(SDL_Renderer* renderer, int centreX, int centreY, int radius, SDL_Color color);
};