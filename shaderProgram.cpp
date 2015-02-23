#include "shaderProgram.h"


Shader2::Shader2() 
{
    isLinked = false;
}

void Shader2::loadShaders(const char* vlsl, const char* flsl)
{
    isLinked = true;
    programID = LoadShaders(vlsl, flsl);
}
void Shader2::unloadShader()
{
    glUseProgramObjectARB(0);
}

void Shader2::useProgram()
{
    glUseProgram(programID);
}

GLuint Shader2::getProgramID()
{
    return isLinked ? programID : 0;
}

/*-----------------------------------------------


ShaderProgram::ShaderProgram()
{
	bLinked = false;
}

/*-----------------------------------------------

Name:	createProgram

Params:	none

Result:	Creates a new program.

/*---------------------------------------------*/
void ShaderProgram::loadShaders(const char* vlsl, const char* flsl)
{
    uiProgram = LoadShaders(vlsl, flsl);
    bLinked = true;
}


/*-----------------------------------------------

Name:	deleteProgram

Params:	none

Result:	Deletes program and frees memory on GPU.

/*---------------------------------------------*/

void ShaderProgram::deleteProgram()
{
	if(!bLinked)return;
	bLinked = false;
	glDeleteProgram(uiProgram);
}

/*-----------------------------------------------

Name:	useProgram

Params:	none

Result:	Tells OpenGL to use this program.

/*---------------------------------------------*/

void ShaderProgram::useProgram()
{
	if(bLinked)glUseProgram(uiProgram);
}

/*-----------------------------------------------

Name:		getProgramID

Params:	none

Result:	Returns OpenGL generated shader program ID.

/*---------------------------------------------*/

GLuint ShaderProgram::getProgramID()
{
	return uiProgram;
}

/*-----------------------------------------------

Name:		uniformSetters

Params:	yes, there are :)

Result:	These set of functions set most common
			uniform variables.

/*---------------------------------------------*/

// Setting floats

void ShaderProgram::setUniform(const char* sName, float* fValues, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::setUniform(const char* sName, const float fValue)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::setUniform(const char* sName, glm::vec2* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(const char* sName, const glm::vec2 vVector)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(const char* sName, glm::vec3* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(const char* sName, const glm::vec3 vVector)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(const char* sName, glm::vec4* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(const char* sName, const glm::vec4 vVector)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void ShaderProgram::setUniform(const char* sName, glm::mat3* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniformMatrix3fv(iLoc, iCount, GL_FALSE, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(const char* sName, const glm::mat3 mMatrix)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniformMatrix3fv(iLoc, 1, GL_FALSE, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(const char* sName, glm::mat4* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniformMatrix4fv(iLoc, iCount, GL_FALSE, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(const char* sName, const glm::mat4 mMatrix)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniformMatrix4fv(iLoc, 1, GL_FALSE, (GLfloat*)&mMatrix);
}

// Setting integers

void ShaderProgram::setUniform(const char* sName, int* iValues, int iCount)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::setUniform(const char* sName, const int iValue)
{
	int iLoc = glGetUniformLocation(uiProgram, sName);
	glUniform1i(iLoc, iValue);
}

