#include "GEApp.h"
#include "GEBase.h"
#include <iostream>


int main(int argc, char** argv)
{
	GEApp::globalGameEngineInstance = new GEApp;
	GEApp::GameEngine()->Initialize();
	GEApp::GameEngine()->Run();

	delete GEApp::GameEngine();
	GEApp::globalGameEngineInstance = nullptr;
	return 0;
}