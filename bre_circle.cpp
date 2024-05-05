#include <GL/glut.h>
#include<iostream>
//#include<stdio.h>
//#include<math.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0); // Set drawing color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0); // Set the coordinate system range
    glPointSize(3.0f);
}

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Circle() {
    int xC = 100, yC = 100, r = 50; // Center at (100, 100), radius 50
    int x = 0, y = r;
    int d = 1 - r; // Initial decision parameter

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Set color to red

    // Draw quadrant lines
    glColor3f(0.5, 0.5, 0.5); // Gray color for lines
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(0, yC);
    glVertex2i(200, yC);
    // Y-axis
    glVertex2i(xC, 0);
    glVertex2i(xC, 200);
    glEnd();

    // Draw circle
    while (x <= y) {
        setPixel(xC + x, yC + y);
        setPixel(xC + y, yC + x);
        setPixel(xC - x, yC + y);
        setPixel(xC - y, yC + x);
        setPixel(xC + y, yC - x);
        setPixel(xC + x, yC - y);
        setPixel(xC - x, yC - y);
        setPixel(xC - y, yC - x);
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Circle");
    init();
    glutDisplayFunc(Circle);
    glutMainLoop();
    return 0;
}
