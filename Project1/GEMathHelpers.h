#pragma once
#include <iostream>
#include <iomanip>
#include "GEPhysicsHeaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"

//printout helper functions
void PrintNewtonMatrix(const dFloat* matrix, std::ostream& stream);
void PrintNewtonMatrix(dMatrix &matrix, std::ostream& stream);
void PrintGlmMatrix(glm::mat4 &matrix, std::ostream& stream);

//conversion helper function for converting to/from newton math and glm math.
dMatrix GlmToNewt(glm::mat4 matrix4);

glm::quat NewtToGlm(dQuaternion& nQuat);
glm::mat4 NewtToGlm(dMatrix& nMatrix);