#include<iostream>
#include</Programming/Paint/Paint/headers/Application.h>
int main(int argc,char* argv[])
{
	Application* paint = Application::GetInstance();
	paint->Init();
	paint->Run();
	paint->Clean();

	return 0; 
}