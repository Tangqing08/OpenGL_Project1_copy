
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"


//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float lastX;
float lastY;
bool firstMouse = true;

unsigned int indices[] = {
	0,1,3,
	2,1,3
};


//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0.0f, 0), glm::vec3(0, 1.0f, 0));
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
	}
	else
	{
		camera.speedZ = 0.0f;
	}
};

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float delX, delY;
	delX = xPos - lastX;
	delY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	float sensitivity = 0.05f;
	delX *= sensitivity;
	delY *= sensitivity;
	camera.ProcessMouseMovement(delX, delY);
	//printf("%f \n", delX);
};


//using namespace std;

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "my opengl window", NULL, NULL);

	if (window == NULL) {
		printf("open window failed!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	glewExperimental = true;


	if (glewInit() != GLEW_OK)
	{
		printf("init glew failed!");
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);


	Shader* myshader = new Shader("vertexsource.txt", "fragmentsource.txt");//ָ����ʽ��new��̬�ڴ棬֮��Ҫ�ͷ��ڴ�

	//testshader->test();	

	//shader testshader = shader("vertexsource.txt", "fragmentsource.txt");
	//testshader.test();


	//glpolygonmode(gl_front_and_back, gl_line);

	//glenable(gl_cull_face);
	//glcullface(gl_back);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	stbi_set_flip_vertically_on_load(true);


	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	int width, height, nrChannel;
	unsigned char* data = stbi_load("container.png", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Load image failed!" << std::endl;
	}
	stbi_image_free(data);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);

	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Load image failed!" << std::endl;
	}
	stbi_image_free(data2);




	



	//unsigned int vertexshader;
	//vertexshader = glcreateshader(gl_vertex_shader);
	//glshadersource(vertexshader, 1, &vertexshadersource, null);
	//glcompileshader(vertexshader);

	//unsigned int fragmentshader;
	//fragmentshader = glcreateshader(gl_fragment_shader);
	//glshadersource(fragmentshader, 1, &fragmentshadersource, null);
	//glcompileshader(fragmentshader);

	//unsigned int shaderprogram;
	//shaderprogram = glcreateprogram();
	//glattachshader(shaderprogram, vertexshader);
	//glattachshader(shaderprogram, fragmentshader);
	//gllinkprogram(shaderprogram);





	//calculate our transformation matrix here

	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    //trans = glm::rotate(trans, (float)glfwGetTime()+1, glm::vec3(0, 0, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	
	//glm::mat4 model;
	while (!glfwWindowShouldClose(window))
	{
		// input
	  // -----
		
		glm::mat4 modelMat;
		//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
		//modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 viewMat;
		//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
		viewMat = camera.GetViewMatrix();
		glm::mat4 projMat;
		projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		//trans = glm::translate(trans, glm::vec3(-0.00000004, 0.0, 0.0));
		//trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0, 0, 1.0f));
		/*glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime()-90, glm::vec3(0, 0, 1.0f));
		trans = glm::scale(trans, glm::vec3(1.5f, 5.0f, 1.5f));*/
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		for (int i = 0 ; i < 10; i++) {

			glm::mat4 tenModel;
			tenModel = glm::translate(tenModel, cubePositions[i]);

			myshader->use();

			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myshader->ID, "ourFace"), 3);
			//unsigned int transformLoc = glGetUniformLocation(myshader->ID, "transform");
			//glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "transform"),1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "tenModel"), 1, GL_FALSE, glm::value_ptr(tenModel));
			//glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));



			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		/*float timevalue = glfwgettime();
		float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;

		int vertexcolorlocation = glgetuniformlocation(shaderprogram, "ourcolor");

		gluseprogram(shaderprogram);

		gluniform4f(vertexcolorlocation, 0, greenvalue, 0, 1.0f);*/

		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);








		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPosition();

	}


	glfwTerminate();

	return 0;





	/*int var1;
	int var2;
	int var3;*/

	/*char var1[1];
	char var2[1];
	char var3[1];

	cout << &var1 <<endl;
	cout << &var2 << endl;
	cout << &var3 << endl;*/

	/*int var = 20;
	int* ip;

	ip = &var;

	cout << var << endl;
	cout << ip << endl;
	cout << *ip << endl;*/

	/*int var = 10;

	std::cout << var;*/




}

//using namespace std;

//int main()
//{
//    cout << "type: \t\t" << "************size**************" << endl;
//    cout << "bool: \t\t" << "��ռ�ֽ�����" << sizeof(bool);
//    cout << "\t���ֵ��" << (numeric_limits<bool>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<bool>::min)() << endl;
//    cout << "char: \t\t" << "��ռ�ֽ�����" << sizeof(char);
//    cout << "\t���ֵ��" << (numeric_limits<char>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<char>::min)() << endl;
//    cout << "signed char: \t" << "��ռ�ֽ�����" << sizeof(signed char);
//    cout << "\t���ֵ��" << (numeric_limits<signed char>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<signed char>::min)() << endl;
//    cout << "unsigned char: \t" << "��ռ�ֽ�����" << sizeof(unsigned char);
//    cout << "\t���ֵ��" << (numeric_limits<unsigned char>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<unsigned char>::min)() << endl;
//    cout << "wchar_t: \t" << "��ռ�ֽ�����" << sizeof(wchar_t);
//    cout << "\t���ֵ��" << (numeric_limits<wchar_t>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<wchar_t>::min)() << endl;
//    cout << "short: \t\t" << "��ռ�ֽ�����" << sizeof(short);
//    cout << "\t���ֵ��" << (numeric_limits<short>::max)();
//    cout << "\t\t��Сֵ��" << (numeric_limits<short>::min)() << endl;
//    cout << "int: \t\t" << "��ռ�ֽ�����" << sizeof(int);
//    cout << "\t���ֵ��" << (numeric_limits<int>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;
//    cout << "unsigned: \t" << "��ռ�ֽ�����" << sizeof(unsigned);
//    cout << "\t���ֵ��" << (numeric_limits<unsigned>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<unsigned>::min)() << endl;
//    cout << "long: \t\t" << "��ռ�ֽ�����" << sizeof(long);
//    cout << "\t���ֵ��" << (numeric_limits<long>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<long>::min)() << endl;
//    cout << "unsigned long: \t" << "��ռ�ֽ�����" << sizeof(unsigned long);
//    cout << "\t���ֵ��" << (numeric_limits<unsigned long>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<unsigned long>::min)() << endl;
//    cout << "double: \t" << "��ռ�ֽ�����" << sizeof(double);
//    cout << "\t���ֵ��" << (numeric_limits<double>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<double>::min)() << endl;
//    cout << "long double: \t" << "��ռ�ֽ�����" << sizeof(long double);
//    cout << "\t���ֵ��" << (numeric_limits<long double>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<long double>::min)() << endl;
//    cout << "float: \t\t" << "��ռ�ֽ�����" << sizeof(float);
//    cout << "\t���ֵ��" << (numeric_limits<float>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<float>::min)() << endl;
//    cout << "size_t: \t" << "��ռ�ֽ�����" << sizeof(size_t);
//    cout << "\t���ֵ��" << (numeric_limits<size_t>::max)();
//    cout << "\t��Сֵ��" << (numeric_limits<size_t>::min)() << endl;
//    cout << "string: \t" << "��ռ�ֽ�����" << sizeof(string) << endl;
//    // << "\t���ֵ��" << (numeric_limits<string>::max)() << "\t��Сֵ��" << (numeric_limits<string>::min)() << endl;  
//    cout << "type: \t\t" << "************size**************" << endl;
//    return 0;
//}