#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "common_header.h"
#include "common/shader.hpp"

class Shader2
{
    public:
        Shader2() 
	{
	    isLinked = false;
	}
        ~Shader2() {}
        GLuint programID;
	bool isLinked;

	void loadShaders(const char* vlsl, const char* flsl)
	{
	    isLinked = true;
            programID = LoadShaders(vlsl, flsl);
	}
	void unloadShader()
	{
            glUseProgramObjectARB(0);
	}
	void useProgram()
	{
	    glUseProgram(programID);
	}

	void setUniform(const char* sName, glm::mat4* mMatrices, int iCount = 1)
	{
	    if(!isLinked) return;
            GLuint id = glGetUniformLocation(programID, sName);
            glUniformMatrix4fv(id, iCount, GL_FALSE, glm::value_ptr(*mMatrices));
	}
};

class ShaderProgram
{
public:
	void loadShaders(const char* vlsl, const char* flsl);
	void deleteProgram();

	void useProgram();

	GLuint getProgramID();


	// Setting vectors
	void setUniform(const char* sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(const char* sName, const glm::vec2 vVector);
	void setUniform(const char* sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(const char* sName, const glm::vec3 vVector);
	void setUniform(const char* sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(const char* sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(const char* sName, float* fValues, int iCount = 1);
	void setUniform(const char* sName, const float fValue);

	// Setting 3x3 matrices
	void setUniform(const char* sName, glm::mat3* mMatrices, int iCount = 1);
	void setUniform(const char* sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void setUniform(const char* sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(const char* sName, const glm::mat4 mMatrix);

	// Setting integers
	void setUniform(const char* sName, int* iValues, int iCount = 1);
	void setUniform(const char* sName, const int iValue);

	ShaderProgram();

private:
	GLuint uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};


#endif
