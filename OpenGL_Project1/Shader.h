#pragma once
//#include <iostream>
#include <string>

//using namespace std;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);//建构函数（构造函数）
	//~Shader();//解构函数（解析函数）

	//void test();

	std::string vertexString;
	std::string fragmentString;
	const char* myVertexSource = "0";
	const char* myFragmentSource = "0";
	unsigned int ID = 0; //Shader program ID
	void use();



private:
	void checkCompileErrors(unsigned int ID, std::string type);
	

};


