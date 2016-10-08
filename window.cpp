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

#include "shader.h"


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
		GLfloat vertices_triangle[] = {
			//triangle 
			/*
		    -pnt, -pnt, 0.0f,
		     pnt, -pnt, 0.0f,
		     0.0f,  pnt, 0.0f
		     //*/
		     //carré
		     pnt, pnt, 0.0f,
		     pnt, -pnt, 0.0f,
		     -pnt, -pnt, 0.0f,
		     -pnt, pnt, 0.0f,
		     0.0f, 1.0f, 0.0f,

		}; 

		//pour le carré
		GLuint indices[] = {  // Note that we start from 0!
		    0, 1, 3,   // First Triangle
		    1, 2, 3,    // Second Triangle
		    3, 0, 4
		};
		GLuint EBO;
		glGenBuffers(1, &EBO);		


		//create vertex
		GLuint VBO;
		glGenBuffers(1, &VBO);
		////copie vertices array in buffere
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);

		

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
		    // 2. Copy our vertices array in a buffer for OpenGL to use
		  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//ELEMENT , VBO->EBO
		  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //ELEMENT, vertices_triangle ->indices
		    // 3. Then set our vertex attributes pointers
		    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		    glEnableVertexAttribArray(0);  
		//4. Unbind the VAO
		glBindVertexArray(0);
		// ..:: Drawing code (in Game loop) :: ..


	//reste ouverte tant que pas choisi de cloturer
	while(!glfwWindowShouldClose(window)){
		//vérifie et appelle les évènements
		glfwPollEvents();

		// 5. Draw the object
		monShader.Use();
		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//======================================================================================
		//échange les buffers
		glfwSwapBuffers(window);
	}

	 // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
