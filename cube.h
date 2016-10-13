#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
  
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

#include <GlFW/glfw3.h>

class Cube
{
	
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	public:
		Cube();
		//Cube(int pnt);
		GLuint render() const;
		void deleteVertexBuffer();
};
  
#endif