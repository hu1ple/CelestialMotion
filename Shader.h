#pragma once           //防止重复包含头文件
#include<iostream>
#include<GLEW/glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include "Minicore.h"
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		ShaderProgram = glCreateProgram();
		if (ShaderProgram == 0)
		{
			std::cout << "Error Creating shader program!" << std::endl;
			exit(-1);
		}
		CompileShaderFromFIle(vertexPath, GL_VERTEX_SHADER);
		CompileShaderFromFIle(fragmentPath, GL_FRAGMENT_SHADER);
		LinkShaderProgram();
	}
	~Shader()
	{
		glDeleteShader(ShaderProgram);
	}
	void UseProgram()
	{
		glUseProgram(ShaderProgram);
	}

	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), static_cast<int>(value));
	}

	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}

	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}

	void Set4Float(const std::string& name, float v1, float v2, float v3, float v4)const
	{
		glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), v1, v2, v3, v4);
	}
	void SetMatrix4fv(const std::string& name, const glm::mat4& mat)const
	{
		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
private:
	GLuint ShaderProgram;
	void CompileShaderFromFIle(const char* path, GLenum shaderType) {
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			code = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ:" << e.what() << std::endl;
		}
		const GLchar* shaderCode = code.c_str();
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);
		CheckErrors(shader, "SHADER", GL_COMPILE_STATUS);
		glAttachShader(ShaderProgram, shader);
		glDeleteShader(shader);
	}
	void LinkShaderProgram() {
		glLinkProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_LINK_STATUS);
#ifndef _APPLE
		glValidateProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_VALIDATE_STATUS);
#endif // !_APPLE

	}
	void CheckErrors(GLuint obj, std::string type, int checkStatus)
	{
		GLint success;
		if (type == "SHADER")
		{
			CheckErrorAndLog(glGetShaderiv, glGetShaderInfoLog)
		}
		else if (type == "PROGRME")
		{
			CheckErrorAndLog(glGetProgramiv, glGetProgramInfoLog)
		}
	}
};
