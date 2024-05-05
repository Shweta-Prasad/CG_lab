#include <iostream>
#include <GL/glut.h>
/*
#include <math.h>
#include <time.h>
*/

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void boundFill(int x, int y, float *fillColor, float *boundaryColor) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        boundFill(x + 1, y, fillColor, boundaryColor);
        boundFill(x - 1, y, fillColor, boundaryColor);
        boundFill(x, y + 1, fillColor, boundaryColor);
        boundFill(x, y - 1, fillColor, boundaryColor);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = WINDOW_HEIGHT - y;
        float fillColor[] = {0, 0, 1}; // Blue
        float boundaryColor[] = {1, 0, 0}; // Red
        boundFill(x, y, fillColor, boundaryColor);
    }
}

void drawShape() {
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Red
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(drawShape);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}