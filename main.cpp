// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

#include <string>


//////////////////////////////////////

class GCApp {
private:
	friend class GCRunner;
	const char* title = "Grafica pe calculator - primul exemplu";

	GLuint VaoId; // identificator pentru Vertex Array Object
	GLuint VboId; // identificator pentru Vertex Buffer Object ce va contine pozitiile 
	GLuint ColorBufferId; // identificator pentru Bufferul ce va contine culorile
	GLuint ProgramId; // identificatorul programului


	void createVBO()
	{
		// varfurile 
		GLfloat Vertices[] = {
			0.5f,  0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
			0.5f,  0.5f, 0.0f, 1.0f
		};

		// culorile, ca atribute ale varfurilor
		GLfloat Colors[] = {
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		  1.0f, 0.5f, 0.2f, 1.0f,
		};

		// se creeaza un buffer nou
		glGenBuffers(1, &VboId);
		// este setat ca buffer curent
		glBindBuffer(GL_ARRAY_BUFFER, VboId);
		// varfurile sunt "copiate" in bufferul curent
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
		glGenVertexArrays(1, &VaoId);
		glBindVertexArray(VaoId);

		// se activeaza lucrul cu atribute;
		// atributul 0 = pozitie
		// valoarea 0 corespunde cu valoarea din shader-ul "example.vert" linia 4
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		// un nou buffer, pentru culoare
		glGenBuffers(1, &ColorBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

		// atributul 1 = culoare
		// valoarea 1corespunde cu valoarea din shader-ul "example.vert" linia 5
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void destroyVBO(void)
	{
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &ColorBufferId);
		glDeleteBuffers(1, &VboId);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VaoId);
	}



	void createShaders()

	{
		ProgramId = LoadShaders("example.vert", "example.frag");
		glUseProgram(ProgramId);
	}
	void destroyShaders()
	{
		glDeleteProgram(ProgramId);
	}

	void initialize()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // culoarea de fond a ecranului
		createVBO();
		createShaders();
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
		destroyVBO();
	}
};

class GCRunner {
private:
	static GCApp app;

	static void render() {
		app.renderFunction();
	}

	static void cleanup() {
		app.cleanup();
	}

public:
	static void run(GCApp app, int argc = 0, char* argv[] = new char* [0]) {
		GCRunner::app = app;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
		glutInitWindowSize(600, 600); //dimensiunile ferestrei
		glutCreateWindow(app.title); // titlul ferestrei
		glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
		app.initialize();
		glutDisplayFunc(render);
		glutCloseFunc(cleanup);
		glutMainLoop();
	}
};

GCApp GCRunner::app = GCApp();



int main(int argc, char* argv[])
{
	GCApp app = GCApp();
	GCRunner::run(app, argc, argv);
}

