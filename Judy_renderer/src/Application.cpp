#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Globals.h"
#include "Shaders.h"

int main(void)
{
	GLFWwindow* window;
	global_variables global;
	renderer_shaders shader;



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

	


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shader.vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shader.fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	unsigned int fragmentShader1;
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &shader.fragmentShaderSource1, NULL);
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



	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Calls

		//Judy->DrawCall OBJ1
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);


		//Judy->DrawCall OBJ2
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}