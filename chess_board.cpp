#include<GL/glut.h>
#include<iostream>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int GRID_SIZE = 4;
const float SQUARE_SIZE = static_cast<float>(WINDOW_WIDTH)/GRID_SIZE;

//Draw 4x4 chessboard
void drawChessboard() {
	bool isWhite = true; //Flag to alternate between white and black squares
	for (int i = 0; i < GRID_SIZE; ++i) {
		for(int j = 0; j<GRID_SIZE; ++j) {
			if(isWhite)
				glColor3f(1.0f, 1.0f, 1.0f);  //White color
			else
				glColor3f(0.0f, 0.0f, 0.0f);  //Black color
			isWhite = !isWhite; // Toggle color for the next square
			glBegin(GL_QUADS);
			glVertex2f(i * SQUARE_SIZE, j * SQUARE_SIZE);
			glVertex2f((i + 1) * SQUARE_SIZE, j * SQUARE_SIZE);
			glVertex2f((i + 1) * SQUARE_SIZE, (j + 1) * SQUARE_SIZE);
			glVertex2f(i * SQUARE_SIZE, (j + 1) * SQUARE_SIZE);
			glEnd();
		}
		// Toggle color at the end of each row to maintain the alternating pattern
		isWhite = !isWhite;
	}
}

// OpenGL display function
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawChessboard();
	glFlush();
}

// OpenGL initialization function
void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Chessboard");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
