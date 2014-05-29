#include "GEAABB.h"


GEAABB::GEAABB() : GEBase()
{
	minBound = glm::vec3(-0.5, -0.5, -0.5);
	maxBound = -minBound;
}


GEAABB::~GEAABB()
{
}



glm::vec3 GEAABB::GetMinBound()
{
	return minBound;
}
glm::vec3 GEAABB::GetMaxBound()
{
	return maxBound;
}