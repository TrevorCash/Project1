#include "GEMathHelpers.h"

void PrintNewtonMatrix(const dFloat* matrix, std::ostream& stream)
{
	stream << matrix[0] << "," << std::setw(5) << matrix[1] << "," << std::setw(5) << matrix[2] << "," << std::setw(5) << matrix[3] << "," << std::setw(5) << std::endl;
	stream << matrix[4] << "," << std::setw(5) << matrix[5] << "," << std::setw(5) << matrix[6] << "," << std::setw(5) << matrix[7] << "," << std::setw(5) << std::endl;
	stream << matrix[8] << "," << std::setw(5) << matrix[9] << "," << std::setw(5) << matrix[10] << "," << std::setw(5) << matrix[11] << "," << std::setw(5) << std::endl;
	stream << matrix[12] << "," << std::setw(5) << matrix[13] << "," << std::setw(5) << matrix[14] << "," << std::setw(5) << matrix[15] << "," << std::setw(5) << std::endl;
}

void PrintNewtonMatrix(dMatrix &matrix, std::ostream& stream)
{
	stream << matrix[0][0] << "," << std::setw(5) << matrix[0][1] << "," << std::setw(5) << matrix[0][2] << "," << std::setw(5) << matrix[0][3] << "," << std::setw(5) << std::endl;
	stream << matrix[1][0] << "," << std::setw(5) << matrix[1][1] << "," << std::setw(5) << matrix[1][2] << "," << std::setw(5) << matrix[1][3] << "," << std::setw(5) << std::endl;
	stream << matrix[2][0] << "," << std::setw(5) << matrix[2][1] << "," << std::setw(5) << matrix[2][2] << "," << std::setw(5) << matrix[2][3] << "," << std::setw(5) << std::endl;
	stream << matrix[3][0] << "," << std::setw(5) << matrix[3][1] << "," << std::setw(5) << matrix[3][2] << "," << std::setw(5) << matrix[3][3] << "," << std::setw(5) << std::endl;
}

void PrintGlmMatrix(glm::mat4 &matrix, std::ostream& stream)
{
	stream << matrix[0][0] << "," << std::setw(5) << matrix[0][1] << "," << std::setw(5) << matrix[0][2] << "," << std::setw(5) << matrix[0][3] << "," << std::setw(5) << std::endl;
	stream << matrix[1][0] << "," << std::setw(5) << matrix[1][1] << "," << std::setw(5) << matrix[1][2] << "," << std::setw(5) << matrix[1][3] << "," << std::setw(5) << std::endl;
	stream << matrix[2][0] << "," << std::setw(5) << matrix[2][1] << "," << std::setw(5) << matrix[2][2] << "," << std::setw(5) << matrix[2][3] << "," << std::setw(5) << std::endl;
	stream << matrix[3][0] << "," << std::setw(5) << matrix[3][1] << "," << std::setw(5) << matrix[3][2] << "," << std::setw(5) << matrix[3][3] << "," << std::setw(5) << std::endl;
}






//dMatrix GlmToNewt(glm::mat4 matrix4)
//{
//	dMatrix newtMat;
//	newtMat[0][0] = matrix4[0][0];   newtMat[0][1] = matrix4[1][0];   newtMat[0][2] = matrix4[2][0];   newtMat[0][3] = matrix4[3][0];
//
//	newtMat[1][0] = matrix4[0][1];   newtMat[1][1] = matrix4[1][1];   newtMat[1][2] = matrix4[2][1];   newtMat[1][3] = matrix4[3][1];
//
//	newtMat[2][0] = matrix4[0][2];   newtMat[2][1] = matrix4[1][2];   newtMat[2][2] = matrix4[2][2];   newtMat[2][3] = matrix4[3][2];
//
//	newtMat[3][0] = matrix4[0][3];   newtMat[3][1] = matrix4[1][3];   newtMat[3][2] = matrix4[2][3];   newtMat[3][3] = matrix4[3][3];
//	return newtMat;
//}
dMatrix GlmToNewt(glm::mat4 matrix4)
{
	return dMatrix(&matrix4[0][0]);
}

glm::quat NewtToGlm(dQuaternion& nQuat)
{
	glm::quat gQuat;
	gQuat.w = nQuat.m_q0;
	gQuat.x = nQuat.m_q1;
	gQuat.y = nQuat.m_q2;
	gQuat.z = nQuat.m_q3;
	return gQuat;
}

glm::mat4 NewtToGlm(dMatrix& nMatrix)
{
	glm::mat4 glmMat;
	glmMat[0][0] = nMatrix[0][0];   glmMat[0][1] = nMatrix[0][1];   glmMat[0][2] = nMatrix[0][2];   glmMat[0][3] = nMatrix[0][3];

	glmMat[1][0] = nMatrix[1][0];   glmMat[1][1] = nMatrix[1][1];   glmMat[1][2] = nMatrix[1][2];   glmMat[1][3] = nMatrix[1][3];

	glmMat[2][0] = nMatrix[2][0];   glmMat[2][1] = nMatrix[2][1];   glmMat[2][2] = nMatrix[2][2];   glmMat[2][3] = nMatrix[2][3];

	glmMat[3][0] = nMatrix[3][0];   glmMat[3][1] = nMatrix[3][1];   glmMat[3][2] = nMatrix[3][2];   glmMat[3][3] = nMatrix[3][3];
	return glmMat;
}