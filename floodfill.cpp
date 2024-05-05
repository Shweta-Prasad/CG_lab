#include <iostream>
#include <GL/glut.h>
/*
#include <math.h>
#include <time.h>
*/

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// Function to initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

// Flood fill algorithm
void floodFill(int x, int y, float* fillColor, float* initialColor) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if (color[0] == initialColor[0] && color[1] == initialColor[1] && color[2] == initialColor[2]) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        floodFill(x - 2, y, fillColor, initialColor);
        floodFill(x + 1, y, fillColor, initialColor);
        floodFill(x, y + 1, fillColor, initialColor);
        floodFill(x, y - 2, fillColor, initialColor);
    }
}

// Mouse click callback function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = WINDOW_HEIGHT - y;
        float initialColor[] = {1, 0, 0}; // Red
        float fillColor[] = {0, 0, 1}; // Blue
        floodFill(x, y, fillColor, initialColor);
    }
}

// Function to draw the initial shapes
void drawShapes() {
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw first polygon in red
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(15, 10);
    glVertex2i(155, 200);
    glVertex2i(305, 10);
    glEnd();

    // Draw second polygon in green
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2i(300, 398);
    glVertex2i(150, 198);
    glVertex2i(450, 198);
    glEnd();

    // Draw third polygon in blue
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex2i(300, 10);
    glVertex2i(600, 10);
    glVertex2i(450, 200);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill");
    glutDisplayFunc(drawShapes);  // Call drawShapes function to draw initial shapes
    glutMouseFunc(mouse);  // Set mouse callback function
    init();   // Initialize OpenGL
    glutMainLoop();
    return 0;
}
