#include "GEModelData.h"


GEModelData::GEModelData(void) : GEBase(false)
{
	classType = GECLASS_ModelData;
	graphicsBound = false;
}


GEModelData::~GEModelData(void)
{
	UnBindGraphics();
}


void GEModelData::BindGraphics()
{
	if (graphicsBound)
		UnBindGraphics();

	std::cout << "Binding Graphics For ModelData" << this << std::endl;
	std::cout << "Number Of Meshes: " << meshDataList.size() << std::endl;
	
	// For each mesh
	for (unsigned int n = 0; n < meshDataList.size(); n++)
	{
		GEMeshData& mesh = meshDataList[n];
		std::cout << "	Mesh " << n + 1 << std::endl;
			glGenBuffers(1, &mesh.vertexBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBufferObject);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* mesh.numVertices * 4, mesh.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &mesh.indexBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBufferObject);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.numIndices, mesh.indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &mesh.normalBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBufferObject);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* mesh.numVertices * 3, mesh.normals, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			std::cout << "	vertexBufferObject Indx: " << mesh.vertexBufferObject << std::endl;
			std::cout << "		Number Of Vertices: " << mesh.numVertices << std::endl;
			std::cout << "	indexBufferObject Indx: " << mesh.indexBufferObject << std::endl;
			std::cout << "		Number Of Indices: " << mesh.numIndices << std::endl;
			std::cout << "	normalBufferObject Indx: " << mesh.normalBufferObject << std::endl;
			std::cout << "		Number Of Normals: " << mesh.numNormals << std::endl;
	}
	
	graphicsBound = true;
}
void GEModelData::UnBindGraphics()
{
	if (graphicsBound == false)
		return;

	

	// For each mesh
	for (unsigned int n = 0; n < meshDataList.size(); n++)
	{
		GEMeshData& mesh = meshDataList[n];
		
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &mesh.vertexBufferObject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &mesh.indexBufferObject);


	}
	
	GLenum ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout << "ERROR: Could not create a VBO: " 
			      << gluErrorString(ErrorCheckValue)
			      << std::endl;

	}

}