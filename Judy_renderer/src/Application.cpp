#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include "Globals.h"
#include "RendererShaders.h"

int main(void)
{
	std::cout << "Starting Konkol Engine please wait..." << std::endl;
	std::cout << "Initializing: Judy Renderer..." << std::endl;
	GLFWwindow* window;
	global_variables global;
	RendererShaders shaders;



	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(global.screenWidith, global.screenHeight, "Judy Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	std::cout << "Loading shaders" << std::endl;
	shaders.LoadShaders(); //loads shaders to memory



	float vertices1[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices1[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
		2, 3, 0
	};

	float vertices2[] = {
	 0.2f,  0.4f, 0.0f,  // top right
	 0.4f, -0.4f, 0.0f,  // bottom right
	-0.4f, -0.4f, 0.0f,  // bottom left
	-0.4f,  0.4f, 0.0f   // top left 
	};
	unsigned int indices2[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
		2, 3, 0
	};

	


	std::string tect2 = shaders.GetFragmentShader(std::string("main"));
	const char* mainFragmentShader = tect2.c_str();
	std::string tect = shaders.GetVertexShader(std::string("main"));
	const char* mainVertexShader = tect.c_str();


	GLint result = GL_FALSE;
	int logLength;

	std::cout << "Compiling shaders: please wait..." << std::endl;
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &mainVertexShader , NULL);
	glCompileShader(vertexShader);


	//chceck shader

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(vertexShader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;

	//
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &mainFragmentShader, NULL);
	glCompileShader(fragmentShader);



	// Check fragment shader

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragShaderError[0]);
	std::cout << &fragShaderError[0] << std::endl;

	unsigned int fragmentShader1;
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &mainFragmentShader, NULL);
	glCompileShader(fragmentShader1);


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);




	unsigned int VAO[2]; //vertex attribute
	glGenVertexArrays(2, VAO);
	


	unsigned int EBO[2]; //EBO lol, zapomniałem co to było, ale to przechowuje informacje o kolejności trójkątów
	glGenBuffers(2, EBO);

	unsigned int VBO[2]; //Vertex buffer 
	glGenBuffers(1, VBO);





	//send data to GPU
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);



	
	glUseProgram(shaderProgram);







	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Calls

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		


		//Judy->DrawCall OBJ1
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);


		//Judy->DrawCall OBJ2
		//glUseProgram(shaderProgram1);
		//glBindVertexArray(VAO[1]);
		//glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, (void*)0);
		//glBindVertexArray(0);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}