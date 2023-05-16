#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

int i = 0;

const unsigned int width = 800;
const unsigned int height = 800;

//                                                    X       Y

GLfloat vertices[] =
{
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.5f, 0.75f,     0.0f, -1.0f, 0.0f, // Bottom side		prawa dó³				 lewa dó³			 0.25f, 0.75f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.25f, 0.75f,      0.0f, -1.0f, 0.0f, // Bottom side		lewa dó³				 lewa góra			0.25f, 1.0f,	
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.25f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side			lewa góra				 prawa góra				 0.5f, 1.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.5f, 1.0f,     0.0f, -1.0f, 0.0f, // Bottom side		prawa góra				 prawa dó³				0.5f, 0.75f,


	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	0.25f, 0.75f,       0.0f, 1.0f, 0.0f, // Top side		 0.0f, 0.75f,
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.75f,     0.0f, 1.0f, 0.0f, // Top side			 0.0f, 1.0f, 
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	  0.0f, 1.0f,      0.0f, 1.0f, 0.0f, // Top side		0.25f, 1.0f, 
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.25f, 1.0f,      0.0f, 1.0f, 0.0f, // Top side		 0.25f, 0.75f, 

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.25f, 0.5f,      0.0f, 0.0f, 1.0f, // Front side		0.0f, 0.5f, 
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.5f,      0.0f, 0.0f, 1.0f, // Front side		0.0f, 0.75f,
	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.75f,      0.0f, 0.0f, 1.0f, // Front side		0.25f, 0.75f,  
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.25f, 0.75f,      0.0f, 0.0f, 1.0f, // Front side		0.25f, 0.5f, 

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.5f,	 -1.0f, 0.0f, 0.0f, // Left side	0.5f, 0.5f,		 0.75f, 0.5f,
	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	 0.75f, 0.5f,		 -1.0f, 0.0f, 0.0f, // Left side	0.5f, 0.75f,
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.75f, 0.75f,	 -1.0f, 0.0f, 0.0f,	// Left side	 0.75f, 0.75f,		 1.0f, 0.75f,
	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.75f,	 -1.0f, 0.0f, 0.0f, // Left side	 0.75f, 0.5f,


	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.5f, 0.5f,      0.0f, 0.0f, -1.0f, //Back side		0.25f, 0.5f, 
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f, 	  0.75f, 0.5f,      0.0f, 0.0f, -1.0f, //Back side		0.25f, 0.75f,		 0.5f, 0.5f, 
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f, 	 0.75f, 0.75f,       0.0f, 0.0f, -1.0f, //Back side		0.5f, 0.75f, 
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.5f, 0.75f,      0.0f, 0.0f, -1.0f, //Back side		0.5f, 0.5f		0.75f, 0.75f, 

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.25f, 0.5f,		  1.0f, 0.0f, 0.0f, // Right side		0.75f, 0.5f,			0.5f, 0.5f,	
	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	  0.5f, 0.5f,		  1.0f, 0.0f, 0.0f, // Right side		0.75f, 0.75f,			1.0f, 0.5f,	
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.5f, 0.75f,	  1.0f, 0.0f, 0.0f, // Right side		1.0f, 0.75f,			0.25f, 0.75f,
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.25f, 0.75f,	  1.0f, 0.0f, 0.0f, // Right side		1.0f, 0.5f,				0.75f, 0.75f,

};

GLuint indices[] =
{
	0, 1, 2,	// Bottom side
	0, 2, 3,	// Bottom side
	4, 5, 6,	// Top side
	4, 6, 7,	// Top side
	8, 9, 10,   // Left side 
	8, 10, 11,  // Left side
	12, 13, 14, // Right side
	12, 14, 15, // Right side
	16, 17, 18, // Front side
	16, 18, 19,	// Front side
	20, 21, 22, // Back side
	20, 22, 23  // Back side
};

GLfloat lightVertices[] =
{
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);



	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(vertices, sizeof(vertices));
	EBO EBO2(indices, sizeof(indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	//Ziemia
	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(vertices, sizeof(vertices));
	EBO EBO3(indices, sizeof(indices));
	VAO3.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	//mars

	VAO VAO4;
	VAO4.Bind();
	VBO VBO4(vertices, sizeof(vertices));
	EBO EBO4(indices, sizeof(indices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	//Jowisz

	VAO VAO5;
	VAO5.Bind();
	VBO VBO5(vertices, sizeof(vertices));
	EBO EBO5(indices, sizeof(indices));
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();


	//Saturn

	VAO VAO6;
	VAO6.Bind();
	VBO VBO6(vertices, sizeof(vertices));
	EBO EBO6(indices, sizeof(indices));
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();

	//Uran

	VAO VAO7;
	VAO7.Bind();
	VBO VBO7(vertices, sizeof(vertices));
	EBO EBO7(indices, sizeof(indices));
	VAO7.LinkAttrib(VBO7, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO7.LinkAttrib(VBO7, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO7.LinkAttrib(VBO7, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO7.LinkAttrib(VBO7, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO7.Unbind();
	VBO7.Unbind();
	EBO7.Unbind();

	//Neptun

	VAO VAO8;
	VAO8.Bind();
	VBO VBO8(vertices, sizeof(vertices));
	EBO EBO8(indices, sizeof(indices));
	VAO8.LinkAttrib(VBO8, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO8.LinkAttrib(VBO8, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO8.LinkAttrib(VBO8, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO8.LinkAttrib(VBO8, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO8.Unbind();
	VBO8.Unbind();
	EBO8.Unbind();


	//slonce


	VAO VAO9;
	VAO9.Bind();
	VBO VBO9(vertices, sizeof(vertices));
	EBO EBO9(indices, sizeof(indices));
	VAO9.LinkAttrib(VBO8, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO9.LinkAttrib(VBO8, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO9.LinkAttrib(VBO8, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO9.LinkAttrib(VBO8, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO9.Unbind();
	VBO9.Unbind();
	EBO9.Unbind();





	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(250.0f);

	//merkury

	glm::vec3 pyramidPos = glm::vec3(30.0f, 0.0f, -14.0f);
	glm::mat4 pyramidModel = glm::mat4(0.40f);

	//wenus

	glm::vec3 pyramidPos2 = glm::vec3(-50.0f, 0.0f, 48.0f);
	glm::mat4 pyramidModel2 = glm::mat4(1.2f);

	//ziemia
	glm::vec3 ziemiaPos = glm::vec3(60.0f, 0.0f, -70.0f);
	glm::mat4 ziemiaModel = glm::mat4(1.2f);


	//mars
	glm::vec3 marsPos = glm::vec3(-84.0f, 0.0f,-90.0f);
	glm::mat4 marsModel = glm::mat4(0.6f);


	//jowisz
	glm::vec3 jowiszPos = glm::vec3(-120.0f, -7.0f, 96.0f);
	glm::mat4 jowiszModel = glm::mat4(14.0f);


	//Saturn
	glm::vec3 saturnPos = glm::vec3(150.0f, -6.0f, -140.0f);//
	glm::mat4 saturnModel = glm::mat4(12.0f);



	//Uran
	glm::vec3 uranPos = glm::vec3(170.0f, 0.0f, -180.0f);//
	glm::mat4 uranModel = glm::mat4(0.51f);


	//Neptun
	glm::vec3 neptunPos = glm::vec3(200.0f, 0.0f, -200.0f);//
	glm::mat4 neptunModel = glm::mat4(0.49f);

	glm::vec3 skyPos = glm::vec3(0.0f, -250.0f, 0.0f);//
	glm::mat4 skyModel = glm::mat4(500.0f);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	Texture popMerkury("merkury.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popMerkury.texUnit(shaderProgram, "tex0", 0);

	Texture popWenus("wenus.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popWenus.texUnit(shaderProgram, "tex0", 0);

	Texture popZiemia("ziemia.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popZiemia.texUnit(shaderProgram, "tex0", 0);

	Texture popMars("mars.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popMars.texUnit(shaderProgram, "tex0", 0);

	//jowisz
	Texture popJowisz("jowisz.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popJowisz.texUnit(shaderProgram, "tex0", 0);

	//saturn
	Texture popSaturn("saturn.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popSaturn.texUnit(shaderProgram, "tex0", 0);

	//uran
	Texture popUran("uran.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popUran.texUnit(shaderProgram, "tex0", 0);

	//neptun
	Texture popNeptun("neptun.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popNeptun.texUnit(shaderProgram, "tex0", 0);

	//skybox

	Texture popSky("sky.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popSky.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 100.0f, 0.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);


		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), pyramidPos.x, pyramidPos.y, pyramidPos.z);
		popMerkury.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel2));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), pyramidPos2.x, pyramidPos2.y, pyramidPos2.z);
		popWenus.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Ziemai
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(ziemiaModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), ziemiaPos.x, ziemiaPos.y, ziemiaPos.z);
		popZiemia.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//mars
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(marsModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), marsPos.x, marsPos.y, marsPos.z);
		popMars.Bind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//jowisz

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(jowiszModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), jowiszPos.x, jowiszPos.y, jowiszPos.z);
		popJowisz.Bind();
		VAO5.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		//saturn

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(saturnModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), saturnPos.x, saturnPos.y, saturnPos.z);
		popSaturn.Bind();
		VAO6.Bind();//
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		//uran

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(uranModel));//
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), uranPos.x, uranPos.y, uranPos.z);
		popUran.Bind();
		VAO7.Bind();//
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//neptun

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(neptunModel));//
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), neptunPos.x, neptunPos.y, neptunPos.z);
		popNeptun.Bind();
		VAO8.Bind();//
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		//sky
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(skyModel));//
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "offset"), skyPos.x, skyPos.y, skyPos.z);
		popSky.Bind();
		VAO9.Bind();//
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	popMars.Delete();
	popWenus.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}