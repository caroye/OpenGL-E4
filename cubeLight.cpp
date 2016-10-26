#include "cubeLight.h"

#define pnt 0.5f

CubeLight::CubeLight(){
	GLfloat vertices_triangle[] = {
	     /*carré
	     pnt, pnt, 0.0f,
	     pnt, -pnt, 0.0f,
	     -pnt, -pnt, 0.0f,
	     -pnt, pnt, 0.0f,
	     0.0f, 1.0f, 0.0f,*/
	     //Cube 3D création des coordonnées des vertices
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, 0.5f, -0.5f, 
	}; //*/

	//creation des tableaux de Vertex
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//creation du buffer VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copie donnee
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//defini les attributs du tableau de Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

}
CubeLight::CubeLight(float pt){
	GLfloat vertices_triangle[] = {
	     //Cube 3D pour la lumière création des vertices
		-pt, -pt, -pt,
		pt, -pt, -pt,
		pt,  pt, -pt,
		pt,  pt, -pt,
		-pt,  pt, -pt,
		-pt, -pt, -pt,

		-pt, -pt,  pt,
		pt, -pt,  pt,
		pt,  pt,  pt,
		pt,  pt,  pt,
		-pt,  pt,  pt,
		-pt, -pt,  pt,

		-pt,  pt,  pt,
		-pt,  pt, -pt,
		-pt, -pt, -pt,
		-pt, -pt, -pt,
		-pt, -pt,  pt,
		-pt,  pt,  pt,

		pt,  pt,  pt,
		pt,  pt, pt,
		pt, -pt, -pt,
		pt, -pt, -pt,
		pt, -pt,  pt,
		pt,  pt,  pt,

		-pt, -pt, -pt,
		pt, -pt, -pt,
		pt, -pt,  pt,
		pt, -pt,  pt,
		-pt, -pt,  pt,
		-pt, -pt, -pt,

		-pt,  pt, -pt,
		pt,  pt, -pt, 
		pt,  pt,  pt,
		pt,  pt,  pt,
		-pt,  pt,  pt,
		-pt, pt, -pt, 
	}; //*/

	//creation Destableaux de Vertex
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//creation du buffer VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copie donnee
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//defini les attributs du vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

}

//envoi des données du cube de lumière
GLuint CubeLight::render() const{
	return VAO;
}

void CubeLight::deleteVertexBuffer(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}
