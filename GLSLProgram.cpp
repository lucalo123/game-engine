#include "GLSLProgram.h"

#include <fstream>
#include <vector>

npe::GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0) { }


void npe::GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		ErrorHandler::Message("Couldnt create vertexshader.");
	}
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		ErrorHandler::Message("Couldnt create fragmentshader.");
	}

	// Compile shaders
	CompileShader(vertexShaderFilePath, _vertexShaderID);
	CompileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void npe::GLSLProgram::AddAttrib(const std::string& attribName)
{
	glBindAttribLocation(_programID, _numAttributes++, attribName.c_str());
}

void npe::GLSLProgram::CompileShader(const std::string& filePath, GLuint id)
{
	// When vertex and fragment shaders are successfully compiled
	// link them together into a program.
	_programID = glCreateProgram();

	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		ErrorHandler::Message("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);
	// Errorhandling
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		// Maxlength includes NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		std::printf("%s\n", &errorLog[0]);
		ErrorHandler::Message("Shader " + filePath + " failed to compile.");
	}
}

void npe::GLSLProgram::LinkShaders()
{
	// Attach shaders to our program.
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link our program
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// Maxlength includes nullcharacter
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// Free up memory.
		glDeleteProgram(_programID);
		// Dont leak shaders.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		ErrorHandler::Message("Shaders failed to link!");
	}
	// Detach
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

GLuint npe::GLSLProgram::GetUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		ErrorHandler::Message("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

void npe::GLSLProgram::Enable()
{
	glUseProgram(_programID);

	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void npe::GLSLProgram::Disable()
{
	glUseProgram(0);

	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

npe::GLSLProgram::~GLSLProgram()
{
	// Free up memory.
	glDeleteProgram(_programID);
}
