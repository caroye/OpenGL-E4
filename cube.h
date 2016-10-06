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
		GLfloat vertices_cube[];
		GLuint indices_cube[];
	public:
	  	// The program ID
	//	GLuint Program;
		// Constructor reads and builds the shader
	//	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	  	// Use the program
	// 	void Use();
		Cube();
		GLfloat getVertices();
		GLuint getIndices();
		GLuint getSizeofIndices();
};
  
#endif