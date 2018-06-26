// basicSetup.cpp : Template code for setting up window gen and input handling.
//

#include "stdafx.h"
#include <iostream>
#include <glad.h> //Always include glad.h before other opengl header files
#include <glfw3.h>

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

	//Render Loop
	while (!glfwWindowShouldClose(window)) {
		//Input
		processInput(window);

		//Rendering code

		//Check for call events and swap buffers
		glfwSwapBuffers(window);//Swap buffer that contains colours to draw to screen
		glfwPollEvents(); //Poll for keyboard/mouse/joystick events
	}

	glfwTerminate();
	return 0;
// basicSetup.cpp : Template code for setting up window gen and input handling.
//

#include "stdafx.h"
#include <iostream>
#include <glad.h> //Always include glad.h before other opengl header files
#include <glfw3.h>

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

	//Render Loop
	while (!glfwWindowShouldClose(window)) {
		//Input
		processInput(window);

		//Rendering code

		//Check for call events and swap buffers
		glfwSwapBuffers(window);//Swap buffer that contains colours to draw to screen
		glfwPollEvents(); //Poll for keyboard/mouse/joystick events
	}

	glfwTerminate();
	return 0;
}