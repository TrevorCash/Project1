#include "GEApp.h"
#include "GEBase.h"
#include <iostream>


int main(int argc, char** argv)
{
	GEApp* app = new GEApp;
	GEApp::GameEngine()->Initialize();
	GEApp::GameEngine()->Run();

	delete app;
	GEApp::globalGameEngineInstance = nullptr;
	return 0;
}