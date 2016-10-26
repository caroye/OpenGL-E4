#include "cube.h"

#define pnt 0.5f

Cube::Cube() {
	GLfloat vertices_triangle[] = {
		/* pour un carré
		pnt, pnt, 0.0f,
		pnt, -pnt, 0.0f,
		-pnt, -pnt, 0.0f,
		-pnt, pnt, 0.0f,
		0.0f, 1.0f, 0.0f,*/
		//Cube 3D création des vertices avec leurs coordonnées
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	}; 

    //Création des tableaux de Vertex
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Création buffer VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//creation buffer EBO
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Copie des données
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Défini les attributs du tableau de Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

}
//Constructeur d'un cube d'une taille spécifique
Cube::Cube(float pt) {
	GLfloat vertices_triangle[] = {
		//Cube 3D création des vertices avec leurs coordonnées
		-pt, -pt, -pt, 0.0f, 0.0f, -1.0f,
		pt, -pt, -pt,  0.0f, 0.0f, -1.0f,
		pt,  pt, -pt,  0.0f, 0.0f, -1.0f,
		pt,  pt, -pt,  0.0f, 0.0f, -1.0f,
		-pt,  pt, -pt, 0.0f, 0.0f, -1.0f,
		-pt, -pt, -pt, 0.0f, 0.0f, -1.0f,

		-pt, -pt,  pt, 0.0f, 0.0f, 1.0f,
		pt, -pt,  pt,  0.0f, 0.0f, 1.0f,
		pt,  pt,  pt,  0.0f, 0.0f, 1.0f,
		pt,  pt,  pt,  0.0f, 0.0f, 1.0f,
		-pt,  pt,  pt, 0.0f, 0.0f, 1.0f,
		-pt, -pt,  pt, 0.0f, 0.0f, 1.0f,

		-pt,  pt,  pt, -1.0f, 0.0f, 0.0f,
		-pt,  pt, -pt, -1.0f, 0.0f, 0.0f,
		-pt, -pt, -pt, -1.0f, 0.0f, 0.0f,
		-pt, -pt, -pt, -1.0f, 0.0f, 0.0f,
		-pt, -pt,  pt, -1.0f, 0.0f, 0.0f,
		-pt,  pt,  pt, -1.0f, 0.0f, 0.0f,

		pt,  pt,  pt, 1.0f, 0.0f, 0.0f,
		pt,  pt, pt,  1.0f, 0.0f, 0.0f,
		pt, -pt, -pt, 1.0f, 0.0f, 0.0f,
		pt, -pt, -pt, 1.0f, 0.0f, 0.0f,
		pt, -pt,  pt, 1.0f, 0.0f, 0.0f,
		pt,  pt,  pt, 1.0f, 0.0f, 0.0f,

		-pt, -pt, -pt, 0.0f, -1.0f, 0.0f,
		pt, -pt, -pt,  0.0f, -1.0f, 0.0f,
		pt, -pt,  pt,  0.0f, -1.0f, 0.0f,
		pt, -pt,  pt,  0.0f, -1.0f, 0.0f,
		-pt, -pt,  pt, 0.0f, -1.0f, 0.0f,
		-pt, -pt, -pt, 0.0f, -1.0f, 0.0f,

		-pt,  pt, -pt, 0.0f, 1.0f, 0.0f,
		pt,  pt, -pt,  0.0f, 1.0f, 0.0f,
		pt,  pt,  pt,  0.0f, 1.0f, 0.0f,
		pt,  pt,  pt,  0.0f, 1.0f, 0.0f,
		-pt,  pt,  pt, 0.0f, 1.0f, 0.0f,
		-pt, pt, -pt,  0.0f, 1.0f, 0.0f,
	}; //*/


    //Création Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Création buffer VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//creation buffer EBO
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Copie des données
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Défini les attributs du vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

}
//Envoie des données
GLuint Cube::render() const {
	return VAO;
}

//Suppression des Vertex Buffer
void Cube::deleteVertexBuffer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}