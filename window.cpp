/* For Linux users compiling with GCC the following command line options might
help you compile the project -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi. 
Not correctly linking the corresponding libraries will generate many undefined 
reference errors. */

/*gcc window.cpp -o window -lGLEW -lGLU -lGL -I/usr/include/GL 
-I/usr/include/libdrm -lglfw -lstdc++
*/



#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600
#define nullptr NULL
#define pnt 0.5f

//Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

//Position initiale camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX =  WIDTH  / 2.0;
GLfloat lastY =  HEIGHT / 2.0;
bool keys[1024];	//Les touches du clavier/souris : pour le déplacement de la caméra
bool firstMouse=true;


//Pour calculer la vitesse de la caméra
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main(){
	glfwInit(); //initialise GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//initialisation fenêtre
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 


	//initialisation glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//choix de la taille de la fenêtre
	int width = WIDTH, height = HEIGHT;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	//create forme 
	//rendu =========================================================================
	GLfloat vertices[] = {
		//triangle 
		/*
		-pnt, -pnt, 0.0f,
		pnt, -pnt, 0.0f,
		0.0f,  pnt, 0.0f
		//
		//carré
		pnt, pnt, 0.0f,
		pnt, -pnt, 0.0f,
		-pnt, -pnt, 0.0f,
		-pnt, pnt, 0.0f,
		0.0f, 1.0f, 0.0f,
		*/
		//Cube 3D
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f, 
	}; 

	/*//pour le carré
	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3,    // Second Triangle
	3, 0, 4
	};
	GLuint EBO;
	glGenBuffers(1, &EBO);		
	*/
	//create vertex
	GLuint VBO;
	glGenBuffers(1, &VBO);
	////copie vertices array in buffere
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	Shader monShader("/home/caroye/Documents/OpenGL/OpenGL-E4/VertexShader.vs","/home/caroye/Documents/OpenGL/OpenGL-E4/FragmentShader.frag");

	//liaison des attributs du vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); 

	//create vertex array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO); 

	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
	// 1. Bind Vertex Array Object
	glBindVertexArray(VAO);
	/*    // 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//ELEMENT , VBO->EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //ELEMENT, vertices_triangle ->indices*/
	// 3. Then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);  
	//4. Unbind the VAO
	glBindVertexArray(0);
	// ..:: Drawing code (in Game loop) :: ..


	//reste ouverte tant que pas choisi de cloturer
	while(!glfwWindowShouldClose(window)){
		//Calcul de la vitesse de déplacement de la caméra
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame; 
		//vérifie et appelle les évènements
		glfwPollEvents();
		do_movement();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// 5. Draw the object
		monShader.Use();

		//Creation matrice MVP
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		view = camera.GetViewMatrix(); 
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		//Get the uniforms locations
		GLint modelLoc = glGetUniformLocation(monShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(monShader.Program, "view");
		GLint projLoc = glGetUniformLocation(monShader.Program, "projection");

		//Pass the matrices to the shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//======================================================================================
		//échange les buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
			keys[key] = true;
		else if(action == GLFW_RELEASE)
			keys[key] = false;  
	}
}
void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 5.0f*deltaTime;
	if(keys[GLFW_KEY_Z])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if(keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if(keys[GLFW_KEY_Q])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if(keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}