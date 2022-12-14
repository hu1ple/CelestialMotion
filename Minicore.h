#pragma once
#include <GLEW/glew.h>
#define ERROR_LOG(ErrorMessage) std::cout << ErrorMessage << std::endl;glfwTerminate();exit(-1);
#define WINDOWWIDTH 1600
#define WINDOWHEIGHT 1200

typedef void(*CheckStatus)(GLuint, GLenum, GLint*);
typedef void(*ReadLog)(GLuint, GLsizei, GLsizei*, GLchar*);
#define CheckErrorAndLog(CheckStatus, ReadLog) CheckStatus(obj, checkStatus, &success);if (!success){GLchar InfoLog[1024];ReadLog(obj, 1024, NULL, InfoLog);std::cout << "ERROR::SHADER::PROGRAM_FAILED\n" << InfoLog<< std::endl;}
