#ifndef CUBELIGHT_H
#define CUBELIGHT_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#include <GL/glew.h> 

#include <GLFW/glfw3.h>

class CubeLight
{
	
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	public:
		CubeLight();//Constructeur par défaut
		CubeLight(float pt);//Constructeur d'un cube d'une taille spécifique
		GLuint render() const;//Retourne le VAO
		void deleteVertexBuffer();//Suppresion des Vertex Buffer
};
  
#endif