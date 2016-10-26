#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

#include <GLFW/glfw3.h>

class Cube
{
	
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	public:
		Cube(); //Constructeur par défaut
		Cube(float pt);//Constructeur pour un cube de taille spécifique 
		GLuint render() const;//Retourne le VAO
		void deleteVertexBuffer();//Suppression des Vertex Buffer
};
  
#endif