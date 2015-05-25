#ifndef GEAABB_H
#define GEAABB_H
#include "GEBase.h"
#include "glm\glm.hpp"

class GEAABB :
	public GEBase
{
public:
	GEAABB();
	~GEAABB();

	glm::vec3 GetMinBound();
	glm::vec3 GetMaxBound();

	GEAABB& operator+=(glm::vec3& cords)
	{
		this->minBound += cords;
		this->maxBound += cords;
		return *this;
	}
private:

	glm::vec3 minBound;
	glm::vec3 maxBound;
};

inline GEAABB operator+(GEAABB& aabb, glm::vec3& cords)
{
	return aabb += cords;
}
inline GEAABB operator-(GEAABB& aabb, glm::vec3& cords)
{
	return aabb += -cords;
}

#endif