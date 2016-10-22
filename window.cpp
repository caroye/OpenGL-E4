#include "window.h"

int main(){
	glfwInit(); //initialise GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//initialisation fenêtre
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

	//initialisation glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	    std::cout << "Failed to initialize GLEW" << std::endl;
	    return -1;
	}

	//choix de la taille de la fenêtre
	int width = WIDTH, height = HEIGHT;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	//setup OpenGL option
	glEnable(GL_DEPTH_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);

	//create forme 
	//rendu =========================================================================
		
		//elo : /home/caroye/Documents/OpenGL/OpenGL-E4/
		//lorkan : U:/PR-4104/Projet_Github/PR-4104/PR-4104/
		//kevin : U:/PR-IT-4104/Lumiere/Lumiere/
		//nico :
		Shader cubeShader("/home/caroye/Documents/OpenGL/OpenGL-E4/VertexShader.vs","/home/caroye/Documents/OpenGL/OpenGL-E4/FragmentShader.frag");
		Shader lampShader("/home/caroye/Documents/OpenGL/OpenGL-E4/lamp.vs","/home/caroye/Documents/OpenGL/OpenGL-E4/lamp.frag");
		Cube monCube;
		CubeLight myLight;
		GLuint VAO_w = monCube.render();
		GLuint lightVAO = myLight.render();


		
	//reste ouverte tant que pas choisi de cloturer
	while(!glfwWindowShouldClose(window)){
		//Plusieurs cubes
		glm::vec3 cubePositions[] = {					//Positions des cubes modifiées, pour des résultats plus probants
			glm::vec3(xCube,yCube,zCube),//glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(xCube2,yCube2,zCube2),//glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(xCube3,yCube3,zCube3),//glm::vec3(0.5f, -1.0f, -2.0f)
		};


		//Calcul de la vitesse de déplacement de la caméra
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame; 
		//vérifie et appelle les évènements
		glfwPollEvents();
		do_movement();		
		setPos();
		setRot();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		cubeShader.Use();
		//Creation matrice MVP
		glm::mat4 model;
		glm::mat4 modelLight;
		glm::mat4 view;
		glm::mat4 projection;

		/*/model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(rxCube, ryCube, rzCube));
		model = glm::translate(model, glm::vec3(xCube, yCube, zCube));//*/

		view = camera.GetViewMatrix();
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		//Get the uniforms locations
		GLint modelLoc = glGetUniformLocation(cubeShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(cubeShader.Program, "view");
		GLint projLoc = glGetUniformLocation(cubeShader.Program, "projection");
		GLint objectColorLoc = glGetUniformLocation(cubeShader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(cubeShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(cubeShader.Program, "lightPos");
		
		GLint indirectLightPos1 = glGetUniformLocation(cubeShader.Program, "indirectLightPos1");				//Une lumière indirecte par cube
		GLint indirectLightPos2 = glGetUniformLocation(cubeShader.Program, "indirectLightPos2");
		GLint indirectLightPos3 = glGetUniformLocation(cubeShader.Program, "indirectLightPos3");

		GLint viwPosLoc = glGetUniformLocation(cubeShader.Program, "viewPos");

		GLint accentuationLoc= glGetUniformLocation(cubeShader.Program, "accentuation");

		
		//Initialisation des attributs de couleur (pour le cube)
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viwPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		
		glUniform3f(indirectLightPos1, cubePositions[0].x, cubePositions[0].y, cubePositions[0].z);
		glUniform3f(indirectLightPos2, cubePositions[1].x, cubePositions[1].y, cubePositions[1].z);
		glUniform3f(indirectLightPos3, cubePositions[2].x, cubePositions[2].y, cubePositions[2].z);

		//Pass the matrices to the shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// 5. Draw the object		
		glBindVertexArray(VAO_w);
		//glDrawArrays(GL_TRIANGLES, 0, 36); //pour un seul triangle
		
		for(GLint i=0; i<3;i++){
			model = glm::rotate(model, angle*i, glm::vec3(rxCube, ryCube, rzCube));
			model = glm::translate(model, cubePositions[i]);
			//*GLfloat*/ angle = 20.0f*i;
			//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			//model = glm::translate(model, glm::vec3(xCube, yCube, zCube));//*/
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		setLum(accentuationLoc);


		//draw light
		lampShader.Use();
		modelLoc=glGetUniformLocation(lampShader.Program, "modelLight");
		viewLoc=glGetUniformLocation(lampShader.Program, "view");
		projLoc=glGetUniformLocation(lampShader.Program, "projection");
		glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
		glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(projection));
		modelLight=glm::mat4();
		modelLight=glm::translate(modelLight,lightPos);
		modelLight=glm::scale(modelLight,glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLight));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//======================================================================================
		//échange les buffers
		glfwSwapBuffers(window);

		//std::cout << "cube 1 x:" << cubePositions[0].x << std::endl;
	}

	//libere la memoire allouee aux buffers et vertex array
    monCube.deleteVertexBuffer();
    myLight.deleteVertexBuffer();

	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
			keys[key] = true;
		else if(action == GLFW_RELEASE)
			keys[key] = false;  
	}
}
void do_movement()
{	
	//elo,kevin:Q->A, Z->W
	// Camera controls
	if(keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if(keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if(keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if(keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if(keys[GLFW_KEY_LEFT_CONTROL])
		camera.ProcessKeyboard(DOWN, deltaTime);
	if(keys[GLFW_KEY_SPACE])
		camera.ProcessKeyboard(UP,deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

//Change la position du cube
void setPos()
{
	if (keys[GLFW_KEY_U])
		xCube += 0.1f;
	if (keys[GLFW_KEY_I])
		yCube += 0.1f;
	if (keys[GLFW_KEY_O])
		zCube += 0.1f;
	if (keys[GLFW_KEY_J])
		xCube -= 0.1f;
	if (keys[GLFW_KEY_K])
		yCube -= 0.1f;
	if (keys[GLFW_KEY_L])
		zCube -= 0.1f;
}

//Change la rotation du cube
void setRot()
{
	if (keys[GLFW_KEY_V])//rotation sur X
	{
		angleX = angleX+0.05f;
		angle = angleX;
		//*
		rxCube = 1.0f;//cos(angle) + (rxCube*rxCube)*(1 - cos(angle));//
		ryCube = 0.0f;//ryCube*rxCube*(1 - cos(angle)) + rzCube*sin(angle);//
		rzCube = 0.0f;//rxCube*rzCube*(1 - cos(angle)) - ryCube*sin(angle);//*/
		/*
		rxCube = xCube;
		ryCube = cos(angleX)*yCube-sin(angleX)*zCube;
		rzCube = sin(angleX)*yCube+cos(angleX)*zCube;//*/
	}
	if (keys[GLFW_KEY_B])//rotation sur Y
	{
		angleY = angleY+0.05f;
		angle = angleY;
		//*
		rxCube = 0.0f;//ryCube*rxCube*(1 - cos(angle)) - rzCube*sin(angle);//
		ryCube = 1.0f;//cos(angle) + (ryCube*ryCube)*(1 - cos(angle));//
		rzCube = 0.0f;//ryCube*rzCube*(1 - cos(angle)) - rxCube*sin(angle);//*/
		/*
		rxCube = cos(angleY)*xCube+sin(angleY)*zCube;
		ryCube = yCube;
		rzCube = -sin(angleY)*xCube+cos(angleY)*zCube;//*/
	}
	if (keys[GLFW_KEY_N])//rotation sur Z
	{
		angleZ = angleZ+0.05f;
		angle = angleZ;
		//*
		rxCube = 0.0f;//rxCube*rzCube*(1 - cos(angle)) + ryCube*sin(angle);//
		ryCube = 0.0f;//ryCube*rzCube*(1 - cos(angle)) - rxCube*sin(angle);//
		rzCube = 1.0f;//cos(angle) + (rzCube*rzCube)*(1 - cos(angle));//*/
		/*
		rxCube = cos(angleZ)*xCube-sin(angleZ)*yCube;
		ryCube = sin(angleZ)*xCube+cos(angleZ)*yCube;
		rzCube = zCube;//*/
	}
}

void setLum(GLint accentuationLoc){
	//elo : P et C
	//autre : KP_ADD et KP_SUBTRACT
	if(keys[GLFW_KEY_P]){
		accentuation+=0.01f;
		glUniform1f(accentuationLoc, accentuation);
	}
	if(keys[GLFW_KEY_C] && accentuation >=0.0f){
		accentuation-=0.01f;
		glUniform1f(accentuationLoc, accentuation);
	}
}