#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
 
#include <GLFW/glfw3.h>

#include "cube.h"

#define pnt 0.5f

/*Cube::Cube() : vertices_cube{
		pnt, pnt, 0.0f,
		pnt, -pnt, 0.0f,
		-pnt, -pnt, 0.0f,
		-pnt, pnt, 0.0f,
		0.0f, 1.0f, 0.0f,
	}, indices_cube{
		0, 1, 3,   // First Triangle
		1, 2, 3,    // Second Triangle
		3, 0, 4
	} {
}*/
/*Cube::Cube(void){
	this.vertices_cube = {
		pnt, pnt, 0.0f,
		pnt, -pnt, 0.0f,
		-pnt, -pnt, 0.0f,
		-pnt, pnt, 0.0f,
		0.0f, 1.0f, 0.0
	};
	this.indices_cube = {
		0, 1, 3,   // First Triangle
		1, 2, 3,    // Second Triangle
		3, 0, 4
	}
}

std::vector<GLfloat> Cube::getVertices(){
	return this->vertices_cube;
}

GLuint Cube::getSizeofIndices(){
	GLuint taille = sizeof(this->indices_cube);
	std::cout << "taille: " << taille <<std::endl;
	return taille;
}
/*std::vector<GLuint> *//*GLuint* Cube::getIndices(){
	return this->indices_cube;
}*/

Cube::Cube(){
	GLfloat vertices_triangle[] = {
		//triangle 
		/*
	    -pnt, -pnt, 0.0f,
	     pnt, -pnt, 0.0f,
	     0.0f,  pnt, 0.0f
	     //*/
	     //*carré
	     pnt, pnt, 0.0f,
	     pnt, -pnt, 0.0f,
	     -pnt, -pnt, 0.0f,
	     -pnt, pnt, 0.0f,
	     0.0f, 1.0f, 0.0f,
	}; //*/
	//pour le carré 
	GLuint indices[] = {  // Note that we start from 0!
	    0, 1, 3,   // First Triangle
	    1, 2, 3,    // Second Triangle
	    3, 0, 4
	};//*/

	//création EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);

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


}

void Cube::deleteVertexBuffer(){
			glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}