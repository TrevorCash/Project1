#pragma once
#include "gebase.h"
#include "LowLevelGraphics.h"
#include "glm\glm.hpp"

#include <vector>

class GEContext
{
public:
	GEContext(void);
	~GEContext(void);

	glm::vec2 GetResolution();
	GLFWwindow* GetWindow();
	bool IsClosing();
	void SwapBuffers();

	bool KeyDown(int key);
	bool KeyHit(int key);

	void UpdateMouse();
	glm::dvec2 GetMouseVel();
	void HideMouse();
	void ShowMouse();


	void OnKeyStateChange(int key, int action, int mod);

private:

	void InitWindow();


	glm::vec2 resolution;

	GLFWwindow* window;

	std::vector<int> keyStates;
	glm::dvec2 curMousePos;
	glm::dvec2 lastMousePos;
	glm::dvec2 mouseVel;

	bool quit;

};

//some global callbacks for GLFW....
void GLFW_OnError(int error, const char* description);
void GLFW_OnKeyStateChange(GLFWwindow* window, int key, int scancode, int action, int mods);
