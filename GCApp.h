#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

class GCApp {
private:
	// pentru a permite clasei GCRunner sa acceseze metodele si atributele private
	friend class GCRunner;

	const char* title = "Grafica pe calculator - primul exemplu";
	const int xWindowPosition = 100;
	const int yWindowPosition = 100;
	const int windowHeight = 600;
	const int windowWidth = 600;

	GLuint vaoId; // identificator pentru Vertex Array Object
	GLuint vboPositionId; // identificator pentru Vertex Buffer Object ce va contine pozitiile varfurilor
	GLuint vboColorId; // identificator pentru Bufferul ce va contine culorile
	GLuint programId; // identificatorul programului

	void initialize()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // culoarea de fond a ecranului
		//createVAO();
		createVBOPositions();
		createVBOColors();
		createShaders();
	}

	void createVAO() {
		// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);
	}

	void createVBOPositions() {
		GLfloat vertices[] = {
			0.5f,  0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
			0.5f,  0.5f, 0.0f, 1.0f
		};

		// se creeaza un buffer nou
		glGenBuffers(1, &vboPositionId);
		// este setat ca buffer curent
		glBindBuffer(GL_ARRAY_BUFFER, vboPositionId);
		// varfurile sunt "copiate" in bufferul curent
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// se activeaza lucrul cu atribute;
		// atributul 0 = pozitie
		// valoarea 0 corespunde cu valoarea din shader-ul "example.vert" linia 4
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void createVBOColors()
	{
		// culorile, ca atribute ale varfurilor
		GLfloat colors[] = {
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		};

		// un nou buffer, pentru culoare
		glGenBuffers(1, &vboColorId);
		glBindBuffer(GL_ARRAY_BUFFER, vboColorId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		// atributul 1 = culoare
		// valoarea 1corespunde cu valoarea din shader-ul "example.vert" linia 5
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void destroyVBOs(void)
	{
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vboColorId);
		glDeleteBuffers(1, &vboPositionId);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoId);
	}

	void createShaders()
	{
		programId = LoadShaders("example.vert", "example.frag");
		glUseProgram(programId);
	}
	void destroyShaders()
	{
		glDeleteProgram(programId);
	}

	void renderFunction()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Functiile de desenare
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		glFlush();
	}
	void cleanup()
	{
		destroyShaders();
		destroyVBOs();
	}
};