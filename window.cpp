/* For Linux users compiling with GCC the following command line options might
 help you compile the project -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi. 
 Not correctly linking the corresponding libraries will generate many undefined 
 reference errors. */

 /*gcc window.cpp -o window -lGLEW -lGLU -lGL -I/usr/include/GL 
 -I/usr/include/libdrm -lglfw -lstdc++
*/

/*Clavier:
U,I,O -> +x,y,z déplacement
J,K,L -> -x,y,z déplacement
V,B,N -> rotation autour des axes x,y,z 
*/



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "cube.h"
#include "camera.h"
//#include "clavier.h"

#define WIDTH 1000
#define HEIGHT 1000
#define nullptr NULL
#define pnt 0.5f

//Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
glm::vec3 vecPos(float x, float y, float z);
void setPos();
void setRot();

//Position initiale camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX =  WIDTH  / 2.0;
GLfloat lastY =  HEIGHT / 2.0;
bool keys[1024];	//Les touches du clavier/souris : pour le déplacement de la caméra
bool firstMouse=true;
//Position du cube
float xCube = 1.0f;
float yCube = 1.0f;
float zCube = 1.0f;

float rxCube = 1.0f;
float ryCube = 1.0f;
float rzCube = 1.0f;
float angle = 0.1f;

int RxCube = 1.0f;
int RyCube = 1.0f;
int RzCube = 1.0f;

//Pour calculer la vitesse de la caméra
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame*/


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


	//setup OpenGL option
	glEnable(GL_DEPTH_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);

	//create forme 
	//rendu =========================================================================
		Cube monCube;
		Shader monShader("D:/ESIEE/E4/PR-IT-4104/OpenGL-E4-archi_camera/OpenGL-E4-archi/VertexShader.vs","D:/ESIEE/E4/PR-IT-4104/OpenGL-E4-archi_camera/OpenGL-E4-archi/FragmentShader.frag");
		GLuint VAO_w = monCube.render();


	//reste ouverte tant que pas choisi de cloturer
	while(!glfwWindowShouldClose(window)){
	//while(key != 'q'){

		//Creation matrice MVP
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;



		model = glm::rotate(model, angle, glm::vec3(rxCube, ryCube, rzCube));
		model = glm::translate(model, glm::vec3(xCube, yCube, zCube));
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

		//Calcul de la vitesse de déplacement de la caméra
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame; 
		//vérifie et appelle les évènements
		glfwPollEvents();
		do_movement();
		setPos();
		setRot();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		
		// 5. Draw the object
		monShader.Use();
		
		glBindVertexArray(VAO_w);
		glDrawArrays(GL_TRIANGLES, 0, 36); //pour un seul triangle
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //pour plusieurs triangles
		
		//delie le VAO
		glBindVertexArray(0);

		//======================================================================================
		//échange les buffers
		glfwSwapBuffers(window);
	}

	//libere la memoire allouee aux buffers et vertex array
    monCube.deleteVertexBuffer();

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

glm::vec3 vecPos(float x, float y, float z)
{
	return glm::vec3(x,y,z);
}

//Change la position du cube
void setPos()
{
	if (keys[GLFW_KEY_U])
		xCube += 0.1f;
	if (keys[GLFW_KEY_I])
		yCube += 0.1f;
	if (keys[GLFW_KEY_O])
		zCube += 0.1f;
	if (keys[GLFW_KEY_J])
		xCube -= 0.1f;
	if (keys[GLFW_KEY_K])
		yCube -= 0.1f;
	if (keys[GLFW_KEY_L])
		zCube -= 0.1f;
}

//Change la rotation du cube
void setRot()
{
	if (keys[GLFW_KEY_V])//rotation sur X
	{
		angle += 0.01f;
		rxCube = cos(angle) + (RxCube^2)*(1 - cos(angle));
		ryCube = ryCube*rxCube*(1 - cos(angle)) + rzCube*sin(angle);
		rzCube = rxCube*rzCube*(1 - cos(angle)) - ryCube*sin(angle);
	}
	if (keys[GLFW_KEY_B])//rotation sur Y
	{
		angle += 0.01f;
		rxCube = ryCube*rxCube*(1 - cos(angle)) - rzCube*sin(angle);
		ryCube = cos(angle) + (RyCube ^ 2)*(1 - cos(angle));
		rzCube = ryCube*rzCube*(1 - cos(angle)) - rxCube*sin(angle);
	}
	if (keys[GLFW_KEY_N])//rotation sur Z
	{
		angle += 0.01f;
		rxCube = rxCube*rzCube*(1 - cos(angle)) + ryCube*sin(angle);
		ryCube = ryCube*rzCube*(1 - cos(angle)) - rxCube*sin(angle);
		rzCube = cos(angle) + (RzCube ^ 2)*(1 - cos(angle));
	}
}