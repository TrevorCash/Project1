#pragma once
#include "GEBase.h"
#include "LowLevelGraphics.h"
class GEMeshData :
	public GEBase
{
public:
	GEMeshData();
	~GEMeshData();


	float* vertices;//positions of vertices {x1, y1, z1, w1},{x2, y2, z2, w2},....
	unsigned int numVertices;

	float* normals;//positions of normals {x1, y1, z1, w1},{x2, y2, z2, w2},....
	unsigned int numNormals;

	(unsigned int*) indices;//defines triangles unsigned ints specifiying which vertex to use. {1,2,3},{3,2,4},...
	unsigned int numIndices;

	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint normalBufferObject;
	GLuint indexBufferObject;

};

