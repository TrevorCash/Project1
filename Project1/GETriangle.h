#pragma once
#include "glm\glm.hpp"

class GETriangle
{
public:
	GETriangle(){}
	~GETriangle(){}

	glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;

	glm::vec3 normal;

	glm::vec2 uvcord0;
	glm::vec2 uvcord1;
	glm::vec2 uvcord2;
};
