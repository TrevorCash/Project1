//fixes some conflics with win sock redefinitions and glfw...
#define _WINSOCKAPI_

#include "GEApp.h"
#include "GEConsole.h"
#include "GEWorld.h"
#include "GEContext.h"
#include "GERenderer.h"
#include "GEClient.h"
#include "GENetworkManager.h"
#include <iostream>

GEApp* GEApp::globalGameEngineInstance = nullptr;

GEApp::GEApp(void)
{
	GEApp::globalGameEngineInstance = this;
	//comment
	pConsole = nullptr;
	pNetStatus = nullptr;
	pContext = nullptr;
	pRenderer = nullptr;
	pWorld = nullptr;
	pClient = nullptr;



	pConsole = new GEConsole();
	pConsole->SetNickName("Console");

	pNetStatus = new GENetworkManager();

	pContext = new GEContext();
	
	pRenderer = new GERenderer(pContext);
	pRenderer->SetNickName("Renderer");

	pWorld = new GEWorld();
	pWorld->SetNickName("World");

	pClient = new GEClient();
	
	
	glfwSetTime(0.0);
	appTime = glfwGetTime();
}


GEApp::~GEApp(void)
{

	//this order DOES matter.
	delete pRenderer;
	NewtonWorld* pNewt = pWorld->newtonWorld;
	delete pWorld;
	delete pContext;
	delete pClient;
	
	delete pConsole;

	NewtonDestroy(pNewt);
}

void GEApp::Initialize()
{
	PrintEngineSpecs();
	//this doesnt neccessarily need to be here.
	std::cout << "Is This A Client Or Server? (c/s): ";
	char answer;
	answer = 'c';
	//std::cin >> answer;
	if (answer == 's')
	{
		pNetStatus->ConfigureAsHost(1234);
	}
	else//assume client
	{
		pNetStatus->ConfigureAsClient();
		
		//ask user for server address to connect to..
		pNetStatus->ConnectToHost("localhost");
	}

	pWorld->Initialize();
	pContext->HideMouse();
}
void GEApp::PrintEngineSpecs()
{
	int* i = new int;
	std::cout << i;
	delete i;
	i = nullptr;
}




void GEApp::Run(void)
{
	std::cout << "Game Engine Running" << std::endl;

	float interpolation;
	double preRenderTime = glfwGetTime();
	double postRenderTime = glfwGetTime();
	double preTickTime = glfwGetTime();
	double postTickTime = glfwGetTime();
	double timeAccumulator = 0.0;
	const double TickTime = (double)(1 / WORLDTICKMUL);
	
	while(!pContext->IsClosing())
	{	
		
		while (timeAccumulator >= TickTime)
		{
			preTickTime = glfwGetTime();
			pContext->UpdateMouse();
			pConsole->BaseTickUpdate(TickTime);
			pNetStatus->Update();
			pWorld->BaseTickUpdate(TickTime);
			postTickTime = glfwGetTime();
			timeAccumulator -= TickTime;
			if ((postTickTime - preTickTime) > TickTime) break;
			timeAccumulator + (postTickTime - preTickTime);
		}
		
		
		preRenderTime = glfwGetTime();
			if (!pNetStatus->IsServer())
			{
				interpolation = glm::clamp((timeAccumulator)/ TickTime, 0.0, 1.0);
				pRenderer->Render(pClient, pWorld, interpolation);
			}
			
			pContext->SwapBuffers();
			glfwPollEvents();
		postRenderTime = glfwGetTime();
	
		timeAccumulator = timeAccumulator + ( postRenderTime - preRenderTime );

	}

	std::cout << "Game Engine Shutdown...." << std::endl;

}