#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
  
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

#include <GLFW/glfw3.h>

class Cube
{
	
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	public:
		Cube();
		Cube(float pt);
		GLuint render() const;
		void deleteVertexBuffer();
};
  
#endif