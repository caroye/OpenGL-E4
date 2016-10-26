#include "camera.h"

// Constructeur avec vecteurs
Camera::Camera(glm::vec3 position , glm::vec3 up , GLfloat yaw , GLfloat pitch ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}
// Constructeur avec des scalaires 
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

//Retourne la matrice vue calcul�e avec les angles d'Euler et la matrice LookAt
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

//Execution des entr�es en provenance du clavier, permet de d�placer la cam�ra
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
        this->Position += this->Front * velocity;
    if (direction == BACKWARD)
        this->Position -= this->Front * velocity;
    if (direction == LEFT)
        this->Position -= this->Right * velocity;
    if (direction == RIGHT)
        this->Position += this->Right * velocity;
}

//Ex�cution des entr�es en provenance de la souris, permet d'orienter la cam�ra selon une direction
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw   += xoffset;
    this->Pitch += yoffset;

    //Pour �viter de retourner l'�cran, la valeur du pitch est fix� a 89� m�me si celle ci est sup�rieure
    if (constrainPitch)
    {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }

    //Mise � jour des vecteur 'Front' et 'Right' en tenant compte de la mise � jour des angles d'Euler
    this->updateCameraVectors();
}

//Ex�cution des entr�es en provenance du scroll de la souris
void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
        this->Zoom -= yoffset;
    if (this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if (this->Zoom >= 45.0f)
        this->Zoom = 45.0f;
}

//Calcule l'actuel vecteur 'Front' qui r�sulte des angles 'Pitch' et 'Yaw'
void Camera::updateCameraVectors()
{
    //Calcul du vecteur
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    //Calcul du vecteur 'Right' 
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  //Normalise le vecteur
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
}