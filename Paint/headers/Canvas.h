#pragma once
#include<SDL.h>
#include</Programming/Paint/Paint/headers/Tool.h>
class Canvas
{
private:
	int m_prevX;
	int m_prevY;

	//def colour
	//SDL_Colour* defBackgroundColour;
	SDL_Surface* m_surface;
	SDL_Surface* m_windowSurface;

	//Colors 
	SDL_Color m_currentSelectedColor;
	SDL_Color m_defaultDrawingToolColor;



	//using textures

	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	uint32_t defBackgroundColour;
	//uint32_t currentSelectedColour;
public: 
	Canvas(SDL_Renderer* renderer);
	Pencil* pencil;
	Eraser* eraser;
	Tool* currentTool;
	ToolType currentActiveTool;
public:
	//void Reset();
	void HandleDrawingTool(int x, int y);
	void InitializeDrawingTools();
	void ResetPointerPosition();
	void CreateCanvasTexture();
	void Render();
	void SaveCanvas(const char* fileName, int width , int height);
	void SetInitialPoint(int x,int y);
	void HandleMouseClick(int mouseX, int mouseY);
	void SetActiveTool(Tool tool);
	void Draw(int x, int y);
	void ResizeDrawingTool();
	//void DrawLineBetweenTwoPoints(int x, int y);
	void Erase(int x, int y);
	void Fill();

	//colors
	

};