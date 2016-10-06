#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
 
#include <GLFW/glfw3.h>

#include "cube.h"

#define pnt 0.5f

Cube::Cube(){
	this->vertices_cube[] = {
		pnt, pnt, 0.0f,
		pnt, -pnt, 0.0f,
		-pnt, -pnt, 0.0f,
		-pnt, pnt, 0.0f,
		0.0f, 1.0f, 0.0f,
	}

	this->indices_cube[] = {
		0, 1, 3,   // First Triangle
		1, 2, 3,    // Second Triangle
		3, 0, 4
	}
}

GLFloat Cube::getVertices(){
	return this->vertices_cube[];
}

GLuint Cube::getSizeofIndices(){
	GLuint taille = sizeof(this->indices_cube[]);
	std::cout << "taille: " << taille <<std::endl;
	return taille;
}
GLuint Cube::getIndices(){
	return this->indices_cube[];
}