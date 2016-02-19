#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <string>
using namespace::std;

class GameEngine;
class Application
{
public:
	static Application& Instance();
	
	void Init();
	void Run();
	void Exit();

	StopWatch timer;

private:
	Application();
	~Application();

	GameEngine* engine;
};

#endif