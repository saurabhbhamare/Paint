#pragma once
#include<SDL.h>

class Tool
{
private: 
	SDL_Cursor* m_cursor;	
	int m_size;

};
class Pencil : public Tool
{

};
class Eraser : public Tool
{

};
class Brush : public Tool
{

};