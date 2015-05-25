#include "GEApp.h"
#include "GERenderer.h"
#include "GEWorld.h"
#include "GEContext.h"
#include "GEClient.h"
#include "GEEntityRenderable.h"
#include "GEEntityCamera.h"
#include "GEShaderProgram.h"
#include "GEShader.h"
#include "GEModelData.h"
#include "GEModelLoader.h"
#include "GEMeshData.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "GLFW\glfw3.h"

GERenderer::GERenderer(GEContext* pContext) : GEBase()
{
	context = pContext;
	LoadRenderingAssets();
	Initialize();

	UnSubscribeFrom((GEBase*)GEApp::Console());
}


GERenderer::~GERenderer(void)
{
	FreeRenderingAssets();
}


//Renders Through the given world.
void GERenderer::Render(GEClient* client, GEWorld* world, float interpolation)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	double timeOfRender = glfwGetTime();

	GEEntityCamera* currCam = client->GetCamera();

	glm::mat4 WorldToCamera = glm::inverse(currCam->GetInterpolatedTransform(interpolation, true, timeOfRender));
	glm::mat4 CameraToScreen = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(WorldToCamera));
	glm::mat4 WorldToScreen = CameraToScreen * WorldToCamera;

	GLint WorldToScreen_Loc = glGetUniformLocation(shaderProgramList[0]->ProgramID(), "WorldToScreenTransform");
	GLint LocalToWorld_Loc = glGetUniformLocation(shaderProgramList[0]->ProgramID(), "LocalToWorldTransform");
	GLint LocalToScreen_Loc = glGetUniformLocation(shaderProgramList[0]->ProgramID(), "LocalToScreenTransform");
	GLint Color_Loc = glGetUniformLocation(shaderProgramList[0]->ProgramID(), "Color");
	
	shaderProgramList[0]->Use();
	//tell shader how to get from world cords to screen cords.
	glUniformMatrix4fv(WorldToScreen_Loc, 1, GL_FALSE, glm::value_ptr(WorldToScreen));

	//tell the shader the normaltrasformmatrix
	//glUniformMatrix4fv(NormalToCamera_Loc, 1, GL_FALSE, glm::value_ptr(NormalMatrix));


	for (std::map<std::string, GEBase*>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
	{		

		GEEntityRenderable* ent = (GEEntityRenderable*)it->second;

		glm::mat4 localToWorld = ent->GetInterpolatedTransform(interpolation, true, timeOfRender);


		glm::mat4 localToScreen = WorldToScreen * localToWorld;

		//tell shader how to get from object cords to world cords.
		glUniformMatrix4fv(LocalToWorld_Loc, 1, GL_FALSE, glm::value_ptr(localToWorld));
		//tell shader how to get from object cords to screen cords.
		glUniformMatrix4fv(LocalToScreen_Loc, 1, GL_FALSE, glm::value_ptr(localToScreen));
		//tell chader about overall object coloring.
			
		glUniform4fv(Color_Loc, 1,  glm::value_ptr(ent->GetColor()));

		DrawRenderable(ent);

	}
	glUseProgram(0);

	glBegin(GL_LINE);
	glVertex2d(0, 0);
	glVertex2d(800, 600);
	glEnd();
}

void GERenderer::LoadRenderingAssets()
{
	//load shaders
    GEShader* pVertShad = new GEShader(GL_VERTEX_SHADER, "vertShader.shad");
	GEShader* pFragShad = new GEShader(GL_FRAGMENT_SHADER, "fragShader.shad");
	shaderList.push_back(pVertShad);
	shaderList.push_back(pFragShad);

	//create programs to use those shaders.
	GEShaderProgram* pShadProgram = new GEShaderProgram();
	pShadProgram->AttachShader(pVertShad);
	pShadProgram->AttachShader(pFragShad);
	pShadProgram->Link();
	shaderProgramList.push_back(pShadProgram);

	//load meshes
	GEModelData* pTestData = new GEModelData();
	modelLoader.LoadIntoModel(pTestData, "monkey.3ds");
	pTestData->BindGraphics();
	modelDataList.push_back(pTestData);

	GEModelData* pBoxData = new GEModelData();
	modelLoader.LoadIntoModel(pBoxData, "box.3ds");
	pBoxData->BindGraphics();
	modelDataList.push_back(pBoxData);

	GEModelData* pLegendData = new GEModelData();
	modelLoader.LoadIntoModel(pLegendData, "legend.3ds");
	pLegendData->BindGraphics();
	modelDataList.push_back(pLegendData);

	GEModelData* pGearData = new GEModelData();
	modelLoader.LoadIntoModel(pGearData, "gear1.3ds");
	pGearData->BindGraphics();
	modelDataList.push_back(pGearData);
}

void GERenderer::FreeRenderingAssets()
{
	for (int i = 0; i < (int)shaderProgramList.size(); i++)
	{
		shaderProgramList[i]->UnSubscribeFrom(this);
	}
	shaderProgramList.clear();


	for (int i = 0; i < (int)shaderList.size(); i++)
	{
		shaderList[i]->UnSubscribeFrom(this);
	}
	shaderList.clear();
}

void GERenderer::Initialize()
{
	glClearColor (0.5, 0.5, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
 
	int width, height;
    glfwGetFramebufferSize(context->GetWindow(), &width, &height);
    glViewport(0, 0, width, height);
}



void GERenderer::DrawRenderable(GEEntityRenderable* entity)
{
	
	

	// For each mesh
	for (unsigned int n = 0; n < entity->modelData->meshDataList.size(); n++)
	{
		GEMeshData& mesh = entity->modelData->meshDataList[n];

		glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBufferObject);
			
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
			
			
			glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBufferObject);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			

			//glDrawArrays(GL_TRIANGLES, 0, mesh.numIndices*3);
			glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, nullptr);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}

}

std::vector<GEModelData*>& GERenderer::ModelData()
{
	return modelDataList;
}