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
	/*private:
		std::vector<GLfloat> vertices_cube[3*5];
		std::vector<GLuint> indices_cube[3*3];
		
	public:
	  	// The program ID
	//	GLuint Program;
		// Constructor reads and builds the shader
	//	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	  	// Use the program
	// 	void Use();
		Cube();
		std::vector<GLfloat> getVertices();
		//std::vector<GLuint> getIndices();
		GLuint* getIndices();
		GLuint getSizeofIndices();*/
	private:
		GLuint VAO;
		//Gluint VBO;
		GLuint EBO;
	public:
		Cube();
		Cube(int pnt);
		//void render(mat4* transform);
		void deleteVertexBuffer();
};
  
#endif