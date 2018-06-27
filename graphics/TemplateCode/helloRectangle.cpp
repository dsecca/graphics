// helloRectangle.cpp : Basically all buffers we'll need ever in openGL
//

#include "stdafx.h"
#include <iostream>
#include <glad.h> //Always include glad.h before other opengl header files
#include <glfw3.h>
#include <string>

//Handling of user window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//Handling user input
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//Vertex Shader
const char* vertexShaderSource[] = { "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0" };

//Fragment shader
const char* fragmentShaderSource[] = { "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0" };


int main()
{
	//GLFW Window initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set window parameters and create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Make the window context the main context of the current thread
	glfwMakeContextCurrent(window);

	//Initialize GLAD before calling any openGL function
	//Here we load the address of openGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Tell openGl what the size is of the rendering window
	glViewport(0, 0, 800, 600);

	//Let GLFW know what function to call when user resizes window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//Build and Compile the Shader programs
	//-------------------------------------
	//Compile Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Compile Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Check for shader compile time errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Link shader programs
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check for shader linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Delete shader objects since shader program is linked and created
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Rectangle Coordinates
	float vertices[] = {
		0.5f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f
	};

	//Specify order in which to draw each vertex
	//Rectangle indices
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};


	//Create memory on GPU to store vertex data.
	//We tell OpenGL how to access it by creating
	//a vertex buffer object and assigning it an ID
	//Create element buffer object to store the indices
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	//Bind the VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Copy indices to the buffer's memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Tell openGL how to interpret the vertex data
	//Create position attribute (If we had texture or something else, we'd create another attribute pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind VBO then VAO since the data is copied
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Tell openGL in what way it can draw the shapes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Render Loop
	while (!glfwWindowShouldClose(window)) {
		//Input
		processInput(window);

		//Rendering code
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell openGL to use the shader program we've just created
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//Used to draw from element buffer object
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//Used to draw directly from VAO/VBO
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//Check for call events and swap buffers
		glfwSwapBuffers(window);//Swap buffer that contains colours to draw to screen
		glfwPollEvents(); //Poll for keyboard/mouse/joystick events
	}

	glfwTerminate();
	return 0;
}

