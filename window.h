/* For Linux users compiling with GCC the following command line options might
 help you compile the project -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi. 
 Not correctly linking the corresponding libraries will generate many undefined 
 reference errors. */

 /*gcc window.cpp -o window -lGLEW -lGLU -lGL -I/usr/include/GL 
 -I/usr/include/libdrm -lglfw -lstdc++
*/



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "cubeLight.h"

#define WIDTH 800
#define HEIGHT 600
#define nullptr NULL
#define pnt 0.5f

//Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

//Position initiale camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX =  WIDTH  / 2.0;
GLfloat lastY =  HEIGHT / 2.0;
bool keys[1024];	//Les touches du clavier/souris : pour le déplacement de la caméra
bool firstMouse=true;


//Pour calculer la vitesse de la caméra
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame*/

//Origine de la source de lumière :
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);