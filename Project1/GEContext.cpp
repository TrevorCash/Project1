#include "GEContext.h"
#include "glm\glm.hpp"
#include "LowLevelGraphics.h"
#include "GEApp.h"

#include <iostream>



GEContext::GEContext(void)
{

	keyStates.resize(500);

	GLenum GlewInitResult;

	glfwSetErrorCallback(GLFW_OnError);
	

	if(!glfwInit())
		exit(EXIT_FAILURE);

	InitWindow();
	

	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		std::cout << "Glew Error: " << glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, GLFW_OnKeyStateChange);
}

GEContext::~GEContext(void)
{
	glfwDestroyWindow(window);

	glfwTerminate();
}


glm::vec2 GEContext::GetResolution()
{
	return resolution;
}

GLFWwindow* GEContext::GetWindow()
{
	return window;
}

bool GEContext::IsClosing()
{
	return glfwWindowShouldClose(window) || quit;
}

void GEContext::SwapBuffers()
{
	glfwSwapBuffers(window);
}


void GEContext::InitWindow()
{

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(1024, 768, "My Title", NULL, NULL);

	glfwMakeContextCurrent(window);
	
	std::cout << "Context created with GLFW Version: " << glfwGetVersionString() << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	quit = false;
}

bool GEContext::KeyDown(int key)
{
	if (key < 0)
		return false;

	if (keyStates[key] == 1)
		return true;

	return false;
}
bool GEContext::KeyHit(int key)
{
	if (key < 0)
		return false;

	if (keyStates[key] == 1)
	{
		keyStates[key] = 2;
		return true;
	}
	return false;
}

void GEContext::OnKeyStateChange(int key, int action, int mod)
{
	if (key < 0)
		return;

	if (action == GLFW_PRESS)
	{
		if (keyStates[key] == 0)
			keyStates[key] = 1;

		if (key == GLFW_KEY_ESCAPE)
			quit = true;
	}
	if (action == GLFW_RELEASE)
	{
		if (keyStates[key] > 0)
			keyStates[key] = 0;
	}
}

void GEContext::UpdateMouse()
{
	lastMousePos = curMousePos;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	curMousePos = glm::dvec2(x, y);

	mouseVel = curMousePos - lastMousePos;

	if (KeyHit(GLFW_KEY_M))
		ShowMouse();
}

glm::dvec2 GEContext::GetMouseVel()
{
	return mouseVel;
}
void GEContext::HideMouse()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void GEContext::ShowMouse()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}






//global callbacks
void GLFW_OnError(int error, const char* description)
{
	std::cerr << "GLFW ERROR: " << description << std::endl;

}

void GLFW_OnKeyStateChange(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//forward the message to the client object.
	GEApp::Context()->OnKeyStateChange(key, action, mods);
}