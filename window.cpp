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
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shader.h"
#include "cube.h"

#define WIDTH 800
#define HEIGHT 600
#define nullptr NULL
#define pnt 0.5f


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



	//create forme 
	//rendu =========================================================================
		Cube monCube;
		Shader monShader("/home/caroye/Documents/OpenGL/OpenGL-E4/VertexShader.vs","/home/caroye/Documents/OpenGL/OpenGL-E4/FragmentShader.frag");
		GLuint VAO_w = monCube.render();

	//reste ouverte tant que pas choisi de cloturer
	while(!glfwWindowShouldClose(window)){
		//vérifie et appelle les évènements
		glfwPollEvents();

		// 5. Draw the object
		monShader.Use();
		
		glBindVertexArray(VAO_w);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //pour un seul triangle
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //pour plusieurs triangles
		
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
