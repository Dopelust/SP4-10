#include "Application.h"

int main()
{
	Application::Instance().Init();
	Application::Instance().Run();
	Application::Instance().Exit();
}