#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> 

#include <GLFW/glfw3.h>

class Shader
{
public:
	// L'identifieur du programme, pour récupérer le programme dans le main
	GLuint Program;

	// Constructeur du shader, composé d'un vertex shader et d'un fragment shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Lancement du programme
	void Use();
};

#endif