#include "GEEntityCamera.h"
#include "GEClient.h"
#include "EasyInput.h"
#include <iostream>
#include "glm\glm.hpp"

GEEntityCamera::GEEntityCamera() : GEEntity()
{
	yaw = 0;
	pitch = 0;
}


GEEntityCamera::~GEEntityCamera()
{

}

void GEEntityCamera::OnBaseTickUpdate(double deltaTime)
{
	GEEntity::OnBaseTickUpdate(deltaTime);

	
	MoveBy(vel);

	glm::vec3 dir(0,0,0);

	if (KeyDown(GLFW_KEY_D))
		dir += GetRight();

	if (KeyDown(GLFW_KEY_A))
		dir -= GetRight();

	if (KeyDown(GLFW_KEY_W))
		dir += GetForward();

	if (KeyDown(GLFW_KEY_S))
		dir -= GetForward();

	if (glm::length(dir) > 0.0f)
		vel = glm::normalize(dir);

	float speed;
	if (KeyDown(GLFW_KEY_LEFT_SHIFT))
		speed = 2.0;
	else if (KeyDown(GLFW_KEY_LEFT_CONTROL))
		speed = 0.3;
	else
		speed = 0.7;

	vel = dir*speed;


	yaw += -MouseVel().x/4.0f;
	pitch += -MouseVel().y/4.0f;

	if (pitch > 85)
		pitch = 85;

	if (pitch < -85)
		pitch = -85;

	if (yaw > 359)
		yaw = 0;

	
	SetRotation(0, glm::vec3(1,0,0));
	RotateBy(yaw, glm::vec3(0,1,0));
	RotateBy(pitch,glm::vec3(1,0,0));
	
} 