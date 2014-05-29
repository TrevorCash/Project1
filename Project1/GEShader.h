#pragma once
#include "gebase.h"
#include "LowLevelGraphics.h"
#include <string>

class GEShader :
	public GEBase
{
public:
	GEShader(GLenum shaderType, std::string filepath);
	~GEShader();

	friend class GEShaderProgram;

private:

	bool LoadSource(std::string filepath);

	std::string sourceCode;

	GLuint shaderID;
	GLenum shaderType;
};

