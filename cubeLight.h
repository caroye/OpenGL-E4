#ifndef CUBELIGHT_H
#define CUBELIGHT_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

#include <GLFW/glfw3.h>

class CubeLight
{
	
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	public:
		CubeLight();
		CubeLight(float pt);
		GLuint render() const;
		void deleteVertexBuffer();
};
  
#endif