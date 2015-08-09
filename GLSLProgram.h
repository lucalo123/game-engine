#pragma once
#include <string>
#include <GL\glew.h>
#include "ErrorHandler.h"
namespace npe {
	class GLSLProgram
	{
		GLuint _programID, _vertexShaderID, _fragmentShaderID;
		int _numAttributes;
		void CompileShader(const std::string& filePath, GLuint id);
	public:
		GLSLProgram();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void AddAttrib(const std::string& attribName);

		void LinkShaders();

		GLuint GetUniformLocation(const std::string& uniformName);

		void Enable();

		void Disable();

		~GLSLProgram();
	};
}
