#include "Shader.h"
#include <fstream>
#include <sstream>

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

Shader::Shader(const char*vertexPath, const char*fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;

	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	/*vertexString = "0";
	fragmentString = "0";*/

	/*myVertexSource = "0";
	myFragmentSource = "0";*/

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("Open file error!");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();


		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		myVertexSource = vertexString.c_str();
		myFragmentSource = fragmentString.c_str();

		/*printf(vertexSource);
		printf("\n");
		printf(fragmentSource);*/


		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &myVertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &myFragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);


	}
	catch (const std::exception&ex)
	{
		//count << (ex.what()) << endl;²»ÐÐ¡£¡£
		printf(ex.what());
	}

}


void Shader::use() {
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type) {
	int success;
	char infolog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infolog);
			cout << "Shader compile error:" << infolog << endl;
		}
		
	}
	else
	{
		glGetProgramiv(ID,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			cout << "Shader link error" << infolog << endl;
		}

	}
}


//void Shader::test() {
//	printf("shader test");
//}