#include "GEShaderProgram.h"
#include "LowLevelGraphics.h"
#include "GEApp.h"
#include <iostream>

GEShaderProgram::GEShaderProgram(bool autoSubscribe) : GEBase(autoSubscribe)
{
	programID = glCreateProgram();

	if (autoSubscribe)
	{
		SubscribeTo((GEBase*)GEApp::Renderer());
	}
}


GEShaderProgram::~GEShaderProgram(void)
{

	for(auto sh : shaderList)
		DetachShader(sh);

	glDeleteProgram(programID);
}

void GEShaderProgram::Link(void)
{
	glLinkProgram(programID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
		std::cout << "Error Linking shader program " << programID << "." << std::endl;

}

void GEShaderProgram::Use(void)
{
	glUseProgram(programID);
}

void GEShaderProgram::AttachShader(GEShader* shader)
{
	glAttachShader(programID, shader->shaderID);

	shaderList.push_back(shader);
}

void GEShaderProgram::DetachShader(GEShader* shader)
{
	for(unsigned int i = 0; i < shaderList.size(); i++)
	{
		if(shaderList[i] == shader)
		{
			glDetachShader(programID, shader->shaderID);
			break;
		}
	}
}