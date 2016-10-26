#ifndef CAMERA_H
#define CAMERA_H
#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



//D�fini les options possible pour les mouvements de la cam�ra. Utilis�s comme abstraits pour rester en dehors des  m�thodes d'entr�es sp�cifiques de la fen�tre syst�me.
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

//Valeur de la cam�ra par d�faut
const GLfloat YAW        = -90.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;


//Classe cam�ra abstraite: ex�cute et calcule les angles d'Euler,vecteurs et matrices correspondantes 
class Camera
{
public:
    //Attribut
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    //Angles d'Euler
    GLfloat Yaw;
    GLfloat Pitch;

    //Option
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

     //Constructeur avec vecteur
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    
    //Constructeur avec des scalaires
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
    

	//Retourne la matrice vue calcul�e avec les angles d'Euler et la matrice LookAt
    glm::mat4 GetViewMatrix();

	//Execution des entr�es en provenance du clavier, permet de d�placer la cam�ra
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	//Ex�cution des entr�es en provenance de la souris, permet d'orienter la cam�ra selon une direction
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
  
	//Ex�cution des entr�es en provenance du scroll de la souris
    void ProcessMouseScroll(GLfloat yoffset);

private:
	//Calcule l'actuel vecteur 'Front' qui r�sulte des angles 'Pitch' et 'Yaw'
    void updateCameraVectors();
};

#endif
